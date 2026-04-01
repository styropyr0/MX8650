#ifndef mx8650
#define mx8650

#include <Arduino.h>
#include <SPI.h>
#include "MX8650_Constants.h"

/**
 * @author Saurav Sajeev
 * @brief This library makes the task of communicating with the mouse controller MX8650, and reading/writing datas to its internal registers.
 * @note Refer the MX8650 datasheet before transferring data to the sensor registries.
 */

class MX8650
{
public:
    /**
     * @brief Constructor which set up MX8650 Mouse controller to send and recieve data.
     * @param SCLK PIN to which Serial Clock pin is attached.
     * @param SDIO PIN to which Serial Data pins (Both In and Out) are attached.
     */
    MX8650(uint8_t SCLK, uint8_t SDIO);
    /**
     * @brief Constructor which set up MX8650 Mouse controller to send and recieve data.
     * @param SCLK PIN to which Serial Clock pin is attached.
     * @param SDIO PIN to which Serial Data pins (Both In and Out) are attached.
     * @param CS Optional external CS pin. Commonly a transistor's base pin.
     */
    MX8650(uint8_t SCLK, uint8_t SDIO, uint8_t CS);
    /**
     * @brief Gets the log output from the controller.
     * @returns The log output as String.
     */
    String getLog();
    /**
     * @brief Prints the log output from the controller on the Serial monitor.
     */
    void Log();
    /**
     * @brief Gets the Motion status.
     * @returns The Motion status as String.
     */
    String getMotionStatus();
    /**
     * @brief Gets the Motion data from the controller.
     * @returns The value of Motion data.
     */
    uint8_t getMotionData();
    /**
     * @brief Gets the change in motion data on X axis.
     * @returns The value of change in motion data on X axis.
     */
    uint8_t getDeltaX();
    /**
     * @brief Gets the change in motion data on Y axis.
     * @returns The value of change in motion data on Y axis.
     */
    uint8_t getDeltaY();
    /**
     * @brief Gets the Product ID of the controller.
     * @returns The PID as a Hexadecimal String.
     */
    String getPID();
    /**
     * @brief Gets the Operational mode of the controller.
     * @returns The Operational mode of the controller.
     */
    String getOperationalMode();
    /**
     * @brief Gets the Image quality being used by the sensor array.
     * @returns The Image quality being used.
     */
    uint8_t getImageQuality();
    /**
     * @brief Gets the rate of Image recogonition by the controller.
     * @returns The Image recogonition rate of the controller.
     */
    uint8_t getImageRecRate();
    /**
     * @brief Gets the Image threshold used by the Motion Estimation Engine.
     * @returns The Image threshold being used by MEE.
     */
    uint8_t getImageThreshold();
    /**
     * @brief Gets the Operation state being used.
     * @returns The Operation state.
     */
    String getOperationState();
    /**
     * @brief Gets the DPI (Sensitivity) being used by the Motion Estimation Engine.
     * @returns The DPI being used by MEE.
     */
    uint16_t getDPI();
    /**
     * @brief Sets the Sleep mode. You may use the built-in sleep constants or refer the datasheet.
     * @param mode The Sleep mode to be changed to.
     */
    void setSleepMode(uint8_t mode);
    /**
     * @brief Sets the DPI. You may use the built-in DPI constants or refer the datasheet.
     * @param state The DPI to set.
     */
    void setDPI(uint8_t state);
    /**
     * @brief Sets the Image quality. You may refer the datasheet before setting the image quality.
     * @param quality The Image quality to set.
     */
    void setImageQuality(uint8_t quality);
    /**
     * @brief Sets the Operation state. You may refer the datasheet before setting the Operation state.
     * @param state The Operation state to set.
     */
    void setOperationState(uint8_t state);
    /**
     * @brief Sets the frequency of Sleep mode 1. You may use the built-in Sleep frequency constants or refer the datasheet before setting.
     * @param frequency The Sleep frequency to set.
     */
    void setSleepSetting_1(uint8_t frequency);
    /**
     * @brief Sets the frequency of Sleep mode 2. You may use the built-in Sleep frequency constants or refer the datasheet before setting.
     * @param freqency The Sleep frequency to set.
     */
    void setSleepSetting_2(uint8_t frequency);
    /**
     * @brief Sets the time to enter both sleep modes seperately. You may  refer the datasheet before setting.
     * @param mode The time to enter sleep modes.
     */
    void setSleepEnterTime(uint8_t mode);
    /**
     * @brief Sets the Image threshold value. You may refer the datasheet before setting.
     * @param threshold The threshold to be used by the Motion Estimation Engine.
     */
    void setImageThreshold(uint8_t threshold);
    /**
     * @brief Sets the Image recogonition rate. You may use the built-in Image recogonition rate constants or refer the datasheet before setting.
     * @param rate The rate to be used by the Motion Estimation Engine.
     */
    void setImageRecRate(uint8_t rate);

private:
    uint8_t SDIO = 11, SCLK = 13, CS = -1;
    bool deviceFound = false;
    void setUp();
    bool verify();
    void writeToSPI(uint8_t addr, uint8_t data);
    uint8_t transmitViaSerial(uint8_t addr, uint8_t wBit);
    void chipSelectState(uint8_t state);
};

#endif