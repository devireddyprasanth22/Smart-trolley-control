#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>  // LittleFS library for file handling

#define SERIAL_BAUD 115200  // Match with your Serial Monitor

ESP8266WebServer server(80);  // Create a web server on port 80

String serialData = "";

// Static IP for your ESP
const IPAddress serverIPAddress(10, 0, 0, 7);

void setup(void) {
  // Start Serial
  Serial.begin(SERIAL_BAUD);

  // Initialize LittleFS
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount LittleFS!");
    return;
  }

  // Start WiFi in AP mode with a static IP
  WiFi.softAPConfig(serverIPAddress, serverIPAddress, IPAddress(255, 255, 255, 0));
  WiFi.softAP("XC4411 Dual Board");

  // Serve the root index.html
  server.on("/", []() {
    handleFileRequest("/index.html");
  });

  // Serve the CSS file located in data/assets/
  server.on("/assets/index-BphnNmrb.css", []() {
    handleFileRequest("./assets/index-BphnNmrb.css");
  });
  
    // Serve the js file located in data/assets/
  server.on("/assets/index-os2gvVtR.js", []() {
    handleFileRequest("./assets/index-os2gvVtR.js");
  });

  // Serve the svg located in /
  server.on("/triangle.svg", []() {
    handleFileRequest("./triangle.svg");
  });

    // Serve the svg located in /
  server.on("/circle.svg", []() {
    handleFileRequest("./circle.svg");
  });

  // Serve the svg located in /
  server.on("/vite.svg", []() {
    handleFileRequest("/vite.svg");
  });
  
  // Endpoint for serial data reading
  server.on("/reading", []() {
    Serial.println(serialData);
    server.send(200, "text/plain", serialData);
  });

    
  // Endpoint for forward
  server.on("/direction/forward", []() {
    Serial.write("[DIRECTION] forward");
    server.send(200, "text/plain", "forward");
  });

    // Endpoint for backwards
  server.on("/direction/backwards", []() {
    Serial.write("[DIRECTION] backward");
    server.send(200, "text/plain", "backward");
  });

      // Endpoint for left
  server.on("/direction/left", []() {
    Serial.write("[DIRECTION] left");
    server.send(200, "text/plain", "left");
  });

        // Endpoint for right
  server.on("/direction/right", []() {
     Serial.write("[DIRECTION] right");
    server.send(200, "text/plain", "right");
  });

        // Endpoint for stop
  server.on("/direction/stop", []() {
     Serial.write("[DIRECTION] stop");
    server.send(200, "text/plain", "stop");
  });
  // Handle undefined requests
  server.onNotFound(handleNotFound);

  // Start the server
  server.begin();
}

void loop(void) {
  // Read incoming serial data
  while (Serial.available()) {
    char x = Serial.read();
    if (x == '\r') continue;
    serialData += x;
  }

  // Handle incoming client requests
  server.handleClient();
}

// Function to handle file requests from LittleFS
void handleFileRequest(String path) {
  if (path.endsWith("/")) {
    path += "index.html";  // Serve index.html if root path is requested
  }

  String contentType = getContentType(path);  // Determine content type

  if (LittleFS.exists(path)) {
    File file = LittleFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
  } else {
    server.send(404, "text/plain", "File Not Found");
  }
}

// Determine the content type (HTML, CSS, etc.)
String getContentType(String filename) {
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".svg")) return "image/svg+xml";
  return "text/plain";
}

// Handle 404 (file not found) errors
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
