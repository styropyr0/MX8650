#include "mx8650.h"

// SCLK: 13, SDIO: 11
MX8650 mouseController(13, 11);

void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing MX8650...");
}

void loop()
{
    Serial.println("Motion Status: " + mouseController.getMotionStatus());
    Serial.print("Delta X: " + mouseController.getDeltaX() + "\t");
    Serial.println("Delta Y: " + mouseController.getDeltaY());
}