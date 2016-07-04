String Header(){
  return String(
"<!DOCTYPE html>"
"<html xmlns=\"http://www.w3.org/1999/xhtml\">"
"<head>"
"<title>ESPBotino</title>"
    );
}

String Content1(){
    return String(
"<style>"
"html, body, form{height: 100%;}"
".button {width: 305px;height: 55px;font-size: 13px;letter-spacing: 2.5px;font-weight: 500;color: #000;background-color: #fff;border: none;border-radius: 45px;box-shadow: 0px 8px 15px rgba(0, 0, 0, 0.1);transition: all 0.3s ease 0s;cursor: pointer;outline: none;}"
".button:hover { background-color: #2EE59D; box-shadow: 0px 15px 20px rgba(46, 229, 157, 0.4); color: #fff; transform: translateY(-7px);}"
".pwholder {  width: 400px;  position: relative;  }"
"input { width: 275px;  padding: 15px 12px;  margin-bottom: 5px; border: 1px solid #e5e5e5;  border-bottom: 2px solid #ddd;  background: #f2f2f2;  color: #555;}"
".password + .unmask {  position: absolute;  left: 260px;  top: 12px; text-indent: -9999px; width: 25px; height: 25px; background: #aaa;  border-radius: 50%; cursor: pointer; border: none;  -webkit-appearance: none; }"
".password + .unmask:before { content: \"\";  position: absolute;  top: 4px; left: 4px;  width: 17px; height: 17px; background: #e3e3e3;  z-index: 1;  border-radius: 50%; }"
".password[type=\"text\"] + .unmask:after {  content: \"\"; position: absolute;  top: 6px;  left: 6px;  width: 13px; height: 13px; background: #aaa;  z-index: 2; border-radius: 50%;  }"
".form-select { -moz-user-select: -moz-none; -ms-user-select: none; -webkit-user-select: none; user-select: none; background: #ffffff; overflow: hidden; border: 1px solid #cbcbcb; border-radius: 3px; box-shadow: 0 0 1px rgba(0, 0, 0, 0.1), inset 0 0 10px rgba(0, 0, 0, 0.07);-moz-transition: box-shadow 0.2s; -o-transition: box-shadow 0.2s; -webkit-transition: box-shadow 0.2s; transition: box-shadow 0.2s; }"
".form-select:focus, .form-select:hover { box-shadow: 0 0 15px rgba(0, 0, 0, 0.2);}"
".form-select:after { content: '+'; position: absolute; top: 0; right: 12px; z-index: 1; color: #bbbbbb; line-height: 40px; font-size: 14px;}"
".ie .form-select:after { display: none;}"
"select {  position: relative; background: transparent; background-image: none; display: block; width: 100%; outline: none;  color: #888888;cursor: pointer;  z-index: 2; border: none; padding: 10px 10px 10px 5px; text-indent: 5px; -moz-appearance: none; -webkit-appearance: none;}"
"select[multiple=multiple] { height: auto; border: 1px solid #cbcbcb; border-radius: 3px;  box-shadow: 0 0 1px rgba(0, 0, 0, 0.1), inset 0 0 10px rgba(0, 0, 0, 0.07);-moz-transition: box-shadow 0.2s; -o-transition: box-shadow 0.2s; -webkit-transition: box-shadow 0.2s; transition: box-shadow 0.2s;}"
"select[multiple=multiple]:hover { border-color: #cccccc; box-shadow: 0 0 15px rgba(0, 0, 0, 0.2);}"
"select option[disabled] { color: #eeeeee; text-shadow: none; border: none;}"
"select:-moz-focusring { color: transparent; text-shadow: 0 0 0 #888888;}"
"select::-ms-expand { display: none;}"
".column-5 { position: absolute;  top: 30%; left: 50%; margin: -20px 0 0 -150px; width: 300px;}"
".column-6 { position: absolute;  top: 45%;  left: 50%;  margin: -20px 0 0 -150px;  width: 300px;}"
".column-7 { position: absolute; top: 55%; left: 50%; margin: -20px 0 0 -150px;  width: 300px;}"
".column-8 { position: absolute; top: 65%; left: 50%; margin: -20px 0 0 -150px; width: 300px;}"
"</style>"
"</head>" 
  );
}

