function require(module) {
    switch (module) {
        case 'url': {
            return {
                parse:function (u) {
                    var x = undefined;
                    try {
                        x = new URL(u);
                    } catch (e) {
                        if (u[0] != '/')  {
                            var cUrl = new URL(rwutil.m_cloc);
                            var y = cUrl.pathname.split('/');
                            y.pop();
                            y  = y.join('/');
                            u = y + '/' + u;
                        }
                        var t  = new URL(rwutil.m_cloc);
                        x = new URL(t.protocol + "//" + t.host + u);
                    }
                    return x;
                }
            }
        }
        case './rwutil.js': {
            rwutil.win_loc = location;
            return rwutil;
        }
        case 'not_enabled_jsdom' : {
            return {
                JSDOM:function(s) {
                   this.dom = undefined;
                   this.dom.window = document.createElement('div');
                   this.dom.window.innerHTML = s;
                   this.dom.window = this.dom.window.childNodes;

                }
            }
        }
        default:
            return undefined;
    }
}

