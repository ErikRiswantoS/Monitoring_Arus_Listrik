#include <ESP8266WiFi.h>
#include <PZEM004Tv30.h>

// Instalasi objek untuk PZEM
PZEM004Tv30 pzem(12, 13); // 12=D6 (Rx), 13=D7 (Tx)

WiFiClient client;
String apikey = "V8D7D40BDX2GH8PD";
const char* ssid = "Redmi Note 8";
const char* password = "sukabumidapo";
const char* server = "api.thingspeak.com";
unsigned long channelNumber = 2583855;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" connected");
}

void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float pf = pzem.pf();

  if (client.connect(server, 80)) {
    String postStr = apikey;
    postStr += "&field1=";
    postStr += String(voltage);
    postStr += "&field2=";
    postStr += String(current);
    postStr += "&field3=";
    postStr += String(power);
    postStr += "&field4=";
    postStr += String(pf);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apikey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
    Serial.print("Current: "); Serial.print(current); Serial.println(" A");
    Serial.print("Power: "); Serial.print(power); Serial.println(" W");
    Serial.print("Pf: "); Serial.println(pf);
    Serial.println(WiFi.localIP());
  }

  Serial.println();
  delay(20000); // Tunggu 20 detik untuk update berikutnya
}
