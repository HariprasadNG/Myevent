module.exports = function (name, owneruser, startdate, enddate, video, audio, msg, picture){
    //var nodeuuid = require('node-uuid');
    this._name = name;
    this._owener = owneruser.uid;
    this._startedate = startdate;
    this._enddate = enddate;
    this._content = {
        video:video,
        audio:audio,
        msg:msg,
        picture:picture
    };
   // this._eveintid = nodeuuid.v4();
   //May need to add and object for public permissions
}
