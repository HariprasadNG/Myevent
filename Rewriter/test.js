function dumyObj (a, b) {
	this.a=a;
    this.b=b;

    this.print = function () {
        console.log("a: " + a + " b:" + b);
    }
}

var XMLHttpRequest = {};
var window = {};
var history = {};
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
            args[0] = rwutil.rewriteUrl(args[0]);
        } else if (func == 'postMessage') {
            if (args.length > 1 )
            args[1] = rwutil.rewriteUrl(args[1]);
        } else if (obj.constructor == history.constructor && 
                   (func == 'replaceState' ||
                    func == 'pushState')) {
            args[2] = rwutil.rewriteUrl(args[2]);
        }
        if (funApply != null) 
            return funcApply.apply(obj, args);
        if(func == 'bind') debugger; 
        if(obj[func] == null) debugger;
        return obj[func].apply(obj, args);
    }

var x = new dumyObj(1,2);
var f = function (x,y, a, b) {
console.log("x:y:" + x + y);
console.log("a:b:" + a + b);
this.print();
};
var bf = null;//f.bind.call(f, x);
//bf('h', 'a');

//bf = f.call.apply(f.bind,[f,x]);
bf = DSMemberFuncCall(f.call, "apply", [f.bind,[f,x,'hi' ,' hari' ]]);
bf('ha','riprasad');

var xyz = function(a, b, c) { 
            return function () {
                console.log(arguments.length);
                console.log(a);
            };
}

xyz('h', 'a', 'r')();
