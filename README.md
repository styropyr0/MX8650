MX8650 Library Documentation
---------------------------
Overview
This library facilitates communication with the MX8650 mouse controller, allowing for reading and writing data to its internal registers. It is essential to refer to the MX8650 datasheet before transferring data to the sensor registers.
Author: Saurav Sajeev

1. Class: MX8650
   
1.1 Constants
---------
Operational Modes
1.	SLEEP_MODE_ADDR: 0x05
2.	DISABLE_SLEEP: 0xA0
3.	SLEEP_MODE_1: 0xB0
4.	SLEEP_MODE_2: 0xB8
5.	FORCE_SLEEP_1: 0xB2
6.	FORCE_SLEEP_2: 0xBC
7.	FORCE_WAKEUP: 0xB1
DPI Settings
1.	DPI_ADDR: 0x06
2.	DPI_800: 0x04
3.	DPI_100: 0x05
4.	DPI_1200: 0x06
5.	DPI_1600: 0x07
Sleep Frequencies
1.	SLEEP1_FREQ_ADDR: 0x0A
2.	SLEEP2_FREQ_ADDR: 0x0C
3.	SLEEP_FREQ_LOW: 0x02
4.	SLEEP_FREQ_MED: 0x07
5.	SLEEP_FREQ_HIGH: 0xF2
6.	SLEEP1_FREQ_DEFAULT: 0x72
7.	SLEEP2_FREQ_DEFAULT: 0x92
Sleep Mode Enter Time
1.	SLEEP_ENTER_TIME_ADDR: 0x0B
Image Threshold
1.	IMG_THRES_ADDR: 0x0D
Image Recognition Rate
1.	IMG_RECG_ADDR: 0x0E
2.	IMG_RATE_HIGHEST: 0xE0
3.	IMG_RATE_HIGH: 0x07
4.	IMG_RATE_MED: 0x05
5.	IMG_RATE_LOW: 0x09
6.	IMG_RATE_LOWEST: 0x0F
Motion Status
1.	MOTION_STATUS_ADDR: 0x02
2.	DELTA_X_ADDR: 0x03
3.	DELTA_Y_ADDR: 0x04
Image Quality
1.	IMG_QUALITY_ADDR: 0x07
Operation State
1.	OPERATION_STATE_ADDR: 0x08

1.2 Constructors
----------------
1.	MX8650(uint8_t SCLK, uint8_t SDIO)
Initializes the MX8650 Mouse controller for data transmission.
SCLK: PIN to which the Serial Clock pin is attached.
SDIO: PIN to which the Serial Data pins (both In and Out) are attached.
2.	MX8650(uint8_t SCLK, uint8_t SDIO, uint8_t CS)
Initializes the MX8650 Mouse controller for data transmission with an optional CS pin.
SCLK: PIN to which the Serial Clock pin is attached.
SDIO: PIN to which the Serial Data pins (both In and Out) are attached.
CS: Optional external CS pin, typically a transistor's base pin.

1.3 Public Methods
------------------
1.	String getLog()
Retrieves the log output from the controller.
Returns: Log output as a String.
2.	void Log()
Prints the log output from the controller to the Serial monitor.
3.	String getMotionStatus()
Retrieves the Motion status.
Returns: Motion status as a String.
4.	uint8_t getMotionData()
Retrieves the Motion data from the controller.
Returns: Value of Motion data.
5.	uint8_t getDeltaX()
Retrieves the change in motion data on the X-axis.
Returns: Value of change in motion data on the X-axis.
6.	uint8_t getDeltaY()
Retrieves the change in motion data on the Y-axis.
Returns: Value of change in motion data on the Y-axis.
7.	String getPID()
Retrieves the Product ID of the controller.
Returns: PID as a Hexadecimal String.
8.	String getOperationalMode()
Retrieves the Operational mode of the controller.
Returns: Operational mode as a String.
9.	uint8_t getImageQuality()
Retrieves the Image quality used by the sensor array.
Returns: Image quality as uint8_t.
10.	uint8_t getImageRecRate()
Retrieves the rate of image recognition by the controller.
Returns: Image recognition rate as uint8_t.
11.	uint8_t getImageThreshold()
Retrieves the Image threshold used by the Motion Estimation Engine.
Returns: Image threshold as uint8_t.
12.	String getOperationState()
Retrieves the current Operation state.
Returns: Operation state as a String.
13.	uint16_t getDPI()
Retrieves the DPI (sensitivity) used by the Motion Estimation Engine.
Returns: DPI as uint16_t.
14.	void setDPI(uint8_t state)
Sets the DPI. You may use the built-in DPI constants or refer to the datasheet.
state: The DPI to set.
15.	void setImageQuality(uint8_t quality)
Sets the Image quality. Refer to the datasheet before setting the image quality.
quality: The Image quality to set.
16.	void setOperationState(uint8_t state)
Sets the Operation state. Refer to the datasheet before setting the Operation state.
state: The Operation state to set.
17.	void setSleepSetting_1(uint8_t frequency)
Sets the frequency of Sleep mode 1. You may use the built-in Sleep frequency constants or refer to the datasheet before setting.
frequency: The Sleep frequency to set.
18.	void setSleepSetting_2(uint8_t frequency)
Sets the frequency of Sleep mode 2. You may use the built-in Sleep frequency constants or refer to the datasheet before setting.
frequency: The Sleep frequency to set.
19.	void setSleepEnterTime(uint8_t mode)
Sets the time to enter both sleep modes separately. Refer to the datasheet before setting.
mode: The time to enter sleep modes.
20.	void setImageThreshold(uint8_t threshold)
Sets the Image threshold value. Refer to the datasheet before setting.
threshold: The threshold to be used by the Motion Estimation Engine.
21.	void setImageRecRate(uint8_t rate)
Sets the Image recognition rate. You may use the built-in Image recognition rate constants or refer to the datasheet before setting.
rate: The rate to be used by the Motion Estimation Engine.

Note
----
For more detailed information, always refer to the MX8650 datasheet.

