module.exports = function (app,express,passport){
    //Register all routers
    app.use( require('./Routes/All/Router.js')(express,passport));
    app.use('/All', require('./Routes/All/Router.js')(express,passport));
    app.use('/Users', require('./Routes/Auth/Users/Router.js')(express,passport));
    app.use('/Admin', require('./Routes/Auth/Admin/Router.js')(express,passport));

    //Register All static content
    app.use("/Static", express.static('Static'));
};
