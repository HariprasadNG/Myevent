var jsdom = require('jsdom');//this is easy to eliminate;
var fs = require('fs');

function baseRewriter() {
    this.buf = "";
    this.append = function (data) {
        this.buf += data;
    }
    this.rewrite = function () {
        return this.buf;
    }
}
jsRewriter.prototype = new baseRewriter();
jsRewriter.prototype.constructor = jsRewriter;
jsRewriter.prototype.rewrite = function () {
    try {
        var ast = this.esprima.parse(this.buf);
        this.buf = this.code.generate(ast);
        var bootstrp = '"use strict";';
        /*if (fs) {
            bootstrp = '"use strict";' + fs.readFileSync('./clientimpl.js');
        }*/
        bootstrp = '//Strict removed';
        this.buf = this.buf.replace(/[\'\"]use\s+strict[\'\"];/, bootstrp);
    } catch (e) {
        console.error("Error while JavaScript rewriting " + e);
        //console.log(this.buf);
        throw e;
    }
    return this.buf;
}
function jsRewriter(esprima, code) {
    this.esprima = esprima;
    this.code = code;
    return this;
}

htmlRewriter.prototype = new baseRewriter();
htmlRewriter.prototype.constructor = htmlRewriter;
htmlRewriter.prototype.rewrite = function() {
    var dom = undefined;
    if (jsdom) {
        dom = new jsdom.JSDOM(this.buf);
    } else {
       dom.window = window; 
    }

    this.rewriteDom(dom.window.document);

    var x = "";
    if (fs) {
        x = fs.readFileSync('./clientbootstrap.html');
    }

    if (jsdom) {
        if (dom.window.document.children.length > 0) {
            var div = dom.window.document.createElement('div');
            div.innerHTML = x;
            dom.window.document.insertBefore(div,dom.window.document.children[0])
        }
        this.buf = dom.serialize();
    } else {
        this.buf = dom.outerHTML;
    }
    
    return this.buf;
}
htmlRewriter.prototype.tags = {
    script:function (dom) {
        var jsrw = new jsRewriter(this.esprima, this.code);
        jsrw.append(dom.innerHTML);
        dom.innerHTML = jsrw.rewrite();
    }
}
htmlRewriter.prototype.rewriteAttr = function (dom) {
    for (var at in dom) {
        switch (at.toLowerCase()) {
            case 'href':
            case 'src': {
                if (
                    dom[at] != undefined && 
                    !(/^\s*$/.test(dom[at])) && 
                    !(/^data\:/i.test(dom[at]))
                   ) {
                    dom[at] = this.rwutil.rewriteUrl(dom[at]);
                }
                break;
            }
            case 'onafterprint':
            case 'onbeforeprint':
            case 'onbeforeunload':
            case 'onerror':
            case 'onhashchange':
            case 'onload':
            case 'onmessage':
            case 'onoffline':
            case 'ononline':
            case 'onpagehide':
            case 'onpageshow':
            case 'onpopstate':
            case 'onresize':
            case 'onstorage':
            case 'onunload':

            case 'onblur':
            case 'onchange':
            case 'oncontextmenu':
            case 'onfocus':
            case 'oninput':
            case 'oninvalid':
            case 'onrset':
            case 'onsearch':
            case 'onselect':
            case 'onsubmit':

            case 'onkeydown':
            case 'onkeyup':
            case 'onkeypress':

            case 'onclick':
            case 'ondbclick':
            case 'onmousedown':
            case 'onmousemove':
            case 'onmouseout':
            case 'onmouseover':
            case 'onmouseup':
            case 'onmousewheel':
            case 'onwheel':

            case 'ondrag':
            case 'ondragend':
            case 'ondragenter':
            case 'ondragleave':
            case 'ondragover':
            case 'ondragstrart':
            case 'ondrop':
            case 'onscroll':

            case 'oncopy':
            case 'oncut':
            case 'onpaste':
            
            case 'onabort':
            case 'oncanplay':
            case 'oncanplaythrough':
            case 'oncuechange':
            case 'ondurationchange':
            case 'onemptied':
            case 'onended':
            case 'onerror':
            case 'onloadeddata':
            case 'onloadedmetadata':
            case 'onloadstart':
            case 'onpause':
            case 'onplay':
            case 'onplaying':
            case 'onprogress':
            case 'onratechange':
            case 'onseeked':
            case 'onseeking':
            case 'onstalled':
            case 'onsuspend':
            case 'ontimeupdate':
            case 'onvolumechange':
            case 'onwaiting':

            case 'onshow':
            case 'ontoggle': {
                if(dom[at]) {
                    var x = '(' + dom[at] + ')';
                    if (typeof(dom[at]) == "function") {
                        x = '(' + dom[at].toString() + ')';
                    } else {
                        break;
                    }
                    if (/DSFuncCall|DSAssign|DSMemberFuncCall/g.test(x)) {
                        break;
                    }
                    var jsRw = new jsRewriter(this.esprima, this.code);
                    jsRw.append(x);
                    x = jsRw.rewrite();
                    dom[at] = eval(x);
                }
            }
        }
    }
}
htmlRewriter.prototype.rewriteDom = function(dom) {
    if (dom == undefined) return;

    this.rewriteAttr(dom);
    if (dom.tagName && this.tags[dom.tagName.toLowerCase()]) {
        this.tags[dom.tagName.toLowerCase()].apply(this, [dom]);
    }
    var cn = dom.childNodes;
    for (var d in cn) {
       this.rewriteDom(cn[d]);
    }
}
function htmlRewriter(esprima, code, rwutil) {
    this.esprima = esprima;
    this.code = code;
    this.rwutil = rwutil;
    return this;
}

var ctrw = {
    baseRewriter:baseRewriter,
    jsRewriter:jsRewriter,
    htmlRewriter:htmlRewriter
}

module.exports = {
    baseRewriter:baseRewriter,
    jsRewriter:jsRewriter,
    htmlRewriter:htmlRewriter
}
