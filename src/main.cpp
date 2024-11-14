#include <WiFi.h>
#include <RTClib.h>
#include <TinyGPS++.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>

/* 1. Define the Wi-Fi credentials */
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "API_KEY"

/* 3. Define the RTDB URL */
#define DATABASE_URL "DATABASE_URL" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "USER_EMAIL"

#define USER_PASSWORD "USER_PASSWORD"

#define UID "SENSOR_UID"

void connectFirebase();

void sendJson();

void connectWifi();

void initRTC();

void printData();

// wifi client
WiFiClient wifi;


// Define Firebase Data object
FirebaseData bdo;

FirebaseAuth auth;
FirebaseConfig config;

// rtc chip
RTC_DS3231 rtc;
// gps decoder
TinyGPSPlus gps;

String path = "/positions/";

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, 16, 17); // Use hardware serial for GPS module (RX=16, TX=17)
    Serial.println("GPS Start");

    connectWifi();
    initRTC();
    connectFirebase();
    path += UID;
}

void loop() {
    if (!Firebase.ready())
        return;

    if (Serial2.available()) {
        gps.encode(Serial2.read());
        if (gps.location.isValid()) {
            // printData();
            sendJson();
            delay(1000);
        }
    } else if (millis() > 5000 && gps.charsProcessed() < 10)
        Serial.println(F("No GPS data received: Waiting for it."));
}

void connectWifi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }

    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}

void initRTC() {
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
    }

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void printData() {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    const DateTime now = rtc.now();
    Serial.print("Date: ");
    Serial.println(now.timestamp());
    Serial.println();
}


void connectFirebase() {
    Serial.printf("Firebase Client v%s", FIREBASE_CLIENT_VERSION);
    Serial.println();

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    Firebase.begin(&config, &auth);

    Firebase.reconnectWiFi(true);

    Firebase.setDoubleDigits(5);
    Serial.println("Firebase Client Connected.");
    Serial.println();
}

void sendJson() {
    FirebaseJson json;
    const DateTime now = rtc.now();
    json.set("date", now.timestamp());
    json.set("latitude", gps.location.lat());
    json.set("longitude", gps.location.lng());

    String data;
    json.toString(data);

    Serial.printf("Sending position... %s ", data.c_str());

    Serial.print(Firebase.push(bdo, path, json) ? "ok" : bdo.errorReason().c_str());
    Serial.println();
}
