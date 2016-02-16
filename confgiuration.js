module.exports = function (app,express,passport) {

    //These are the common paths where we keep the
    //Project specific libraries sometime required
    require.paths = ['.', './Models', './Auth'];

    var SecreteData = JSON.parse(require("fs").readFileSync('./SecreteData.json'));
        
    //Read express 4.0 migration doc
    //http://expressjs.com/guide/migrating-4.html
    //And passport doc 
    //http://passportjs.org/docs/configure
    app.use(require('cookie-parser')());
    var bodyParser = require('body-parser');
    app.use(bodyParser.json());
    app.use(bodyParser.raw());
    app.use(bodyParser.text());
    app.use(bodyParser.urlencoded({
        extended:true
    }));
    app.use(require('express-session')({
        secret: 'HariOM',
        resave: false,
        saveUninitialized:true
    }));
    /*app.use(require('multer'));----->This causes problem do not use this is required for file uplods check when required*/
    var mongoose = require('mongoose');
    mongoose.connect(require('mongodb-uri').formatMongoose(SecreteData.mongoose_connection_string));

    //Local User Auth Strategy
    var LocalStrategy = require('./Auth/Strategies/Local.js');
    var st = require('passport-local').Strategy;
    var local = new StrateryObj(LocalStrategy.name, new st(LocalStrategy.authFunc));

    //Mongodb users auth strategies.
    var MongoStrategy = require('./Auth/Strategies/Mongolocal.js');
    st = require('passport-local').Strategy;
    var mongousers = new StrateryObj(MongoStrategy.name, new st(MongoStrategy.authFunc));


    //Google Oauth2
    st = require('passport-google-oauth2').Strategy;
    var GoogleStrat = require('./Auth/Strategies/GoogleAuth.js');
    var googleusers = new StrateryObj(GoogleStrat.name, new st(SecreteData.google_auth, GoogleStrat.authFunc));

    //Register all the Auth Strategies with passport
    require('./Auth/Setstrategy.js')(passport, app, [local,mongousers,googleusers]);

    //Setting the templating engine
    //and view direcotry
    app.set('views',__dirname + '/View');
    app.set('view engine','ejs');
    app.engine('html',require('ejs').renderFile);

    //All the routes needs to be registered only after
    //the app is completly configured
    require('./RegisterRoutes.js')(app,express,passport);
};

function StrateryObj(name, strategy){
    this.strategyname = name;
    this.strategy = strategy;
}


