// Flag's Block 產生的草稿碼

#include <ESP8266WiFi.h>
#include <FlagURLEncode.h>
#include <FlagHTTPClient.h>

String ifttt;
boolean mh;
FlagHTTPClient _httpClient;

int _httpGET(String url) {
  _httpClient.end();
  _httpClient.begin(url);
  return _httpClient.GET();
}


// setup() 會先被執行且只會執行一次
void setup() {
  Serial.begin(9600);
  pinMode(D1, INPUT);
  pinMode(D5, OUTPUT);
  pinMode(D2, OUTPUT);

  Serial.println((String(u8"MH senser begin to detect ...") + String(u8"================================")));
  Serial.println(u8"... WiFi start to connect ...");
  WiFi.begin(u8"我有網路你沒有", u8"aabbccddee");
  while (!(WiFi.status() == WL_CONNECTED)) {
    delay(1000);
  }
  Serial.println((String(u8"IP adderss : ") + String((WiFi.localIP().toString()))));

}

// loop() 裡面的程式會不斷重複執行
void loop() {
  ifttt = String(u8"https://maker.ifttt.com/trigger/Opened/with/key/fpz9FtnMLAsQYoD2UPTwHtjSAMvPGiDvUnNt8Phd4iV") + String(u8"value1=") + String(urlencode(String(u8"抽屜被打開了"))) + String(u8"&") + String(u8"value2=") + String(urlencode(String(u8"快來人!"))) + String(u8"&") + String(u8"value3=") + String(urlencode(String(u8"Go Go Go")));
  mh = digitalRead(D1);
  Serial.println((String(u8"MH status = ") + String(mh)));
  while (digitalRead(D1) == HIGH) {
    digitalWrite(D5, HIGH);
    tone(D2,2500,300);
    delay(300);
    digitalWrite(D5, LOW);
    tone(D2,1250,300);
    delay(300);
    if (_httpGET(ifttt) >= 0) {
      delay(10000);
    }
  }

}
