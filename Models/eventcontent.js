module.exports = function(type, content, event, user){
    this._type = type; // video/msg/audio/picture
    this._content = content; //this will be path in case of audio/video/picture or message in case of  msg
    this._timestamp;
    this._eventid = event._id; //uuid of the event to which this item belogns to
    this._from = user.uid;
}
