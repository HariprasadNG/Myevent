module.exports = {
    name:"GoogleAuth",
    authFunc:function(req, acceTk, refreshTk, profile, done) {
        var user = {username:profile.email, uid:profile.id, email:profile.email};
        return done(null,user);
    }
};
