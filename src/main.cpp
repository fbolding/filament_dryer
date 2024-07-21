
#include <Arduino.h>
#include "motor.h"
#include "dryerAPI.h"
#include "tftUI.h"
#include "webUI.h"

dryerAPI dryerControl;
tftUI tftScreen;
webUI webInterface;

void setup()
{
    Serial.begin( 115200 );
    tftScreen.setup(&dryerControl);
}

void loop()
{
    tftScreen.update();

}