String Content2(){
  return String(
"<body>"
    "<div><canvas id=\"demo-canvas\"></canvas></div>"
    "<form id=\"large-header\" method=\"post\" action=\"wifisave\">"
           "<h2 style=\"position: absolute; top: 5%; left: 5%;\">ESPBotino WiFi Config :P</h2>"
        "<div class=\"column-5\"><h2><input name=\"wn\" placeholder=\"Give ur toy a Name\"></h2></div>"        
        "<div class=\"column-6 form-select\">"
            "<select name=\"n\" id=\"\">"
                "<option value=\"\" disabled=\"disabled\" selected=\"selected\">Choose a WiFi</option>"
  
  );
}



String Content3(){
    return String(
            "</select>"
        "</div>"
        "<div class=\"column-7\">"
            "<div class=\"pwholder\"><input name=\"p\"type=\"password\" value=\"\" placeholder=\"Enter Password\" id=\"password\" class=\"password\"><button class=\"unmask\" type=\"button\" onclick=\"unmask_onclick()\" title=\"Mask/Unmask password to check content\">Unmask</button></div>"
            "<script> function unmask_onclick() { if (document.getElementById('password').type == \"password\") { document.getElementById('password').type = \"text\"; } else { document.getElementById('password').type = \"password\"; } } </script>"
        "</div>"
        "<div class=\"column-8\"><button type=\"submit\" class=\"button\">SAVE WiFi</button></div>"
    "</form>"
    
"</body>"

"</html>" 
      
      );
}


String Script1(){
  return String(
"<script src='http://"+(String)WiFi.softAPIP()+"/1.js'></script>"
  );    
}

