module.exports = function (express) {
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
        res.send("Hello logged on User " + req.user);
    });

    router.get("/session", function(req,res){
        res.send("Hello logged on User " + req.user + " in session ");
    });
    
    return router;
}
