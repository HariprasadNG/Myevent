module.exports = function(user, pass, done){
    console.log("verifying " + user + " " + pass);
    if(user == 'hariprasad'){
        if(pass == 'password'){
            return done(null, user);
        }else{
            return done(null, false, {
                'message':'Incorrect password'
            });
        }
    }else if(user == 'erroruser'){
        return done(user);
    }else{
        return done(null, false, {
            'message':'Incorrect username'
        });
    }
}
