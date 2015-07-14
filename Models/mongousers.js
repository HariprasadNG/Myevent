var mongoose = require('mongoose');
var passportLocalMongoose = require('passport-local-mongoose');
var schema = mongoose.Schema;

var Account = new schema ({
    username:String,
    password:String
});

Account.plugin(passportLocalMongoose);

module.exports = mongoose.model('Account',Account);
