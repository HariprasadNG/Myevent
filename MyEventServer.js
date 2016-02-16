var express = require('express');
var MyEvent = express();
var passport = require('passport');

//The below routine configures app and
//registers all the routes
require('./confgiuration.js')(MyEvent,express,passport);



//Line to log the requests...
MyEvent.use(express.Router().use(function Logger(req, res, next) {
    console.log("New Request " + req.url);
    next();
}));

//Start my server here 
var server = MyEvent.listen(3000,function(){
    console.log("The MyEvent server is launched on http://localhost:3000");
});

