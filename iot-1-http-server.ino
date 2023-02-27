#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED1 16  // Pemilihan Pin D0
#define LED2 5    // Pemilihan Pin D1

const char* ssid = "SET_SSID_HERE";       // Nama SSID AP/Hotspot
const char* password = "SET_PASSWORD_HERE";    // Password Wifi

ESP8266WebServer server(80);      //Menyatakan Webserver pada port 80
String webpage;

void setup() {  //Pengaturan Pin
  Serial.begin(115200);
  delay(10);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Connect ke WiFi
  Serial.println();
  Serial.print("Configuring access point...");

  // Mengatur WiFi 
  WiFi.mode(WIFI_STA);                      // Mode Station
  // WiFi.mode(WIFI_AP);                      // Mode AP
  WiFi.begin(ssid, password);               // Mencocokan SSID dan Password
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print status Connect 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Serial.println(WiFi.softAPIP());

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  
  // Isi dari Webpage 
  webpage += "<h1> Web Control LED ESP8266</h1>";
  webpage += "LED 1 : ";
  webpage += "<a href=\"LED1ON\"\"><button>ON</button></a><a href=\"LED1OFF\"\"><button>OFF</button></a><br>";
  webpage += "LED 2 : ";
  webpage += "<a href=\"LED2ON\"\"><button>ON</button></a><a href=\"LED2OFF\"\"><button>OFF</button></a><br>";
  webpage += "LED BUILTIN : ";
  webpage += "<a href=\"LED_BUILTINON\"\"><button>ON</button></a><a href=\"LED_BUILTINOFF\"\"><button>OFF</button></a></br>";

  // Membuat file webpage 
  server.on("/", []() {
    server.send(200, "text/html", webpage);
  });

  // Bagian ini untuk merespon perintah yang masuk 
  server.on("/LED1ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, HIGH);
  });
  server.on("/LED2ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2, HIGH);
  });
  server.on("/LED_BUILTINON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED_BUILTIN, HIGH);
  });
  server.on("/LED1OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, LOW);
  });
  server.on("/LED2OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2, LOW);
  });
  server.on("/LED_BUILTINOFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED_BUILTIN, LOW);
  });

  server.begin();
  Serial.println("Server dijalankan");
}

void loop() {  //Perulangan Program
  server.handleClient();
}
