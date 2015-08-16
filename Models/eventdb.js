module.exports = {

    createEvent:function(event, callback){
        //Update the connection string here
        var db = require('./db.js')('mongodb://test:test123@ds047632.mongolab.com:47632/passport_local_mongo',['events']);
        db.events.insert(event,function(err,inserted){
            if(err)
                callback(err, inserted);
            else
                callback(null, inserted);
        } );
    },

    updateEvent:function(event, callback){

    }
}
