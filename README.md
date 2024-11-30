Here's a more **detailed README** that includes additional sections, explanations, and examples to better explain the library and its usage:

---

# **MX8650 Arduino Library**

### **Overview**

The MX8650 library simplifies communication with the **MX8650 Mouse Controller**, allowing users to interact with its internal registers, manage motion data, and configure sensor settings effectively. Designed for applications such as robotics, motion tracking, and embedded systems, this library provides robust functionality while abstracting low-level details.

### **Author**  
**Saurav Sajeev**

---

## **Table of Contents**
1. [Features](#features)
2. [Hardware Requirements](#hardware-requirements)
3. [Installation](#installation)
4. [Library Structure](#library-structure)
5. [Getting Started](#getting-started)
6. [Detailed API Reference](#detailed-api-reference)
7. [Constants Reference](#constants-reference)
8. [Examples](#examples)
9. [Troubleshooting](#troubleshooting)
10. [Contributing](#contributing)
11. [License](#license)

---

## **1. Features**
- **Motion Data Management**:
  - Retrieve motion status, X/Y deltas, and overall motion data.
- **Dynamic DPI Control**:
  - Change DPI settings using pre-defined constants or custom values.
- **Image Sensor Configuration**:
  - Set image quality, recognition rate, and thresholds.
- **Low Power Modes**:
  - Utilize built-in sleep modes to save power.
- **Ease of Use**:
  - Intuitive API for seamless integration into Arduino projects.

---

## **2. Hardware Requirements**
- **Microcontroller**: Arduino and SPI compatible board (e.g., UNO, Mega, Nano).
- **Pins**:
  - **SCLK**: Serial Clock for SPI communication.
  - **SDIO**: Serial Data Input/Output.
  - **CS**: (Optional) Chip Select for external control.

---

## **3. Installation**

### Using the Arduino Library Manager
1. Open the Arduino IDE.
2. Go to **Sketch → Include Library → Manage Libraries**.
3. Search for `MX8650` and click **Install**.

### Manual Installation
1. Download the library as a ZIP file from [GitHub](https://github.com/styropyr0/MX8650).
2. Open the Arduino IDE.
3. Go to **Sketch → Include Library → Add .ZIP Library**.
4. Select the downloaded ZIP file.

---

## **4. Library Structure**

### File Overview
- `MX8650.h`: Header file defining the class and public API.
- `MX8650.cpp`: Implementation of the MX8650 library.
- `MX8650_Constants.h`: Pre-defined constants for registers and settings.

---

## **5. Getting Started**

### Initialization
Include the library in your sketch and initialize the controller:
```cpp
#include "mx8650.h"

// SCLK: 13, SDIO: 11
MX8650 mouseController(13, 11);

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing MX8650...");
    mouseController.Log();  // Print initialization log
}

void loop() {
    // Your application logic here
}
```

With an optional **CS pin**:
```cpp
MX8650 mouseController(13, 11, 10);  // SCLK, SDIO, CS
```

---

## **6. Detailed API Reference**

### Constructors
- **`MX8650(uint8_t SCLK, uint8_t SDIO)`**  
  Initializes the MX8650 using the specified **SCLK** and **SDIO** pins.

- **`MX8650(uint8_t SCLK, uint8_t SDIO, uint8_t CS)`**  
  Same as above, but includes an optional **CS** pin for chip select.

### Motion Data
- **`String getMotionStatus()`**  
  Returns the motion status as a string.

- **`uint8_t getDeltaX()`**  
  Retrieves the X-axis motion delta.

- **`uint8_t getDeltaY()`**  
  Retrieves the Y-axis motion delta.

- **`uint8_t getMotionData()`**  
  Returns overall motion data.

### Configuration
- **`void setDPI(uint8_t state)`**  
  Sets the DPI to one of the pre-defined constants (`DPI_800`, `DPI_1200`, etc.).

- **`void setImageQuality(uint8_t quality)`**  
  Adjusts the image quality used by the sensor.

- **`void setImageRecRate(uint8_t rate)`**  
  Sets the image recognition rate (e.g., `IMG_RATE_HIGH`).

- **`void setSleepMode(uint8_t mode)`**  
  Configures the sleep mode (`SLEEP_MODE_1`, `FORCE_SLEEP_2`, etc.).

- **`void setSleepSetting_1(uint8_t frequency)`**  
  Configures the frequency for Sleep Mode 1.

### Logging and Debugging
- **`String getLog()`**  
  Retrieves the controller log as a string.

- **`void Log()`**  
  Prints the log to the Serial Monitor.

---

## **7. Constants Reference**

### DPI Settings
| Constant       | DPI Value |
|----------------|-----------|
| `DPI_800`      | 800       |
| `DPI_1200`     | 1200      |
| `DPI_1600`     | 1600      |

### Sleep Modes
| Constant           | Description        |
|--------------------|--------------------|
| `DISABLE_SLEEP`    | No sleep          |
| `SLEEP_MODE_1`     | Enter Sleep Mode 1 |
| `FORCE_SLEEP_2`    | Force Sleep Mode 2 |

### Recognition Rates
| Constant             | Description        |
|----------------------|--------------------|
| `IMG_RATE_HIGH`      | High recognition rate |
| `IMG_RATE_LOW`       | Low recognition rate  |

---

## **8. Examples**

### Example 1: Basic Motion Tracking
```cpp
#include "mx8650.h"

MX8650 mouseController(13, 11);

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing...");
    mouseController.setDPI(DPI_1200); // Set DPI to 1200
}

void loop() {
    Serial.println("Motion Status: " + mouseController.getMotionStatus());
    Serial.println("Delta X: " + String(mouseController.getDeltaX()));
    Serial.println("Delta Y: " + String(mouseController.getDeltaY()));
    delay(500);
}
```

### Example 2: Low-Power Sleep Mode
```cpp
#include "mx8650.h"

MX8650 mouseController(13, 11);

void setup() {
    Serial.begin(9600);
    mouseController.setSleepMode(SLEEP_MODE_1);
    mouseController.setSleepSetting_1(SLEEP_FREQ_LOW);
}

void loop() {
    Serial.println("Entering low-power mode...");
    delay(1000);
}
```

---

## **9. Troubleshooting**

### Common Issues
1. **No Response from Controller**:
   - Verify the SCLK and SDIO pin connections.
   - Ensure proper power supply to the MX8650.

2. **Incorrect Motion Data**:
   - Check if the sensor is correctly positioned.

3. **Compilation Errors**:
   - Confirm the library is installed correctly.

---

## **10. Contributing**

We welcome contributions to enhance this library! Follow these steps:
1. **Fork the Repository**:  
   ```bash
   git clone https://github.com/<your-repo>/MX8650.git
   ```
2. **Create a Branch**:  
   ```bash
   git checkout -b feature-name
   ```
3. **Submit a Pull Request**:  
   Include a description of your changes.

---

## **11. License**

This library is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.
