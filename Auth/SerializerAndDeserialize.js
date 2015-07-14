module.exports = {
    serialize: function(user, done){
        done(null,user);
    },
    deserialize: function(id, done){
        done(null, id);
    }
}
