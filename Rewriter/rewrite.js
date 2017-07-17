var esprima = require('esprima');
var code = require('escodegen');
var http = require('http');
var url = require('url');
var fs = require('fs');
var rwutil = require('./rwutil.js');
var ctrw = require('./ctrw.js');
var bkend = require('./bkEndClinet.js');
var cstcode = require('./cstcodegen.js');
var space = '';
var https = require('https');
var options = {
    key: fs.readFileSync('./dev.hari.com.pem'),
    cert:fs.readFileSync('./dev.hari.com.crt')
};
var srv = https.createServer(options, requestHandler);

code = cstcode.OverrideCodeGen(code);
srv.listen(443);

function requestHandler(req, res) {
    var reqUrl = url.parse(req.url);
    if (/servelocal=true/i.test(reqUrl.search)) {
        var path = reqUrl.pathname;
        path = '.' + path;
        var stat = fs.statSync(path);
        res.writeHead(200, {
            'Content-Type':'text/javascript',
            'Content-Length':stat.size
        });
        var bdStream = fs.createReadStream(path);
        bdStream.pipe(res);
    } else if (/\/favicon.ico$/.test(reqUrl.pathname)){
       fs.createReadStream('rw.png').pipe(res);
    } else {
        var client = new bkend.bkClient(req, res, esprima, code, rwutil);
        client.prepareforBackendRq();
    }
}
/**********************************************************************************************************
                            FINISH OF CODE BELOW IS JUNK COD`E
/**********************************************************************************************************/
