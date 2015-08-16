module.exports = {
    serialize: function(user, done){
        var t_user = {
            username:user.username,
            email:user.email,
            phone:user.phone,
            uid:user._id

        };
        done(null,t_user);
    },
    deserialize: function(id, done){
        done(null, id);
    }
}
