# HomeKit Garage Door Opener Accessory
**An [A+] Apple Home DIY Arduino Sketch Using HomeSpan on ESP32 Microcontrollers**

This program implements a HomeKit-compatible garage door opener accessory for use with ESP32 microcontrollers. It provides smart home control integration for garage doors, enhancing home automation and security capabilities.

## Features
- **HomeKit Integration**: Control your garage door via the Apple Home ecosystem (apps or Siri).
- **Door State Monitoring**: Detects five distinct garage door states using two door sensors for greater position accuracy (Open, Closed, Opening, Closing, Stopped).
- **Obstruction Detection**: Ensures safety by identifying obstacles and preventing automated activations if there is an obstruction.
- **Smart Automation**: Automates state transitions based on sensor readings.
- **Relay Control**: Manages door activation with a connected relay.
  
*Off the shelf units like Meross only use one sensor to detect only when the door is closed. They also lack Obstruction detection.

## App Display and State Transitions

### App Display

The accessory program reports five states to HomeKit: Open, Closed, Opening, Closing, and Stopped. The Apple Home App will display Open and Closed as the primary states, while Opening and Closing show as animations.

*Note that the Apple Home App lacks the ability to properly display the Stopped state. However the accessory continues to monitor the door's real-time status and passes the correct state to HomeKit. Therefore, third party apps may display the Stopped state.

### State Transitions
| **Current State** | **Target State** | **Description**                  |
|------------------|------------------|----------------------------------|
| 0 (Open)         | 0 (Open)         | Door is fully open               |
| 1 (Closed)       | 1 (Closed)       | Door is fully closed             |
| 2 (Opening)      | 0 (Open)         | Door is in the process of opening|
| 3 (Closing)      | 1 (Closed)       | Door is in the process of closing|
| 4 (Stopped)      | Any state        | Door has stopped in transition   |

## Hardware Requirements

- ESP32 microcontroller
- Garage door mechanism
- Open and closed position sensors (connected to pins 27 and 26 respectively)
- Obstruction detection sensor (connected to pin 23)
- Relay for door activation (connected to pin 25)

## Software Dependencies

- Arduino IDE
- ESP32 board support for Arduino
- HomeSpan library (https://github.com/HomeSpan/HomeSpan)

## Setup and Configuration

1. Install the Arduino IDE and ESP32 board support.
2. Install the HomeSpan library in your Arduino IDE.
3. Connect the hardware components as per the pin definitions in the code.
4. Upload the code to your ESP32 board.
5. Follow HomeSpan's instructions for pairing the device with your HomeKit setup.

## Usage

Once set up and paired with HomeKit:

1. Use the Home app or Siri to open, close, or check the status of your garage door.
2. The accessory will automatically detect the door's position and any obstructions.
3. If the door doesn't fully open or close within 14 seconds, it will enter a "Stopped" state.

## Contributing

Contributions to improve the accessory are welcome. There are several ways you can contribute to this project:

### Code Contributions

- Feel free to submit pull requests for bug fixes or new features.
- Open issues to report bugs or suggest enhancements.
- Contribute to the documentation to help others understand and use the project.

### Financial Support

If you find this project useful and would like to support its development and maintenance:

- Financial contributions can be made through PayPal: https://www.paypal.com/donate/?hosted_button_id=WZCVFQZKTBPEA
- These contributions help cover hosting costs, hardware for testing, and time invested in ongoing development.

Please note that financial contributions are entirely voluntary and do not entitle contributors to any special rights or privileges within the project.

### Other Ways to Help

- Share the project with others who might find it useful.
- Provide feedback on your experience using the accessory.
- Help answer questions from other users in the project's issues section.

Thank you for your interest in contributing to the HomeKit Garage Door Opener Accessory project!

## Additional Resources

For those interested in learning more about Apple Home and home automation, check out my booklet:

[![[A+]APPLE HOME: A Future Proof Smart Home Education](https://m.media-amazon.com/images/I/71moUK1EZFL._SL200_.jpg)](https://www.amazon.com/APPLE-HOME-Future-Education-Automation-ebook/dp/B0DF6ZYPQ1/ref=sr_1_1?keywords=Apple+Home&qid=1726433220&refinements=p_27%3AMogir&s=books&sr=1-1)

["[A+] APPLE HOME: A Future Proof Smart Home Education" by Mogir Jason Rofick](https://www.amazon.com/APPLE-HOME-Future-Education-Automation-ebook/dp/B0DF6ZYPQ1/ref=sr_1_1?keywords=Apple+Home&qid=1726433220&refinements=p_27%3AMogir&s=books&sr=1-1)

This book provides an educational insights into the world of Apple Home automation and how to prepare for the future of home automation.

## License

Copyright (c) 2024 MOGIR JASON ROFICK

This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

### You are free to:

- **Share**: copy and redistribute the material in any medium or format
- **Adapt**: remix, transform, and build upon the material for any purpose, even commercially

### Under the following terms:

- **Attribution**: You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
- **ShareAlike**: If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.

### No additional restrictions:

You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.

---

This project aims to provide a robust and reliable HomeKit-compatible garage door opener solution, improving home automation capabilities and user convenience.
