module.exports = function (passport, app, strategies) {
    app.use(passport.initialize());
    app.use(passport.session());

    strategies.forEach(function(item){
        var x;
        for (x in item.strategy)
            console.log(x+ ":" + item.strategy[x]);
        passport.use(item.strategyname,item.strategy);
    });

    //Note all the Auth strategies use same serializers and deserializers
    passport.serializeUser(require('./SerializerAndDeserialize.js').serialize);
    passport.deserializeUser(require('./SerializerAndDeserialize.js').deserialize);
}
