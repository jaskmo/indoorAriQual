#include <Arduino.h>
#include "Helpers/AM2320.h"
#include "Helpers/MQTT.h"
#include "Helpers/CCS811.h"


void setup() {
  Serial.begin(9600);
  setup_AM2320();
  setup_CCS811();
  setup_wifi();
  // Setup MQTT server (Server spec. in MQTT.h)
  client.setServer(mqtt_server, 18165);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // To debug
  Serial.print("Temp: "); Serial.println(am2320.readTemperature());
  Serial.print("Hum: "); Serial.println(am2320.readHumidity());

// Updates message 'meta' info (Probably not nessesary)
  long now = millis();
  if (now - lastMsg > 10000) {
    lastMsg = now;
//     ++value;
    snprintf (temp_msg, 75, "%lf", am2320.readTemperature());
    // To debug
    Serial.print("Publish message: ");
    Serial.println(temp_msg);

    client.publish("Temp", temp_msg);

    snprintf (humid_msg, 75, "%lf", am2320.readHumidity());
    // To debug
    Serial.print("Publish message: ");
    Serial.println(humid_msg);

    client.publish("Humid", humid_msg);

    // CCS811 data
    if(ccs.available()){
      if(!ccs.readData()){
        // CO2 data
        snprintf (co2_msg, 75, "%lf", ccs.geteCO2());
        // To debug
        Serial.print("Publish message: ");
        Serial.println(co2_msg);

        client.publish("eCo2", co2_msg);

        //TVOC ppm data
        snprintf (TVOC_msg, 75, "%lf", ccs.getTVOC());
        // To debug
        Serial.print("Publish message: ");
        Serial.println(TVOC_msg);

        client.publish("ppm TVOC", TVOC_msg);
      }
      else{
        Serial.println("ERROR!");
      }
    }

  }
  delay(2000);
}
