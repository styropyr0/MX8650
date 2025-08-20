#include <mx8650.h>

// SCLK: 13, SDIO: 11
MX8650 mouseController(13, 11);

void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing MX8650...");
    mouseController.begin();
}

void loop()
{
    Serial.print("Motion Status: " + mouseController.getMotionStatus());
    Serial.print("Delta X: " + String(mouseController.getDeltaX()) + "\t");
    Serial.println("Delta Y: " + String(mouseController.getDeltaY()));
    delay(100);
}
