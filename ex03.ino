#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

#define PIN D4         // GPIO2
#define NUMPIXELS 64   // 8x8 matrix

const char* ssid = "Tenda_A97D90";
const char* password = "earlyduty966";

ESP8266WebServer server(80);
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Track on/off state
bool ledStates[NUMPIXELS] = {false};

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/animate", handleAnimate);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head><title>WS2812 Matrix</title></head><body>";
  html += "<h2>Click LED to toggle</h2><table>";

  for (int y = 0; y < 8; y++) {
    html += "<tr>";
    for (int x = 0; x < 8; x++) {
      int index = y * 8 + x;
      String color = ledStates[index] ? "#00FF00" : "#444444";
      html += "<td><a href='/toggle?i=" + String(index) + "'>";
      html += "<div style='width:20px;height:20px;background:" + color + ";'></div>";
      html += "</a></td>";
    }
    html += "</tr>";
  }

  html += "</table><br><a href='/animate'>Run Animation</a></body></html>";
  server.send(200, "text/html", html);
}

void handleToggle() {
  if (server.hasArg("i")) {
    int i = server.arg("i").toInt();
    if (i >= 0 && i < NUMPIXELS) {
      ledStates[i] = !ledStates[i];
      strip.setPixelColor(i, ledStates[i] ? strip.Color(0, 255, 0) : 0);
      strip.show();
    }
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleAnimate() {
  const uint64_t frames[] = {
    0b0001100000011000000000000001100000011000000000000001100000011000,
    0b0010010000100100000000000001100000011000000000000001100000011000,
    0b0010010000100100000000000001100000011000000010000001000000010000,
    0b0010010000100100000000000001100000011000000001000000010000010000
  };

  const int frameCount = sizeof(frames) / sizeof(frames[0]);

  for (int repeat = 0; repeat < 3; repeat++) {
    for (int f = 0; f < frameCount; f++) {
      uint64_t frame = frames[f];
      for (int i = 0; i < NUMPIXELS; i++) {
        bool isOn = (frame >> (63 - i)) & 1;
        strip.setPixelColor(i, isOn ? strip.Color(255, 100, 0) : 0);
      }
      strip.show();
      delay(300);
    }
  }

  // Turn off all LEDs after animation
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, 0);
    ledStates[i] = false;  // <-- this resets the toggle state
  }
  strip.show();

  server.sendHeader("Location", "/");
  server.send(303);
}

