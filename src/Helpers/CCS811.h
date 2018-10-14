#include <Adafruit_CCS811.h>

Adafruit_CCS811 ccs;

void setup_CCS811() {

  if(!ccs.begin()){
    while(1){
      delay(10000);
      Serial.println("Failed to start sensor! Please check your wiring.");
    }
  }
}

// void CCS811_update_data() {
//   if(ccs.available()){
//     float temp = ccs.calculateTemperature();
//     if(!ccs.readData()){
//       Serial.print("eCO2: ");
//       float eCO2 = ccs.geteCO2();
//       Serial.print(eCO2);
//
//       Serial.print(" ppm, TVOC: ");
//       float TVOC = ccs.getTVOC();
//       Serial.print(TVOC);
//     }
//     else{
//       Serial.println("ERROR!");
//       while(1);
//     }
//   }
//   delay(500);
// }
