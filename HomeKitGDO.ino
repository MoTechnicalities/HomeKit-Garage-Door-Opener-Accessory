/*
 * HomeKit Garage Door Opener Accessory
 * 
 * This program implements a HomeKit-compatible garage door opener accessory
 * for use with ESP32 microcontrollers. It provides the following functionality:
 * 
 * - Integrates with Apple HomeKit for smart home control
 * - Manages and reports five distinct garage door states: Open, Closed, 
 *   Opening, Closing, and Stopped
 * - Handles door activation requests from HomeKit
 * - Monitors door position using open and closed sensors
 * - Detects and reports obstructions for safety
 * - Implements state transitions based on sensor readings and timing
 * 
 * This accessory allows users to control and monitor their garage door
 * remotely through the Apple Home app or Siri, enhancing home automation
 * and security capabilities.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright (c) 2024 MOGIR JASON ROFICK
 * 
 * This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 
 * International License. To view a copy of this license, visit 
 * http://creativecommons.org/licenses/by-sa/4.0/ or send a letter to 
 * Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
 * 
 * You are free to:
 * - Share: copy and redistribute the material in any medium or format
 * - Adapt: remix, transform, and build upon the material for any purpose, 
 *   even commercially
 * 
 * Under the following terms:
 * - Attribution: You must give appropriate credit, provide a link to the 
 *   license, and indicate if changes were made. You may do so in any 
 *   reasonable manner, but not in any way that suggests the licensor 
 *   endorses you or your use.
 * - ShareAlike: If you remix, transform, or build upon the material, you 
 *   must distribute your contributions under the same license as the original.
 * 
 * No additional restrictions: You may not apply legal terms or technological 
 * measures that legally restrict others from doing anything the license permits.
 */

#include "Arduino.h"
#include "HomeSpan.h"

#define DOOR_ACTIVATION_RELAY_PIN 25
#define CLOSED_DOOR_SENSOR_PIN 26
#define OPEN_DOOR_SENSOR_PIN 27
#define OBSTRUCTION_SENSOR_PIN 23

class GarageDoorAccessory : public Service::GarageDoorOpener {
private:
    unsigned long lastActivationTime;
    unsigned long stateChangeTime;
    int lastDefiniteState;

    int getCurrentDoorState() {
        bool isClosed = digitalRead(CLOSED_DOOR_SENSOR_PIN) == LOW;
        bool isOpen = digitalRead(OPEN_DOOR_SENSOR_PIN) == LOW;

        if (isClosed && !isOpen) return 1; // Closed
        if (isOpen && !isClosed) return 0; // Open

        // Transitional states
        if (lastDefiniteState == 1 && !isClosed) return 2; // Opening
        if (lastDefiniteState == 0 && !isOpen) return 3; // Closing

        // Check for stopped state
        if (millis() - stateChangeTime > 14000) return 4; // Stopped

        // If unsure, return the last transitional state
        return (lastDefiniteState == 1) ? 2 : 3;
    }

    bool isObstructed() {
        return digitalRead(OBSTRUCTION_SENSOR_PIN) == LOW;
    }

    void activateDoor() {
        digitalWrite(DOOR_ACTIVATION_RELAY_PIN, HIGH);
        delay(1250);  // 1.25 seconds
        digitalWrite(DOOR_ACTIVATION_RELAY_PIN, LOW);
        lastActivationTime = millis();
        stateChangeTime = millis();
    }

public:
    SpanCharacteristic *current;
    SpanCharacteristic *target;
    SpanCharacteristic *obstruction;

    GarageDoorAccessory() : Service::GarageDoorOpener() {
        current = new Characteristic::CurrentDoorState(1);  // 1=closed (initial state)
        target = new Characteristic::TargetDoorState(1);    // 1=closed (initial state)
        obstruction = new Characteristic::ObstructionDetected(false);
        lastActivationTime = 0;
        stateChangeTime = 0;
        lastDefiniteState = 1; // Assume closed initially
    }

    boolean update() override {
        if (target->getNewVal() != target->getVal()) {
            if (!isObstructed()) {
                activateDoor();
                if (current->getVal() == 1) {
                    current->setVal(2); // Opening
                    target->setVal(0);
                } else if (current->getVal() == 0) {
                    current->setVal(3); // Closing
                    target->setVal(1);
                }
            } else {
                // If obstructed, revert the target state
                target->setVal(target->getVal());
                return false; // Indicate that the update was not successful
            }
        }
        return true;
    }

    void loop() {
        int newState = getCurrentDoorState();
        
        if (current->getVal() != newState) {
            current->setVal(newState);
            if (newState == 0 || newState == 1) {
                lastDefiniteState = newState;
                target->setVal(newState);
                stateChangeTime = millis();
            } else if (newState == 4) {
                // Stopped state, keep the existing target
            } else {
                // For transitional states, update the target accordingly
                target->setVal(newState == 2 ? 0 : 1);
            }
        }

        // Update obstruction state
        bool obstructed = isObstructed();
        if (obstruction->getVal() != obstructed) {
            obstruction->setVal(obstructed);
        }

        // Check if we need to transition to stopped state
        if ((current->getVal() == 2 || current->getVal() == 3) && 
            millis() - stateChangeTime > 14000) {
            current->setVal(4); // Stopped
        }
    }
};

GarageDoorAccessory *garageDoor;

void setup() {
    Serial.begin(115200);
    pinMode(DOOR_ACTIVATION_RELAY_PIN, OUTPUT);
    pinMode(CLOSED_DOOR_SENSOR_PIN, INPUT_PULLUP);
    pinMode(OPEN_DOOR_SENSOR_PIN, INPUT_PULLUP);
    pinMode(OBSTRUCTION_SENSOR_PIN, INPUT_PULLUP);

    homeSpan.begin(Category::GarageDoorOpeners, "Garage Door Opener");

    new SpanAccessory();
      new Service::AccessoryInformation();
        new Characteristic::Identify();
      garageDoor = new GarageDoorAccessory();
}

void loop() {
    homeSpan.poll();
}
