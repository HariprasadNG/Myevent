var mongoose = require('mongoose');
var passportLocalMongoose = require('passport-local-mongoose');
var schema = mongoose.Schema;

var Account = new schema ({
    username:String,
    email:String,
    phone:String,
    countryCode:String,
    uid:String
});

Account.plugin(passportLocalMongoose);

module.exports = mongoose.model('Account',Account);
