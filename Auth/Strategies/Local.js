module.exports = {
    authFunc:function(user, pass, done){
        console.log("verifying " + user + " " + pass);
        if(user == 'hariprasad'){
            if(pass == 'password'){
                return done(null, {'username':user,
                                   'email':'aa@aa.com',
                                   'phone':123456789,
                                   'uid':45444});
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
    },

    name:'local'
}
