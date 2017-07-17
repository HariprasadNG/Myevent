var urlparse = require('url');
var rwutil = {
    m_cloc:'https://127.0.0.1:8080',
    joinPath:function (f, s) {
        if (s == undefined || s=='') return f;
        if (f == undefined || f =='') return s;
        if (f[f.length-1] == '/') {
            if (s[0] == '/') {
                return f + s.substr(1, s.length);
            }
            return f + s;
        } else {
            if (s[0] == '/') {
                return f + s;
            }
            return f + '/' + s;
        }
    },
    rewriteUrl:function (u) {
        if (u == undefined || /^\s*$/.test(u)) return u;
        
        var locUrl = urlparse.parse(this.m_cloc);
        if ( /^\/\//.test(u) ) {
            u = locUrl.protocol + u;
        }
        var Url = urlparse.parse(u);
        if((Url.pathname && 
           Url.pathname.split('/').pop().indexOf('hostname') != -1)||(
           Url.protocol != 'http:' &&
           Url.protocol != 'https:' &&
           Url.protocol != null
           )) {
            return u;
        }
        var urlInfo = "";

        var protocol = locUrl.protocol;
        var port = locUrl.port;

        var hostname = locUrl.hostname;
        if (Url.hostname) {
            if (typeof(window) != undefined && 
                window != undefined &&
                window.location.hostname == Url.hostname) {
            } else {
                hostname = Url.hostname;
                protocol = Url.protocol;
                port = Url.port;
            }
        }

        if (protocol.toLowerCase() == "http") {
            urlInfo += "secure,false";
            if(port == null || /^\s*$/.test(port)) port  = "80";
        } else {
            urlInfo += "secure,true";
            if(port == null || /^\s*$/.test(port)) port  = "443";
        }

        urlInfo += ",hostname," + hostname;
        urlInfo += ",port," + port;
        
        var pathArr;
        if(Url.pathname) {
            pathArr = Url.pathname.split('/');
        }
        var file = (pathArr!=undefined)?((pathArr[pathArr.length - 1] != undefined)?pathArr[pathArr.length - 1]:''):'';
        urlInfo = urlInfo + ",file," + file;

        var pathname = locUrl.pathname;
        if (Url.pathname && Url.pathname[0] == '/') {
            pathname =  Url.pathname;
        } else {
            pathname = pathname.split('/');
            pathname.pop();
            pathname = pathname.join('/');
            pathname = rwutil.joinPath(pathname, Url.pathname);
        }
        pathname = pathname.split('/');
        pathname.pop();
        pathname = pathname.join('/');
        var x = rwutil.joinPath(pathname, urlInfo) + ((Url.search != undefined)?Url.search:'') + ((Url.hash != undefined)?Url.hash:'');
        if (x[0] != '/') x = '/' + x;
        return x;
    }
};

module.exports = {
    rewriteUrl:rwutil.rewriteUrl,
    joinPath:rwutil.joinPath,
    cloc:function(loc) {
        this.m_cloc = loc;
    },
    m_cloc:rwutil.m_cloc
}
