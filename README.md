# Intelligent Mirror
 ## Table of Contents
1. [Introduction](#introduction)
2. [General Description](#General-Description)
3. [Hardware Design](#Hardware-Design)
4. [Software Design](#Software-Design)
5. [Results](#Results)
6. [Conclusions](#Conclusions)
7. [Source Code](#Source-Code)
8. [Journal](#Journal)
9. [Bibliography/Resources](#Bibliography/Resources)
10. [License](#License)
    
 ## Introduction
 
 This project is an intelligent mirror that lights up upon detecting movement and offers various functionalities such as LED lighting, an alarm-setting mode, inspirational quotes displayed on an LCD, and music played through a buzzer. The main goal is to create a smart, multifunctional mirror that enhances daily routines by combining practicality and motivation in one device. 
 
 The idea originated from the desire to merge technology with everyday objects, transforming a simple mirror into a useful and interactive tool. This project is beneficial for others by offering a modern, functional home accessory that makes mornings more efficient and motivating.

## General Description
### Block Diagram
<p>
  <img src="https://github.com/mariaxadina/Intelligent-Mirror/blob/images/scheme.png" width="300"/>
</p>

### Detailed Description of Hardware Functionality
**1. Microcontroller - ATmega328P**

ATmega328P is an 8-bit microcontroller based on the AVR architecture, commonly used in Arduino boards. It operates at 5V with a clock speed of up to 16 MHz.The ATmega328P features 23 GPIO pins, supporting digital I/O, PWM, and analog input. It includes communication interfaces like SPI, I2C, and UART, making it ideal for embedded systems, sensors, and small IoT applications due to its low power consumption and versatility.

**2. PIR Motion Sensor**

The PIR Motion Sensor detects movement and triggers the LED strip across the mirror to turn on. It operates on 5V and outputs a digital HIGH signal when motion is detected. The sensor is connected to GPIO pin 7 of the ATmega328P, which monitors the signal to activate the LEDs.

**3. LCD Display (I2C)**

The 16x2 I2C LCD Display is used to show alarm settings and countdown. It connects to the ATmega328P via I2C for simplified communication. A potentiometer is connected to the LCD's V0 pin to adjust contrast, while GPIO pins 2, 3, 4, and 5 control the display functions. It operates at 5V and provides clear text output for user interaction.

**4. Speaker**

The speaker is used to play music and sound an alarm when the countdown reaches zero, allowing tone generation and control. The speaker operates at 5V and provides audio feedback for the system.

**5. Buttons**
   
The project includes three buttons with pull-up resistors for stable input detection:

~ Music Button: Controls music, connected to pin 11.

~ Set Alarm Button: Sets the alarm, connected to pin 9.

~ Start/Stop Alarm Button: Starts or stops the alarm countdown, connected to pin 10.

All buttons use internal pull-up resistors, ensuring reliable operation with active LOW logic.

**6. Power Supply**

The power supply uses a USB 2.0 A/B cable connected to the laptop, delivering 5V to the Arduino.

## Hardware Design 
### Bill of Materials (BOM)

| Component              | Quantity | Description                              | Datasheet                                                                                 |
|------------------------|----------|------------------------------------------|-------------------------------------------------------------------------------------------------|
| Breadboard             | 1        | Standard breadboard                      | https://components101.com/sites/default/files/component_datasheet/Breadboard%20Datasheet.pdf          |
| Jumper Wires (Cables)  | -        | Male-to-female wires                     | https://www.mouser.com/c/ds/tools-supplies/prototyping-products/jumper-wires/?srsltid=AfmBOopanPWOk8Ukw1_juN3MPRRptIMeLviuPscUZNwjSLqPMhHw0F-X|
| Arduino ATmega328P     | 1        | Microcontroller board                    | https://www.alldatasheet.com/datasheet-pdf/view/241077/ATMEL/ATMEGA328P.html |
| Potentiometer          | 1        | 10k Ohm potentiometer                    | https://components101.com/sites/default/files/component_datasheet/potentiometer%20datasheet.pdf                         |
| Push Buttons           | 3        | Buttons with pull-up resistance          | https://components101.com/sites/default/files/component_datasheet/Push-Button.pdf                 |
| Resistors (1kΩ)        | 3        | 1k Ohm resistors                         | [Datasheet](https://www.vishay.com/docs/31027/cmfind.pdf)                                      |
| Resistors (330Ω)       | 1        | 330 Ohm resistor                         | [Datasheet](https://www.vishay.com/docs/31027/cmfind.pdf)                                      |
| LCD 16x2               | 1        | Character display                        | https://components101.com/sites/default/files/component_datasheet/16x2%20LCD%20Datasheet.pdf                               |
| PIR Sensor             | 1        | Motion detection sensor                  | https://components101.com/sites/default/files/component_datasheet/Push-Button.pdf                |


### Circuit Schematic  
<p>
  <img src="https://github.com/mariaxadina/Intelligent-Mirror/blob/images/tinkercad.jpg" width="300"/>
</p>

## Software Design

### Development Environment  
The project is developed using **PlatformIO**, which provides an integrated build system, library manager, and support for multiple boards and frameworks.  

## Results

## Conclusions

## Source Code
### Directory Structure  
- **src/**: Contains all source code files.  
- **hardware/**: Contains schematics and diagrams.  
- **images/**: Contains project images linked in this README. 

## Journal
**12/3/2024**: Started documenting the Intelligent Mirror project, focusing on initial setup and planning.

**12/10/2024**: Implemented the hardware components of the Intelligent Mirror, including the PIR motion sensor, LCD display, speaker, buttons, and power supply.

**12/17/2024**: Completed the circuit schematic, block diagram, and detailed hardware description for the documentation.

## Bibliography/Resources

## License
This project is licensed under the [MIT License](./LICENSE).
