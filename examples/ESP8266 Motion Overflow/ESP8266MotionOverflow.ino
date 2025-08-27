
#include <mx8650.h>

#define SCLK 14
#define SDIO 12
MX8650 mouseController(SCLK, SDIO);

long x = 0;
long y = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("Initializing...");
    mouseController.begin(DISABLE_SLEEP, DPI_1600, IMG_RATE_HIGHEST);
    mouseController.Log();
}


void loop() {
    uint8_t motionStatus = mouseController.getMotionData(); // Reads 0x02, freezes deltas

    bool motionOccurred = motionStatus & 0x80; // BIT7: Motion
    bool yOverflow      = motionStatus & 0x10; // BIT4: ΔY overflow
    bool xOverflow      = motionStatus & 0x08; // BIT3: ΔX overflow

    if (motionOccurred) {
        int8_t dx = (int8_t)mouseController.getDeltaX();
        int8_t dy = (int8_t)mouseController.getDeltaY();

        // Overflow handling — if overflow bits set, apply max step
        if (xOverflow) dx = (dx > 0) ? INT8_MAX : INT8_MIN;
        if (yOverflow) dy = (dy > 0) ? INT8_MAX : INT8_MIN;

        // Safe accumulation
        if ((dx > 0 && x > INT32_MAX - dx) || (dx < 0 && x < INT32_MIN - dx))
            x = (dx > 0) ? INT32_MAX : INT32_MIN;
        else
            x += dx;

        if ((dy > 0 && y > INT32_MAX - dy) || (dy < 0 && y < INT32_MIN - dy))
            y = (dy > 0) ? INT32_MAX : INT32_MIN;
        else
            y += dy;

        Serial.print("ΔX: "); Serial.print(dx);
        Serial.print("\tΔY: "); Serial.print(dy);
        Serial.print("\tX: "); Serial.print(x);
        Serial.print("\tY: "); Serial.print(y);

        if (xOverflow || yOverflow) {
            Serial.print("\t[OVERFLOW] X:");
            Serial.print(xOverflow);
            Serial.print(" Y:");
            Serial.print(yOverflow);
        }
        Serial.println();
        delay(1); // Small delay to avoid flooding serial
    }
}
