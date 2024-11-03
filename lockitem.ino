#include <WiFi.h>
#include <TinyGPS++.h>
#include <RTClib.h>

#define NTP_SERVER     "pool.ntp.org"
int UTC_OFFSET  = 8 * 3600;
#define UTC_OFFSET_DST 8

TinyGPSPlus gps;

char ssid[] = "Wokwi-GUEST";   // Wokwi Wifi 
char pass[] = "";   //Blank Password
WiFiClient  client;
RTC_DS3231 rtc;


void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // Use hardware serial for GPS module (RX=16, TX=17)
  Serial.println("GPS Start");

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}

void loop() {
  while (Serial2.available() > 0) {
    gps.encode(Serial2.read());
    if (gps.location.isValid()) {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
      DateTime now = rtc.now();
      Serial.print("Date: ");
      Serial.println(now.timestamp());
      delay(1000);
    }
  }
}
