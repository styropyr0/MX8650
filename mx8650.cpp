#include <mx8650.h>
#include "MX8650_Constants.h"

MX8650::MX8650(uint8_t sclk, uint8_t sdio)
{
    SCLK = sclk;
    SDIO = sdio;
    setUp();
}

MX8650::MX8650(uint8_t sclk, uint8_t sdio, uint8_t cs)
{
    SCLK = sclk;
    SDIO = sdio;
    CS = cs;
    setUp();
}

void MX8650::setUp()
{
    pinMode(SCLK, OUTPUT);
    pinMode(SDIO, INPUT);

    if (CS > 0)
        pinMode(CS, OUTPUT);
}

void MX8650::begin(uint8_t sleepMode, uint8_t dpi, uint8_t imgRecRate) {
    pinMode(SCLK, OUTPUT);
    pinMode(SDIO, INPUT);

    digitalWrite(SCLK, HIGH);                     
    delayMicroseconds(5);
    digitalWrite(SCLK, LOW);
    delayMicroseconds(1);
    digitalWrite(SCLK, HIGH);
    delay(100); // Wait for sensor ready

    if (CS > 0)
        pinMode(CS, OUTPUT);

    // Apply settings
    writeToSPI(0x80 | SLEEP_MODE_ADDR, sleepMode);
    writeToSPI(0x80 | DPI_ADDR, dpi);
    writeToSPI(0x80 | 0x09, 0x5A); // Write protect for the register 0x0A~0x7F ?
    writeToSPI(0x80 | IMG_THRES_ADDR, 0x04);
    writeToSPI(0x80 | IMG_RECG_ADDR, imgRecRate);
}

String MX8650::getLog()
{
    deviceFound = verify();
    if (deviceFound == true)
        return "Product ID: 0x" + getPID() + "\nOperational mode: 0x" + getOperationalMode() + "\nDPI: " + String(getDPI()) + "\nMotion status: " + getMotionStatus() + "\nMotion data: " + String(getMotionData()) + "\nDelta X: " + String(getDeltaX()) + "\tDelta Y: " + String(getDeltaY()) + "\nImage quality: " + String(getImageQuality()) + "\nOperation state: " + getOperationState() + "\nImage threshold: " + String(getImageThreshold()) + "\nImage recogonition rate: " + String(getImageRecRate());
    else
        return "No MX8650 has been detected. Check the connections or make sure it is working.";
}

bool MX8650::verify()
{
    return transmitViaSerial(0x00, 0x00) == 48;
}

String MX8650::getMotionStatus()
{
    if (transmitViaSerial(MOTION_STATUS_ADDR, 0x00) >= 0x84)
        return "IN MOTION";
    else
        return "IDLE";
}

uint8_t MX8650::getMotionData()
{
    return transmitViaSerial(MOTION_STATUS_ADDR, 0x00);
}

uint8_t MX8650::getDeltaX()
{
    return transmitViaSerial(DELTA_X_ADDR, 0x00);
}

uint8_t MX8650::getDeltaY()
{
    return transmitViaSerial(DELTA_Y_ADDR, 0x00);
}

String MX8650::getPID()
{
    char temp[4];
    String pID;
    itoa(transmitViaSerial(0x00, 0x00), temp, 16);
    pID = String(temp);
    itoa(transmitViaSerial(0x01, 0x00), temp, 16);
    pID += String(temp);
    pID.toUpperCase();
    return pID;
}

String MX8650::getOperationalMode()
{
    char temp[4];
    itoa(transmitViaSerial(SLEEP_MODE_ADDR, 0x00), temp, 16);
    String opMode;
    opMode = String(temp);
    opMode.toUpperCase();
    return opMode;
}

uint8_t MX8650::getImageQuality()
{
    return transmitViaSerial(IMG_QUALITY_ADDR, 0x00);
}

String MX8650::getOperationState()
{
    char temp[4];
    itoa(transmitViaSerial(OPERATION_STATE_ADDR, 0x00), temp, 16);
    String opMode;
    opMode = String(temp);
    opMode.toUpperCase();
    return opMode;
}

