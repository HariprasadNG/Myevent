var mongoose = require('mongoose');
var passportlocalmongoose = require('passport-local-mongoose');
mongoose.connect(require('mongodb-uri').formatMongoose('mongodb://test:test123@ds047632.mongolab.com:47632/passport_local_mongo'),
        function(err,account){
            console.log(err);
            console.log(account);
        });
var Account = require('./Models/mongousers.js');
Account.register(new Account({
    username:'testuser',
    password:'testpassword'
}));
