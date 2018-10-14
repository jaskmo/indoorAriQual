#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"

Adafruit_AM2320 am2320 = Adafruit_AM2320();

void setup_AM2320() {
  while (!Serial) {
    delay(10); // hang out until serial port opens
  }
  am2320.begin();
}