uint8_t MX8650::getImageRecRate()
{
    return transmitViaSerial(IMG_RECG_ADDR, 0x00);
}

uint8_t MX8650::getImageThreshold()
{
    return transmitViaSerial(IMG_THRES_ADDR, 0x00);
}

uint16_t MX8650::getDPI()
{
    uint8_t dpi = transmitViaSerial(DPI_ADDR, 0x00);

    switch (dpi)
    {
    case DPI_100:
        return 100;
    case DPI_800:
        return 800;
    case DPI_1200:
        return 1200;
    case DPI_1600:
        return 1600;
    default:
        return 0;
    }
}

void MX8650::Log()
{
    Serial.println(getLog());
    Serial.println();
}

void MX8650::setSleepMode(uint8_t mode)
{
    writeToSPI(SLEEP_MODE_ADDR, mode);
}

void MX8650::setDPI(uint8_t dpi)
{
    writeToSPI(DPI_ADDR, dpi);
}

void MX8650::setImageQuality(uint8_t quality)
{
    writeToSPI(IMG_QUALITY_ADDR, quality);
}

void MX8650::setOperationState(uint8_t state)
{
    writeToSPI(OPERATION_STATE_ADDR, state);
}

void MX8650::setSleepSetting_1(uint8_t frequency)
{
    writeToSPI(SLEEP1_FREQ_ADDR, frequency);
}

void MX8650::setSleepSetting_2(uint8_t frequency)
{
    writeToSPI(SLEEP2_FREQ_ADDR, frequency);
}

void MX8650::setSleepEnterTime(uint8_t mode)
{
    writeToSPI(SLEEP_ENTER_TIME_ADDR, mode);
}

void MX8650::setImageThreshold(uint8_t threshold)
{
    writeToSPI(IMG_THRES_ADDR, threshold);
}

void MX8650::setImageRecRate(uint8_t rate)
{
    writeToSPI(IMG_RECG_ADDR, rate);
}

uint8_t MX8650::transmitViaSerial(uint8_t addr, uint8_t wBit)
{
    uint8_t result = 0;

    // Activate chip select (active LOW)
    chipSelectState(LOW);

    // --- Send address ---
    pinMode(SDIO, OUTPUT);
    for (int i = 7; i >= 0; i--)
    {
        digitalWrite(SCLK, LOW);
        digitalWrite(SDIO, (addr >> i) & 0x01);
        digitalWrite(SCLK, HIGH);
    }

    // Switch data line to input
    pinMode(SDIO, INPUT);
    delayMicroseconds(100); // tSRAD

    // --- Read data ---
    for (int i = 7; i >= 0; i--)
    {
        digitalWrite(SCLK, LOW);
        digitalWrite(SCLK, HIGH);
        result |= (digitalRead(SDIO) << i);
    }

    delayMicroseconds(100); // tSCLK-NCS

    // Deactivate chip select
    chipSelectState(HIGH);

    return result;
}

void MX8650::writeToSPI(uint8_t addr, uint8_t data)
{
    chipSelectState(LOW);

    // --- Send address (write bit already set in addr if needed) ---
    pinMode(SDIO, OUTPUT);
    for (int i = 7; i >= 0; i--)
    {
        digitalWrite(SCLK, LOW);
        digitalWrite(SDIO, (addr >> i) & 0x01);
        digitalWrite(SCLK, HIGH);
    }

    // --- Send data ---
    for (int i = 7; i >= 0; i--)
    {
        digitalWrite(SCLK, LOW);
        digitalWrite(SDIO, (data >> i) & 0x01);
        digitalWrite(SCLK, HIGH);
    }

    // Short delay before deactivating CS (tSCLK-NCS)
    delayMicroseconds(100);

    // Deactivate chip select
    chipSelectState(HIGH);
}

void MX8650::chipSelectState(uint8_t state)
{
    if (CS > 0)
        digitalWrite(CS, state);
}