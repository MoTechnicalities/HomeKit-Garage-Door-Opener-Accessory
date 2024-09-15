# HomeKit Garage Door Opener Accessory

This program implements a HomeKit-compatible garage door opener accessory for use with ESP32 microcontrollers. It provides smart home control integration for garage doors, enhancing home automation and security capabilities.

## Features

- **HomeKit Integration**: Seamlessly connects with Apple HomeKit for smart home control.
- **Multiple Door States**: Manages and reports five distinct garage door states:
  - Open
  - Closed
  - Opening
  - Closing
  - Stopped
- **Remote Control**: Handles door activation requests from HomeKit.
- **Position Monitoring**: Uses open and closed sensors to monitor door position accurately.
- **Safety Features**: Detects and reports obstructions for enhanced safety.
- **Smart State Management**: Implements state transitions based on sensor readings and timing.

## Functionality

This accessory allows users to control and monitor their garage door remotely through the Apple Home app or Siri. Key functionalities include:

1. Remote door operation (open/close)
2. Real-time status updates
3. Obstruction detection and reporting
4. Automated state transitions
5. Timeout-based stopped state detection

## HomeKit States and Apple Home App Display

This accessory manages five distinct garage door states as per the HomeKit specification:

1. Open (0)
2. Closed (1)
3. Opening (2)
4. Closing (3)
5. Stopped (4)

However, it's important to note that the Apple Home app simplifies the display of these states for the end-user:

- **Open** and **Closed** states are displayed as is.
- **Opening** and **Closing** are shown as transitional states, often with an animation.
- The **Stopped** state is not explicitly displayed in the Apple Home app. When the door is in a Stopped state:
  - The app may show the last known definitive state (Open or Closed).
  - It might display the target state instead.
  - In some cases, it may show an intermediate position without a specific label.

For more detailed state information, users may need to use third-party HomeKit apps that can display all five states explicitly.

### State Transitions

Our accessory handles state transitions as follows:

- *Current: 0 (Open)*, *Target: 0 (Open)*: Door is fully open.
- *Current: 1 (Closed)*, *Target: 1 (Closed)*: Door is fully closed.
- *Current: 2 (Opening)*, *Target: 0 (Open)*: Door is in the process of opening.
- *Current: 3 (Closing)*, *Target: 1 (Closed)*: Door is in the process of closing.
- *Current: 4 (Stopped)*, *Target: any state*: Door has stopped in an intermediate position.

The accessory will report these states accurately to HomeKit, ensuring that even if the Apple Home app doesn't explicitly show the "Stopped" state, the system is aware of the door's actual condition.

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
