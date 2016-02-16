module.exports = function (express){
    var router = express.Router();

    //The is to make sure that authentication
    //is mandatory for all the request that uses
    //this router.
    //NOTE: All the routes needs to be registered 
    //post registration of the middle ware.
    router.use(function(req,res,next){
        if(req.isAuthenticated()){
            console.log("Request is authenticated " + req.method);
            return next();
        }
        console.log("User not authenticated\n!!!");
        res.redirect("/All/");
    });
    
    router.get("/", function(req,res){
        res.send("Hello logged on User " + JSON.stringify(req.user));
    });

    router.get("/session", function(req,res){
        res.send("Hello logged on User " + JSON.stringify(req.user) + " in session ");
    });


    router.route("/createevent").get( function(req,res) {
        res.render("Auth/Users/createevent.html");
    }).post(function(req,res){
        var EventObj = require('../../../Models/event.js');
        var event = new EventObj(
            req.body.eventnmae,
            req.user,
            req.body.startdate,
            req.body.enddate,
            req.body.video,
            req.body.audio,
            req.body.msg,
            req.body.picture);
        var DbOp = require('../../../Models/eventdb.js');
        DbOp.createEvent(event,function(err, matchedvent){
            if(err){
                res.render('Error/uniqueidconfilct.html');
            }else{
                res.render('Auth/Users/inviteguests.html');
            }
        });
    });
    
    return router;
}
