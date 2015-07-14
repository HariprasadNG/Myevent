module.exports = function (express,passport) {
    var router = express.Router();
   
    router.use(function(req,res,next){
        next();
    });

    router.get("/", function(req,res){
        //res.send("This can be my login page or some page that do not require user login");
        res.render("All/login.html");
    });

    router.post("/login", passport.authenticate('local', {
        successRedirect:'/Users/',
        failureRedirect: '/All/'
        //failureFlash: true
    }));
    
    return router;
}
