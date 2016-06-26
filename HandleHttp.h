String Content1(){
    return String(
"<!DOCTYPE html>"
"<html xmlns=\"http://www.w3.org/1999/xhtml\">"
"<head>"
"<title>ESPBotino</title>"
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
".form-select:after { content: '▾'; position: absolute; top: 0; right: 12px; z-index: 1; color: #bbbbbb; line-height: 40px; font-size: 14px;}"
".ie .form-select:after { display: none;}"
"select {  position: relative; background: transparent; background-image: none; display: block; width: 100%; outline: none;  color: #888888;cursor: pointer;  z-index: 2; border: none; padding: 10px 10px 10px 5px; text-indent: 5px; -moz-appearance: none; -webkit-appearance: none;}"
"select[multiple=multiple] { height: auto; border: 1px solid #cbcbcb; border-radius: 3px;  box-shadow: 0 0 1px rgba(0, 0, 0, 0.1), inset 0 0 10px rgba(0, 0, 0, 0.07);-moz-transition: box-shadow 0.2s; -o-transition: box-shadow 0.2s; -webkit-transition: box-shadow 0.2s; transition: box-shadow 0.2s;}"
"select[multiple=multiple]:hover { border-color: #cccccc; box-shadow: 0 0 15px rgba(0, 0, 0, 0.2);}"
"select option[disabled] { color: #eeeeee; text-shadow: none; border: none;}"
"select:-moz-focusring { color: transparent; text-shadow: 0 0 0 #888888;}"
"select::-ms-expand { display: none;}"
".column-5 { position: relative;  top: 40%; left: 50%; margin: -20px 0 0 -150px; width: 300px;}"
".column-6 { position: relative;  top: 45%;  left: 50%;  margin: -20px 0 0 -150px;  width: 300px;}"
".column-7 { position: relative; top: 50%; left: 50%; margin: -20px 0 0 -150px;  width: 300px;}"
".column-8 { position: relative; top: 55%; left: 50%; margin: -20px 0 0 -150px; width: 300px;}"
"</style>"
"</head>" 
  );
}

String Content2(){
  return String(
"<body>"
    "<form method=\"post\" action=\"wifisave\">"
        "<div class=\"column-5\"><h2>ESPBotino WiFi Config :P</h2></div>"
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

