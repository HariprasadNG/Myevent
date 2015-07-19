module.exports = function (express,passport) {
    var router = express.Router();
   
    router.use(function(req,res,next){
        next();
    });

    router.get("/local", function(req,res){
        //res.send("This can be my login page or some page that do not require user login");
        res.render("All/login_local.html");
    });

    router.get("/mongo", function(req,res){
        //res.send("This can be my login page or some page that do not require user login");
        res.render("All/login_mongo.html");
    });

    var MongoStr = require('../../Auth/Strategies/Mongolocal.js');

    router.post("/loginmongo", passport.authenticate(MongoStr.name, {
        successRedirect:'/Users/',
        failureRedirect: '/All/'
        //failureFlash: true
    }));

    var LocalStr = require('../../Auth/Strategies/Local.js');

    router.post("/loginlocal", passport.authenticate(LocalStr.name, {
        successRedirect:'/Users/',
        failureRedirect: '/All/'
        //failureFlash: true
    }));

    router.route("/register").get(function(req,res){
        res.render("All/register.html");
    }).post(function(req,res){
        var Act = require('../../Models/mongousers.js');
        Act.register(new Act({
            username:req.body.username,
            password:req.body.password
        }),req.body.password, function(err,account){
            if(err){
                res.render(err);
            }
        });
    });
    
    return router;
}
