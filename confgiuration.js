module.exports = function (app,express,passport) {
    //Read express 4.0 migration doc
    //http://expressjs.com/guide/migrating-4.html
    //And passport doc 
    //http://passportjs.org/docs/configure
    app.use(require('cookie-parser')());
    app.use(require('express-session')({
        secret: 'HariOM',
        resave: false,
        saveUninitialized:false
    }));
    var bodyParser = require('body-parser');
    app.use(bodyParser.json());
    app.use(bodyParser.raw());
    app.use(bodyParser.text());
    app.use(bodyParser.urlencoded({
        extended:true
    }));
    /*app.use(require('multer'));----->This causes problem do not use this is required for file uplods check when required*/

    //Out Auth strtegies for local Auth
    var LocalStrategy = require('./Auth/Strategies/Local.js');
    var local = new StrateryObj(LocalStrategy.name, LocalStrategy.authFunc,
            require('passport-local').Strategy);

    var MongoStrategy = require('./Auth/Strategies/Mongolocal.js');
    var mongousers = new StrateryObj(MongoStrategy.name, MongoStrategy.authFunc,
            require('passport-local').Strategy);
    var mongoose = require('mongoose');
    mongoose.connect(require('mongodb-uri').formatMongoose('mongodb://test:test123@ds047632.mongolab.com:47632/passport_local_mongo'));

    //Register all the Auth Strategies with passport
    require('./Auth/Setstrategy.js')(passport, app, [local,mongousers]);

    //Setting the templating engine
    //and view direcotry
    app.set('views',__dirname + '/View');
    app.set('view engine','ejs');
    app.engine('html',require('ejs').renderFile);

    //All the routes needs to be registered only after
    //the app is completly configured
    require('./RegisterRoutes.js')(app,express,passport);
};

function StrateryObj(name, authenticate, strategy){
    this.strategyname = name;
    this.authenticate = authenticate;
    this.strategy = strategy;
}


