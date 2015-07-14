module.exports = function(express){
    var router = express.Router();
    
    router.get("/", function(req,res){
        res.send("The Admin login page goes here");
    });
    
    return router;
}
