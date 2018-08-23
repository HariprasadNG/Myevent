    var orgBind = Function.prototype.bind;
    Function.prototype.bind = function (obj) {
        if (arguments[0] == history && (
                    this.name == 'pushState'||
                    this.name == 'replaceState')) {
            var tArgs = [window, history, this.name + "_bind"];
            for (var i = 1; i < arguments.length - 1; i++ ){
                tArgs.push(arguments[i]); 
            }
            return  orgBind.apply(DSMemberFuncCall, tArgs);
        }
        return orgBind.apply(this, arguments);
    }
    require = undefined;
    function unrewriteUrl(url) {
        var urlObj = new URL(url);
        var pArr = urlObj.pathname.split('/');
        var infoArr = pArr.pop().split(',');
        var prop = {};
        for (var i = 0; i < infoArr.length; i+=2) {
            prop[infoArr[i].toLowerCase()] = infoArr[i+1];
        }

        var url = "";;
        if(/true/.test(prop['secure'])) {
            url += "https://";
        } else {
            url += "http://";
        }

        url += prop['hostname'];
        if (prop['port']) {
            url += ":"+prop['port'];
        }

        url = rwutil.joinPath(url, pArr.join('/'));
        url = rwutil.joinPath(url, prop['file']);
        return url;
    }
    rwutil.m_cloc = unrewriteUrl(window.location.href);
    var esprima = window.esprima;
    var code = window.escodegen;
    window.escodegen = cstcodegen.OverrideCodeGen(window.escodegen);
    code = window.escodegen;
    function DSMemberFuncCall(obj, func, args) { 
        if (obj == Function.prototype.bind && func == 'toString') {
            return orgBind.toString();
        }
        var funApply = null;
        if (func == 'apply' || func == 'call') {
            var funcApply = obj;
            if (func == 'apply') {
                obj = args[0];
                args = args[1];
            } else if (func == 'call') {
                obj = args[0];
                args = args.slice(1, args.length);
            }
            func = funcApply.name;
            if (obj == null) {
                return funcApply.apply(obj,args);
            }
            funApply = true;
        }
        if (obj == null) obj = window;
        if (obj.tagName != undefined) {
            if (func == "append" || 
                func == "appendChild" ||
                func == "insertBefore") {
                var htmlRw = new ctrw.htmlRewriter(window.esprima, window.escodegen, rwutil);
                htmlRw.rewriteDom(args[0]);
            }
        } else if (obj.constructor == XMLHttpRequest && func == 'open') {
              args[1] = rwutil.rewriteUrl(args[1]);
        } else if (obj.constructor == window.ServiceWorkerContainer && func == 'register') {
            //args[0] = rwutil.rewriteUrl(args[0]);
            //args[0] +=  ",rewrite,false";
            args[0] = rwutil.rewriteUrl(args[0]);
            args[0] = args[0].replace(/secure,true/i, "secure,true,sw,true");
            for (var i = 2; i < arguments.length; i++) {
                args.push(arguments[i]);
            }
        } else if (func == 'postMessage') {
            if (args.length > 1  && args[1] != '*')
            args[1] = rwutil.rewriteUrl(args[1]);
        } else if (obj.constructor == history.constructor && 
                   (/replaceState/.test(func) ||
                    /pushState/.test(func))) {
           if (/_bind/.test(func)) {
               //Called via bind for needs to reprare the args array.
               func = func.replace(/_bind/,'');
               args = [];
               for (var i = 2; i < arguments.length; i++) {
                   args.push(arguments[i]);
               }
           }
           args[2] = rwutil.rewriteUrl(args[2]);
           return history[func](args[0], args[1], args[2]);
        } else if (obj == window.caches && func == 'match') {
            if (args[0] && args[0].url) {
                console.log(args[0].url);
                //args[0].url = unrewriteUrl(args[0].url);
            }
        }
        if (funApply != null) 
            return funcApply.apply(obj, args);
        if(func == 'bind') debugger; 
        if(obj[func] == null) debugger;
        return obj[func].apply(obj, args);
    }
    function DSFuncCall(func, args) {
        return func.apply(this, args);
    }
    function DSAssign(left, member, op, right) {
        switch (op) {
            case '=':{
                if ( (left && left.tagName)&&
                     member.toLowerCase && 
                     (member.toLowerCase() == 'src'||
                     member.toLowerCase() == 'href')) {
                    left[member] = rwutil.rewriteUrl(left[member]);
                } else if ((left && (left == window || left == document) )&&
                           member == 'location') {
                    left[member] = rwutil.rewriteUrl(right);
                }else {
                    left[member] = right;
                }
                break;
            }
            case '+=':{
                left[member] += right;
                break;
            }
            case '-=':{
                left[member] -= right;
                break;
            }
            case '*=':{
                left[member] *= right;
                break;
            }
            case '/=':{
                left[member] /= right;
                break;
            }
            case '%=':{
                left[member] %= right;
                break;
            }
            case '|=':{
                left[member] |= right;
                break;
            }
            case '&=':{
                left[member] &= right;
                break;
            }
            case '^=':{
                left[member] ^= right;
                break;
            }
            default: {
                left[member] = right;
                console.error("Unknow operator " + op);
            }
        }
        return left[member];
    }
    function DSMemberGet(obj, mem) {
        if (mem == 'location') {
            return new URL(rwutil.m_cloc);
        } else if (/^src$/i.test(mem) ||
                   /^href$/i.test(mem)) {
            return unrewriteUrl(obj[mem]);
        } else {
            return obj[mem];
        }
    }
    function DSMemberGetNUpdate(prefix, obj, mem, op) {
        if ( op == '++') {
            if (prefix) {
                return ++obj[mem];
            } else {
                return obj[mem]++;
            }
        } else {
            if (prefix) {
                return --obj[mem];
            } else {
                return obj[mem]--;
            }

        }
    }
