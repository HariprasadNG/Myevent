var http = require('https');
var https = require('https');
var urlparse = require('url');
var ctrw = require('./ctrw.js');
var fs = require('fs');


function backEndReqOpt(infoSt, rwutil) {
    var info = infoSt.split(',');
    this.port = 80;
    this.path = '/';
    this.rwutil = rwutil;
    this.method = 'GET';
    this.rewrite = true;
    for (var i = 0; i < info.length; i+=2) {
        if (/true/i.test(info[i+1])) {
            this[info[i]] = true;
        } else if (/false/i.test(info[i+1])) {
            this[info[i]] = false;
        } else {
            this[info[i]] = info[i+1];
        }
    }
   
    if (this.hostname) {
        this.host = this.hostname;
    } else {
        this.hostname = this.host;
    }

    this.setHttpMethod = function(m) {
        this.method = m;
    }

    this.setHttpPath = function (p) {
        if (this.file != undefined) {
            this.path = this.rwutil.joinPath(this.path, this.rwutil.joinPath(p,this.file));
        }
        if (!this.file || /\s+/.test(this.file)){
            this.path = this.rwutil.joinPath(this.path, '/');
        }
    }

    this.setHttpAuth = function(a) {
        this.auth = a;
    }

    this.setHttpHeaders = function(h) {
        this.headers = h;
        this.headers['accept-encoding'] = 'identity';

        this.headers.host = this.host + ":" + this.port;
    }

    this.setSearch = function(s) {
        if ( s != undefined)
        this.path += s;
    }

    this.setHash = function(h) {
        if (h != undefined) {
            this.path += '#' + h;
        }
    }

    this.generateUrl = function() {
        var result = '';
        if (this.secure) {
            result += "https://";
        } else {
            result += "http://";
        }
        if (this.hostname) {
            result += this.hostname;
        }
        if (this.port) {
            result += ":" + this.port;
        }

        result = this.rwutil.joinPath(result, this.path);
        return result;
    };

    return this;
};

function bkClient(req, res, esprima, code, rwutil) {
    var url = urlparse.parse(req.url);
    var urlComp = url.pathname.split('/');
    var urlhost = urlComp.pop();
    this.rwutil = rwutil;
    this.uInfo = new backEndReqOpt(urlhost, this.rwutil);
    this.uInfo.setHttpMethod(req.method);
    this.uInfo.setHttpPath(urlComp.join('/'));
    this.uInfo.setHttpAuth(req.auth);
    this.uInfo.setHttpHeaders(req.headers);
    this.uInfo.setSearch(url.search);
    this.uInfo.setHash(url.hash);
    this.orgReq = req;
    this.orgRes = res;
    this.extReq;
    this.extRes;
    this.Rewriter;
    this.esprima = esprima;
    this.code = code;
    this.bd = '';
    this.handleExError = function (e) {
        this.orgRes.writeHead(500, {'Content-Type':'text/html'});
        this.orgRes.write(JSON.stringify(e)+ '<br />');
        this.orgRes.end();
    }

    this.handleExRes = function (exRes) {
        this.extRes = exRes;
        exRes.setEncoding("utf8");
        if (exRes.headers.referrer) {
            this.rwutil.cloc(exRes.headers.referrer);
        } else {
            this.rwutil.cloc(this.uInfo.generateUrl());
        }
        delete exRes.headers['x-frame-options'];
        for (v in exRes.headers) {
            console.log(v + ":" + exRes.headers[v]);
        }

        this.Rewriter = this.createRewriter();

        exRes.on("data", function(data) {
            this.Rewriter.append(data);
        }.bind(this));
        exRes.on("end", function() {
            var buf = this.Rewriter.rewrite();
            if (exRes.statusCode == '302' ||
                exRes.statusCode == '307' ||
                exRes.statusCode == '301') {
                exRes.headers.location = this.rwutil.rewriteUrl(exRes.headers.location);
            }
            if (exRes.statusCode == '404') {
                console.log("HEADERS: " + JSON.stringify(this.uInfo.headers));
                console.error("404 FOR LINK " + this.uInfo.generateUrl());
            }
            console.log(exRes.headers['content-security-policy']);
            if (exRes.headers['content-security-policy'] != null)
                delete exRes.headers['content-security-policy'];
            exRes.headers['content-length'] = Buffer.byteLength(buf);
            this.orgRes.writeHead(exRes.statusCode, exRes.headers);
            if (this.uInfo.sw) {
                var hkfs = fs.readFileSync('./clientimpl.js');
                buf = hkfs + buf;
            }
            this.orgRes.write(buf);
            this.orgRes.end();
        }.bind(this));
    }

    this.createRewriter = function(exRes) {
        if (this.uInfo.rewrite == false) {
            return new ctrw.baseRewriter();
        }

        if (this.uInfo.type) {
            if (this.uInfo.type.toLowerCase() == "js") {
                return new ctrw.jsRewriter(this.esprima,this.code);
            } else if (this.uInfo.type.toLowerCase() == 'html') {

            }
        } else if (this.extRes.headers['content-type']) {
            if (this.extRes.headers['content-type'].toLowerCase().indexOf("javascript") != -1) {
                return new ctrw.jsRewriter(this.esprima, this.code);
            } else if (this.extRes.headers['content-type'].toLowerCase().indexOf('html') != -1) {
                return new ctrw.htmlRewriter(this.esprima, this.code, this.rwutil); 
            }
        } 

        return new ctrw.baseRewriter();
    }

    this.prepareforBackendRq = function() {
        this.orgReq.on('data', function(data) {
         this.bd += data;
        }.bind(this));
        this.orgReq.on('end', function() {
            this.requestBackend();
        }.bind(this));
    }
    this.requestBackend = function () {
        var retExRq;
        if (this.uInfo.hostname == undefined ||
            this.uInfo.hostname == '') {
            console.error("NO HOST " + this.orgReq.url);
        }
        console.log("Recived request " + this.orgReq.url);
        if (this.uInfo.secure) {
            console.log("Making https req " + this.uInfo.generateUrl());
            retExRq = https.request(this.uInfo);
        } else {
            console.log("Making http req " + this.uInfo.generateUrl());
            retExRq = http.request(this.uInfo);
        }
        this.extReq = retExRq;
        retExRq.on('response', function(res){ this.handleExRes(res); }.bind(this));
        retExRq.on('error', function(e) {this.handleExError(e); }.bind(this));
        retExRq.write(this.bd);
        retExRq.end();
    }
}

module.exports = {
    bkClient:bkClient,
    backEndReqOpt:backEndReqOpt
}
