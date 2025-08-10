#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define ssid "WebServer"
#define password "12345678"


#define ledPin1 D0  
#define ledPin2 D3   
#define ledPin3 D6   

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);

bool ledStatus1 = LOW;
bool ledStatus2 = LOW;
bool ledStatus3 = LOW;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(1000);

  server.on("/", handle_onConnect);

  // LED 1 routes
  server.on("/led1on", [](){ ledStatus1 = HIGH; server.send(200, "text/html", getHTML()); });
  server.on("/led1off", [](){ ledStatus1 = LOW; server.send(200, "text/html", getHTML()); });

  // LED 2 routes
  server.on("/led2on", [](){ ledStatus2 = HIGH; server.send(200, "text/html", getHTML()); });
  server.on("/led2off", [](){ ledStatus2 = LOW; server.send(200, "text/html", getHTML()); });

  // LED 3 routes
  server.on("/led3on", [](){ ledStatus3 = HIGH; server.send(200, "text/html", getHTML()); });
  server.on("/led3off", [](){ ledStatus3 = LOW; server.send(200, "text/html", getHTML()); });

  server.onNotFound(handle_notFound);
  server.begin();
  
  Serial.println("....HTTP Server Started....");
}

void loop() {
  server.handleClient();
  digitalWrite(ledPin1, ledStatus1 ? HIGH : LOW);
  digitalWrite(ledPin2, ledStatus2 ? HIGH : LOW);
  digitalWrite(ledPin3, ledStatus3 ? HIGH : LOW);
}

String getHTML() {
  String htmlcode = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0,user-scale=1.0,user-scalable=on">
<title>LED Control</title>
<style>
  body {
    font-family: Arial, sans-serif;
    background: linear-gradient(120deg, #89f7fe, #66a6ff);
    text-align: center;
    color: #333;
    margin: 0;
    padding: 0;
  }
  h1 {
    margin-top: 30px;
    font-size: 2rem;
  }
  h3 {
    font-weight: normal;
    margin-bottom: 20px;
  }
  p {
    font-size: 1.2rem;
    margin: 15px 0;
  }
  .btn {
    display: inline-block;
    background: #4CAF50;
    color: white;
    padding: 10px 20px;
    margin: 8px;
    border-radius: 8px;
    text-decoration: none;
    font-size: 0.95rem;
    transition: background 0.3s ease;
  }
  .btn:hover {
    background: #45a049;
  }
  .btn-off {
    background: #f44336;
  }
  .btn-off:hover {
    background: #da190b;
  }
  .led-block {
    border: 2px solid rgba(255,255,255,0.4);
    border-radius: 12px;
    padding: 15px;
    margin: 15px auto;
    width: 260px;
    background: rgba(255,255,255,0.2);
  }
</style>
</head>
<body>
  <h1>ESP8266 WEB Server</h1>
  <h3>Control Three LEDs via Access Point</h3>
)rawliteral";

  // LED 1
  htmlcode += "<div class='led-block'><p>LED 1 Status: <strong>";
  htmlcode += (ledStatus1 ? "ON" : "OFF");
  htmlcode += "</strong></p>";
  htmlcode += (ledStatus1 ? "<a href='/led1off' class='btn btn-off'>Turn OFF</a>" : "<a href='/led1on' class='btn'>Turn ON</a>");
  htmlcode += "</div>";

  // LED 2
  htmlcode += "<div class='led-block'><p>LED 2 Status: <strong>";
  htmlcode += (ledStatus2 ? "ON" : "OFF");
  htmlcode += "</strong></p>";
  htmlcode += (ledStatus2 ? "<a href='/led2off' class='btn btn-off'>Turn OFF</a>" : "<a href='/led2on' class='btn'>Turn ON</a>");
  htmlcode += "</div>";

  // LED 3
  htmlcode += "<div class='led-block'><p>LED 3 Status: <strong>";
  htmlcode += (ledStatus3 ? "ON" : "OFF");
  htmlcode += "</strong></p>";
  htmlcode += (ledStatus3 ? "<a href='/led3off' class='btn btn-off'>Turn OFF</a>" : "<a href='/led3on' class='btn'>Turn ON</a>");
  htmlcode += "</div>";

  htmlcode += R"rawliteral(
</body>
</html>
)rawliteral";

  return htmlcode;
}

void handle_onConnect() {
  Serial.println("Client connected");
  server.send(200, "text/html", getHTML());
}

void handle_notFound() {
  server.send(404, "text/plain", "Not Found");
}
