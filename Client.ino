#include <ESP8266WiFi.h>
 
const char* ssid     = "SSID";
const char* password = "SIFRE";
 
const char* host = "www.ereneris.net";
 
void setup() {
  Serial.begin(115200); // BaundRate ESP8266 hangisiyse onu ayarla
  delay(100);
 
  // Bağlantı Yapılıyor
 
  Serial.println();
  Serial.println();
  Serial.print("Baglaniyor... ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi Baglandi");  
  Serial.println("IP Adres: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}
 
int value = 0;
 
void loop() {
  delay(5000);
  ++value;
 
  Serial.print("Baglanti Yapiliyor:");
  Serial.println(host);
  
  
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("=>Baglanti Yapilamadi");
    return;
  }
  

  String url = "/kayit.php";
  Serial.print("Get Yapilacak Sayfa: ");
  Serial.println(url);
  
  // Bağlantı Parcacığı oluşturulıupr
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Sayfa bize cevap donmuşsse o okunuyor.
  // Burda kayır duurmuna olumlu olumsuz veya lambanın duurmunu öğrenip kullanıcıya gosterebilirsin. Web sayfasına ne yazarsan o gelir. onu ayıklarsın.
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("Baglanti Kapatıldi");
}