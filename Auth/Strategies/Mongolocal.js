var Account = require('../../Models/mongousers.js');
module.exports = {
    authFunc:Account.authenticate(),
    name:'mongousers'
}
