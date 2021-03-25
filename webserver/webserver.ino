#include <ESP8266WiFi.h>

WiFiServer server(80);

const char* ssid = "0475c6";
const char* password =  "235196706";

String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED){   
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  
  server.begin();
  
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
}

void loop(){
  WiFiClient client = server.available();

  if(client){
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;
    while(client.connected() && currentTime - previousTime <= timeoutTime){
      currentTime = millis();         
      if(client.available()){
        char c = client.read();
        header += c;
        if(c == '\n'){
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if(header.indexOf("GET /O") >= 0){
              Serial.print("O");
            }else if(header.indexOf("GET /R") >= 0){
              Serial.print("R");
            }else if(header.indexOf("GET /L") >= 0){
              Serial.print("L");
            }else if(header.indexOf("GET /U") >= 0){
              Serial.print("U");
            }else if(header.indexOf("GET /D") >= 0){
              Serial.print("D");
            }else if(header.indexOf("GET /F") >= 0){
              Serial.print("F");
            }else if(header.indexOf("GET /B") >= 0){
              Serial.print("B");
            }else if(header.indexOf("GET /C") >= 0){
              Serial.print("C");
            }
            
            client.println("<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\" />");
            client.println("<style>body {background-color: black;color: white;}.container .btn {position: static;width: 100px;height: 50px;cursor: pointer;}");
            client.println(".tit {text-align: center;}.ltit {text-align: left;}.mirror{-webkit-transform: scaleX(-1);transform: scaleX(-1);}");
            client.println(".mirro{-webkit-transform: rotate(90deg);-moz-transform: rotate(90deg);-o-transform: rotate(90deg);-ms-transform: rotate(90deg);transform: rotate(90deg);}");
            client.println(".mirr{-webkit-transform: rotate(-90deg);-moz-transform: rotate(-90deg);-o-transform: rotate(-90deg);-ms-transform: rotate(-90deg);transform: rotate(-90deg);}");
            client.println(".righ{float: right;}.lef{float: left;}.up{position: absolute;top: 10%;right: 47%;}.rig{position: absolute;top: 30%;right: 32%;}");
            client.println(".down{position: absolute;top: 50%;right: 47%;}.le{position: absolute;top: 30%;right: 60%;}.tcenter{text-align: center;}");
            client.println(".grab{position: absolute;top: 31%;right: 47%;background-color: #e0331f;}</style></head>");
            
            client.println("<body><p><h1 class=\"tit\">ESP8266 Arm</h1></p><div class=\"container righ\"><h2 class=\"ltit\"></h2>");
            client.println("<a href=\"R\"><input type=\"image\" src=\"https://cdn.discordapp.com/attachments/374955767880613891/805020466821201950/piros-nyil-220x300.png\" name=\"right\" class=\"btn mirror\" id=\"saveForm\" /></a></div>");
            client.println("<div class=\"container lef\"><h2 class=\"ltit\"></h2><a href=\"L\"><input type=\"image\" src=\"https://cdn.discordapp.com/attachments/374955767880613891/805020466821201950/piros-nyil-220x300.png\" name=\"left\" class=\"btn\" id=\"saveForm\" /></a></div>");            
            client.println("<div class=\"container up\"><h2 class=\"ltit tcenter\"></h2><a href=\"U\"><input type=\"image\" src=\"https://pngimg.com/uploads/red_arrow/red_arrow_PNG60.png\" name=\"up\" class=\"btn mirro\" id=\"saveForm\" /></a></div>");
            client.println("<div class=\"container rig\"><a href=\"F\"><input type=\"image\" src=\"https://pngimg.com/uploads/red_arrow/red_arrow_PNG60.png\" name=\"up\" class=\"btn mirror\" id=\"saveForm\" /></a><h2 class=\"ltit tcenter\"></h2></div>");
            client.println("<div class=\"container down\"><a href=\"D\"><input type=\"image\" src=\"https://pngimg.com/uploads/red_arrow/red_arrow_PNG60.png\" name=\"up\" class=\"btn mirr\" id=\"saveForm\" /></a><h2 class=\"ltit tcenter\"></h2></div>");
            client.println("<div class=\"container le\"><a href=\"B\"><input type=\"image\" src=\"https://pngimg.com/uploads/red_arrow/red_arrow_PNG60.png\" name=\"up\" class=\"btn\" id=\"saveForm\" /></a><h2 class=\"ltit tcenter\"></h2></div>");
            client.println("<div class=\"container grab\"><a href=\"C\"><button type=\"button\" class=\"btn grab\"></button></a></div>");
            
            client.println("</body></html>");          
            
            client.println();
            
            break;
          }else{
            currentLine = "";
          }
        }else if(c != '\r'){
          currentLine += c;
        }
      }
    }
    header = "";
    
    client.stop();
    
  }
}
