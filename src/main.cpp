#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AutoConnect.h>



ESP8266WebServer Server;

AutoConnect       Portal(Server);
AutoConnectConfig Config;       // Enable autoReconnect supported on v0.9.4


void rootPage() {
  String  content =
    "<html>"
    "<head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "</head>"
    "<body>"
    "<h2 align=\"center\" style=\"color:blue;margin:20px;\">Bitcoin Ticker</h2>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Version 1.2</h3>"
    "<p style=\"text-align:center;\">info@zurzy.shop</p>"
    "<p style=\"text-align:center;\"><a href=\"../_ac\">Einstellungen aendern</a></p>"
    "<p></p><p style=\"padding-top:15px;text-align:center\">" AUTOCONNECT_LINK(COG_24) "</p>"
    "</body>"
    "</html>";

   Server.send(200, "text/html", content);

}


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();


  // Enable saved past credential by autoReconnect option,
  // even once it is disconnected.
  Config.autoReconnect = true;
  Config.hostName = "esp32-01";
  
  Portal.config(Config);

  Server.on("/", rootPage);


   Serial.println("Creating portal and trying to connect...");
  // Establish a connection with an autoReconnect option.
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
    Serial.println(WiFi.hostname());
  }

}

void loop() {
  Portal.handleClient();


}