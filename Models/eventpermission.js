module.exports = function(msg, video, audio, picture, event, user){
    //the filds are intigers with follwing meaning
    //001 -> can view
    //010 -> can add
    //100 -> modify //means update/delete
    this._msg = msg;
    this._video = video;
    this._audio = audio;
    this._picture = picture;
    this._eventid = event._id;
    this._userid = user.uid;
}