String Script2(){
  return String(
    "<script> var _gsScope=\"undefined\"!=typeof module&&module.exports&&\"undefined\"!=typeof global?global:this||window;(_gsScope._gsQueue||(_gsScope._gsQueue=[])).push(function(){\"use strict\";_gsScope._gsDefine(\"easing.Back\",[\"easing.Ease\"],function(t){var e,i,s,r=_gsScope.GreenSockGlobals||_gsScope,n=r.com.greensock,a=2*Math.PI,o=Math.PI/2,h=n._class,l=function(e,i){var s=h(\"easing.\"+e,function(){},!0),r=s.prototype=new t;return r.constructor=s,r.getRatio=i,s},_=t.register||function(){},u=function(t,e,i,s){var r=h(\"easing.\"+t,{easeOut:new e,easeIn:new i,easeInOut:new s},!0);return _(r,t),r},c=function(t,e,i){this.t=t,this.v=e,i&&(this.next=i,i.prev=this,this.c=i.v-e,this.gap=i.t-t)},p=function(e,i){var s=h(\"easing.\"+e,function(t){this._p1=t||0===t?t:1.70158,this._p2=1.525*this._p1},!0),r=s.prototype=new t;return r.constructor=s,r.getRatio=i,r.config=function(t){return new s(t)},s},f=u(\"Back\",p(\"BackOut\",function(t){return(t-=1)*t*((this._p1+1)*t+this._p1)+1}),p(\"BackIn\",function(t){return t*t*((this._p1+1)*t-this._p1)}),p(\"BackInOut\",function(t){return 1>(t*=2)?.5*t*t*((this._p2+1)*t-this._p2):.5*((t-=2)*t*((this._p2+1)*t+this._p2)+2)})),m=h(\"easing.SlowMo\",function(t,e,i){e=e||0===e?e:.7,null==t?t=.7:t>1&&(t=1),this._p=1!==t?e:0,this._p1=(1-t)/2,this._p2=t,this._p3=this._p1+this._p2,this._calcEnd=i===!0},!0),d=m.prototype=new t;return d.constructor=m,d.getRatio=function(t){var e=t+(.5-t)*this._p;return this._p1>t?this._calcEnd?1-(t=1-t/this._p1)*t:e-(t=1-t/this._p1)*t*t*t*e:t>this._p3?this._calcEnd?1-(t=(t-this._p3)/this._p1)*t:e+(t-e)*(t=(t-this._p3)/this._p1)*t*t*t:this._calcEnd?1:e},m.ease=new m(.7,.7),d.config=m.config=function(t,e,i){return new m(t,e,i)},e=h(\"easing.SteppedEase\",function(t){t=t||1,this._p1=1/t,this._p2=t+1},!0),d=e.prototype=new t,d.constructor=e,d.getRatio=function(t){return 0>t?t=0:t>=1&&(t=.999999999),(this._p2*t>>0)*this._p1},d.config=e.config=function(t){return new e(t)},i=h(\"easing.RoughEase\",function(e){e=e||{};for(var i,s,r,n,a,o,h=e.taper||\"none\",l=[],_=0,u=0|(e.points||20),p=u,f=e.randomize!==!1,m=e.clamp===!0,d=e.template instanceof t?e.template:null,g=\"number\"==typeof e.strength?.4*e.strength:.4;--p>-1;)i=f?Math.random():1/u*p,s=d?d.getRatio(i):i,\"none\"===h?r=g:\"out\"===h?(n=1-i,r=n*n*g):\"in\"===h?r=i*i*g:.5>i?(n=2*i,r=.5*n*n*g):(n=2*(1-i),r=.5*n*n*g),f?s+=Math.random()*r-.5*r:p%2?s+=.5*r:s-=.5*r,m&&(s>1?s=1:0>s&&(s=0)),l[_++]={x:i,y:s};for(l.sort(function(t,e){return t.x-e.x}),o=new c(1,1,null),p=u;--p>-1;)a=l[p],o=new c(a.x,a.y,o);this._prev=new c(0,0,0!==o.t?o:o.next)},!0),d=i.prototype=new t,d.constructor=i,d.getRatio=function(t){var e=this._prev;if(t>e.t){for(;e.next&&t>=e.t;)e=e.next;e=e.prev}else for(;e.prev&&e.t>=t;)e=e.prev;return this._prev=e,e.v+(t-e.t)/e.gap*e.c},d.config=function(t){return new i(t)},i.ease=new i,u(\"Bounce\",l(\"BounceOut\",function(t){return 1/2.75>t?7.5625*t*t:2/2.75>t?7.5625*(t-=1.5/2.75)*t+.75:2.5/2.75>t?7.5625*(t-=2.25/2.75)*t+.9375:7.5625*(t-=2.625/2.75)*t+.984375}),l(\"BounceIn\",function(t){return 1/2.75>(t=1-t)?1-7.5625*t*t:2/2.75>t?1-(7.5625*(t-=1.5/2.75)*t+.75):2.5/2.75>t?1-(7.5625*(t-=2.25/2.75)*t+.9375):1-(7.5625*(t-=2.625/2.75)*t+.984375)}),l(\"BounceInOut\",function(t){var e=.5>t;return t=e?1-2*t:2*t-1,t=1/2.75>t?7.5625*t*t:2/2.75>t?7.5625*(t-=1.5/2.75)*t+.75:2.5/2.75>t?7.5625*(t-=2.25/2.75)*t+.9375:7.5625*(t-=2.625/2.75)*t+.984375,e?.5*(1-t):.5*t+.5})),u(\"Circ\",l(\"CircOut\",function(t){return Math.sqrt(1-(t-=1)*t)}),l(\"CircIn\",function(t){return-(Math.sqrt(1-t*t)-1)}),l(\"CircInOut\",function(t){return 1>(t*=2)?-.5*(Math.sqrt(1-t*t)-1):.5*(Math.sqrt(1-(t-=2)*t)+1)})),s=function(e,i,s){var r=h(\"easing.\"+e,function(t,e){this._p1=t||1,this._p2=e||s,this._p3=this._p2/a*(Math.asin(1/this._p1)||0)},!0),n=r.prototype=new t;return n.constructor=r,n.getRatio=i,n.config=function(t,e){return new r(t,e)},r},u(\"Elastic\",s(\"ElasticOut\",function(t){return this._p1*Math.pow(2,-10*t)*Math.sin((t-this._p3)*a/this._p2)+1},.3),s(\"ElasticIn\",function(t){return-(this._p1*Math.pow(2,10*(t-=1))*Math.sin((t-this._p3)*a/this._p2))},.3),s(\"ElasticInOut\",function(t){return 1>(t*=2)?-.5*this._p1*Math.pow(2,10*(t-=1))*Math.sin((t-this._p3)*a/this._p2):.5*this._p1*Math.pow(2,-10*(t-=1))*Math.sin((t-this._p3)*a/this._p2)+1},.45)),u(\"Expo\",l(\"ExpoOut\",function(t){return 1-Math.pow(2,-10*t)}),l(\"ExpoIn\",function(t){return Math.pow(2,10*(t-1))-.001}),l(\"ExpoInOut\",function(t){return 1>(t*=2)?.5*Math.pow(2,10*(t-1)):.5*(2-Math.pow(2,-10*(t-1)))})),u(\"Sine\",l(\"SineOut\",function(t){return Math.sin(t*o)}),l(\"SineIn\",function(t){return-Math.cos(t*o)+1}),l(\"SineInOut\",function(t){return-.5*(Math.cos(Math.PI*t)-1)})),h(\"easing.EaseLookup\",{find:function(e){return t.map[e]}},!0),_(r.SlowMo,\"SlowMo\",\"ease,\"),_(i,\"RoughEase\",\"ease,\"),_(e,\"SteppedEase\",\"ease,\"),f},!0)}),_gsScope._gsDefine&&_gsScope._gsQueue.pop()(); </script>"
  );    
}


