module.exports = function(cs, tables){
    var mongo = require('mongojs');
    var db = mongo(cs,tables);
    return db;
}
