
/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-websocket-server-arduino/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include "SPIFFS.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>


// Replace with your network credentials
const char* ssid = "jinyistudio";
const char* password = "25433692";

bool ledState = 0;
const int ledPin = 2;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");



void notifyClients() {
  ws.textAll(String(ledState));
}
// {"prop":"ServerTime","etype":"runFunction","value":[51]}
StaticJsonDocument<256> doc;


void updateVal()
{  
   JsonDocument doc1;
  doc1["etype"] = "runFunction";
  doc1["prop"] = "updateVal";
  
  for (JsonPair kv : doc["params"].as<JsonObject>()) {
    if(strcmp(kv.key().c_str(),"sw0")==0)
      doc1["value"][0]["led0"] = kv.value();  
    else if(strcmp(kv.key().c_str(),"sw1")==0)
      doc1["value"][0]["led1"] = kv.value();
    else if(strcmp(kv.key().c_str(),"sw2")==0)
      doc1["value"][0]["led2"] = kv.value();
    else if(strcmp(kv.key().c_str(),"sw3")==0)
      doc1["value"][0]["led3"] = kv.value();
    else if(strcmp(kv.key().c_str(),"sw4")==0)
      doc1["value"][0]["led4"] = kv.value();
    else if(strcmp(kv.key().c_str(),"sw5")==0)
      doc1["value"][0]["led5"] = kv.value();
    else if(strcmp(kv.key().c_str(),"sw6")==0)
      doc1["value"][0]["led6"] = kv.value();
    else if(strcmp(kv.key().c_str(),"sw7")==0)
      doc1["value"][0]["led7"] = kv.value();
    else
      return;
  }
  
  String outs;
  doc1.shrinkToFit();  // optional
  serializeJson(doc1, outs);     
  
  ws.textAll(outs);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {    
    // Deserialize the JSON document
    data[len]=0;
    Serial.printf("%s\n",data);
    DeserializationError error = deserializeJson(doc, data);
    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }    
    // type: "event", event: eventName, params: parameters}
    const char* type1 = doc["type"];
    const char* event1 = doc["event"];
    
    if(strcmp(type1,"event")==0) {
      if(strcmp(event1,"updateVal")==0) {  
        Serial.printf("updateVal\n");  
        updateVal(); 
      }
    }
    // Serial.printf("prop: %s value: %s\n",prop,val?"true":"false");  
    
  }
}



void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      Serial.printf("WS_EVT_DATA: %s data: %s len:%d\n",client->remoteIP().toString().c_str(),data,len);
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("loading index.html");
    request->send(SPIFFS, "/index.html", String(), false);
  });
  
   //server everything else statically
  server.serveStatic("/", SPIFFS, "/");
  
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "not Found!");
  });
  
  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();
  digitalWrite(ledPin, ledState);
}
