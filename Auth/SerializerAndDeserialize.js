module.exports = {
    serialize: function(user, done){
        //var st = new Error.stack();
        console.log("User %j", user);
        var t_user = {
            username:user.username,
            email:user.email,
            phone:user.phone,
            uid:user._id
        };
        done(null,t_user);
    },
    deserialize: function(id, done){
        //var st = new Error.stack();
        //console.log(st);
        console.log("Id %j", id);
        done(null, id);
    }
}