String Script3(){
  return String(
      "<script>!function () { function e() { h = window.innerWidth, u = window.innerHeight, w = { x: h / 2, y: u / 2 }, v = document.getElementById(\"large-header\"), v.style.height = u + \"px\", f = document.getElementById(\"demo-canvas\"), f.width = h, f.height = u, m = f.getContext(\"2d\"), g = []; for (var e = 0; h > e; e += h / 20) for (var t = 0; u > t; t += u / 20) { var n = e + Math.random() * h / 20, o = t + Math.random() * u / 20, i = { x: n, originX: n, y: o, originY: o }; g.push(i) } for (var a = 0; a < g.length; a++) { for (var r = [], c = g[a], l = 0; l < g.length; l++) { var y = g[l]; if (c != y) { for (var p = !1, x = 0; 5 > x; x++) p || void 0 == r[x] && (r[x] = y, p = !0); for (var x = 0; 5 > x; x++) p || s(c, y) < s(c, r[x]) && (r[x] = y, p = !0) } } c.closest = r } for (var a in g) { var M = new d(g[a], 2 + 2 * Math.random(), \"rgba(255,255,255,0.3)\"); g[a].circle = M } } function t() { \"ontouchstart\" in window || window.addEventListener(\"mousemove\", n), window.addEventListener(\"scroll\", o), window.addEventListener(\"resize\", i) } function n(e) { var t = posy = 0; e.pageX || e.pageY ? (t = e.pageX, posy = e.pageY) : (e.clientX || e.clientY) && (t = e.clientX + document.body.scrollLeft + document.documentElement.scrollLeft, posy = e.clientY + document.body.scrollTop + document.documentElement.scrollTop), w.x = t, w.y = posy } function o() { y = document.body.scrollTop > u ? !1 : !0 } function i() { h = window.innerWidth, u = window.innerHeight, v.style.height = u + \"px\", f.width = h, f.height = u } function a() { r(); for (var e in g) c(g[e]) } function r() { if (y) { m.clearRect(0, 0, h, u); for (var e in g) Math.abs(s(w, g[e])) < 4e3 ? (g[e].active = .3, g[e].circle.active = .6) : Math.abs(s(w, g[e])) < 2e4 ? (g[e].active = .1, g[e].circle.active = .3) : Math.abs(s(w, g[e])) < 4e4 ? (g[e].active = .02, g[e].circle.active = .1) : (g[e].active = 0, g[e].circle.active = 0), l(g[e]), g[e].circle.draw() } requestAnimationFrame(r) } function c(e) { TweenLite.to(e, 1 + 1 * Math.random(), { x: e.originX - 50 + 100 * Math.random(), y: e.originY - 50 + 100 * Math.random(), ease: Circ.easeInOut, onComplete: function () { c(e) } }) } function l(e) { if (e.active) for (var t in e.closest) m.beginPath(), m.moveTo(e.x, e.y), m.lineTo(e.closest[t].x, e.closest[t].y), m.strokeStyle = \"rgba(156,217,249,\" + e.active + \")\", m.stroke() } function d(e, t, n) { var o = this; !function () { o.pos = e || null, o.radius = t || null, o.color = n || null }(), this.draw = function () { o.active && (m.beginPath(), m.arc(o.pos.x, o.pos.y, o.radius, 0, 2 * Math.PI, !1), m.fillStyle = \"rgba(156,217,249,\" + o.active + \")\", m.fill()) } } function s(e, t) { return Math.pow(e.x - t.x, 2) + Math.pow(e.y - t.y, 2) } var h, u, v, f, m, g, w, y = !0; e(), a(), t() }();</script>"
    );    
}

