//var db = require('mongojs').connect('mongodb://test:test123@ds047632.mongolab.com:47632/passport_local_mongo',['accounts']);
var arr = [];
console.log(arr.length);
var unDef;
console.log(!unDef);
var mongo = require('mongojs');
var db = mongo('mongodb://test:test123@ds047632.mongolab.com:47632/passport_local_mongo',['accounts']);
db.accounts.find(function(err,users){
    if(err){
        console.log(err);
    }else{
        users.forEach(function(user){
            console.log(user._id);
            console.log(user.username);
        });
    }
});

console.log("Reached End !!!");

