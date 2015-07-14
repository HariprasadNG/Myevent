module.exports = function (passport, app, strategies) {
    app.use(passport.initialize());
    app.use(passport.session());

    strategies.forEach(function(item){
        passport.use(item.strategyname,new item.strategy(item.authenticate));
    });

    //Note all the Auth strategies use same serializers and deserializers
    passport.serializeUser(require('./SerializerAndDeserialize.js').serialize);
    passport.deserializeUser(require('./SerializerAndDeserialize.js').deserialize);
}
