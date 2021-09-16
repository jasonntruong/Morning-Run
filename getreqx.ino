#include <WiFi.h>

WiFiClient client;

const int LEDPIN = 22;
const int PushButton = 15;

const char* ssid = "YOUR WIFI NAME"; //not going to release this...
const char* password = "WIFI PASSWORD";
const char* host = "HOST WEBSITE";
const String url = "/morningrun.php?REQ_ALARM=X"; //X is a num from 1-4, since each of the 4 ESP32s sends a different REQ_ALARM GET REQUEST VALUE from 1-4, so change X to the appropriate num

IPAddress local_IP(xxx,xxx,xxx,x); //not going to release this...
IPAddress gateway(xxx,xxx,xx,x);
IPAddress subnet(xxx,xxx,xxx,x);
IPAddress primaryDNS(x,x,x,x);
IPAddress secondaryDNS(x,x,x,x);

void setup() {
  Serial.begin(115200);

  pinMode(LEDPIN, OUTPUT);
  pinMode(PushButton, INPUT_PULLUP);

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Failed to connect");
  }
  
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  delay(5000);
  
  if (!client.connect(host, 80)) {
    //if cannot connect to the WiFi, try again
    Serial.println("connection failed");
    setup();
  }
  
  if (client.connect(host, 80)) {
     Serial.println("");
     Serial.println("Wifi connected!");
     Serial.print("Gateway IP: ");
     Serial.println(WiFi.gatewayIP());
     digitalWrite(LEDPIN, HIGH);
     delay(1000);
     digitalWrite(LEDPIN, LOW);
  }

  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

}

void loop() {
  int PushButtonState = digitalRead(PushButton);

  if (PushButtonState == LOW) {
    //when button pressed (using INPUT_PULLUP instead of INPUT to initialize the button pins oddly switched the button pressed state from HIGH to LOW)
    
    digitalWrite(LEDPIN, HIGH);

    //send the GET Request value X (1-4)
    client.println(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: REQ sent\r\n\r\n");
    Serial.println("SENT X");
    client.stop();  //closes connections. if not, causes DNS error on Web browsers
    delay(2000);
    digitalWrite(LEDPIN, LOW);

    //after sending the GET Request, rerun setup() to reconnect to the WiFi and web server/Rasp Pi
    setup();
  }

  if (!client.connect(host, 80)) {
    Serial.println("connection failed");

    //reconnect if connection lost/failed
    setup();
  }
}
