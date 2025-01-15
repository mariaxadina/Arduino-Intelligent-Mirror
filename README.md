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
<a>
  <img src="https://github.com/mariaxadina/Intelligent-Mirror/blob/main/images/scheme.jpg" width="500"/>
</a>

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

| Component              | Quantity | Description                              | Datasheet                                                                                       |
|------------------------|----------|------------------------------------------|-------------------------------------------------------------------------------------------------|
| Breadboard             | 1        | Standard breadboard                      | https://components101.com/sites/default/files/component_datasheet/Breadboard%20Datasheet.pdf    |
| Jumper Wires (Cables)  | -        | Male-to-female wires                     | https://www.mouser.com/c/ds/tools-supplies/prototyping-products/jumper-wires/?srsltid=AfmBOopanPWOk8Ukw1_juN3MPRRptIMeLviuPscUZNwjSLqPMhHw0F-X|
| Arduino ATmega328P     | 1        | Microcontroller board                    | https://www.alldatasheet.com/datasheet-pdf/view/241077/ATMEL/ATMEGA328P.html                    |
| Potentiometer          | 1        | 10k Ohm potentiometer                    | https://components101.com/sites/default/files/component_datasheet/potentiometer%20datasheet.pdf |
| Push Buttons           | 3        | Buttons with pull-up resistance          | https://components101.com/sites/default/files/component_datasheet/Push-Button.pdf               |
| Resistors (1kΩ)        | 3        | 1k Ohm resistors                         |                                       -                                                         |
| Resistors (330Ω)       | 1        | 330 Ohm resistor                         |                                       -                                                         |
| LCD 16x2               | 1        | Character display                        | https://components101.com/sites/default/files/component_datasheet/16x2%20LCD%20Datasheet.pdf    |
| PIR Sensor             | 1        | Motion detection sensor                  | https://components101.com/sites/default/files/component_datasheet/Push-Button.pdf               |
| 9V Battery             | 1        | Portable power source                    | https://www.farnell.com/datasheets/1842389.pdf                                                  |
| Warwick 9V Battery Clip| 1        | Convenient connector                     |                                        -                                                        |
| 8 Ohm 0.5 W Speaker    | 1        | Audio output device                      |https://www.verical.com/datasheet/adafruit-speakers-1890-4292980.pdf?srsltid=AfmBOoqh8d7QvKfPEunbL7mZLFy78uGA7sLrATxcLboLpD3B0acp8ZGM|


### Circuit Schematic  
<a>
  <img src="https://github.com/mariaxadina/Intelligent-Mirror/blob/main/images/tinkercad.png" width="800"/>
</a>

### Connected Components
<a>
  <img src="https://github.com/mariaxadina/Intelligent-Mirror/blob/main/images/image00001.jpeg" width="500"/>
  <img src="https://github.com/mariaxadina/Intelligent-Mirror/blob/main/images/image_w_battery.jpeg" width="500"/>
  <img src="https://github.com/mariaxadina/Intelligent-Mirror/blob/main/images/image00003.jpeg" width="500"/>
  <img src="https://github.com/mariaxadina/Intelligent-Mirror/blob/main/images/image00004.jpeg" width="500"/>

</a>

## Software Design

### Development Environment  
The project is developed using **PlatformIO**, which provides an integrated build system, library manager, and support for multiple boards and frameworks.  

### Libraries
In this project, I used three libraries to manage various components effectively:
- **LiquidCrystal Library**: In my project, the LiquidCrystal library is responsible for managing the 16x2 LCD, which displays the alarm settings, countdown, and other information.
- **Adafruit_NeoPixel Library**: In my intelligent mirror project, the NeoPixel library is used to manage the LED strip surrounding the mirror. It creates visual effects and provides illumination by controlling each LED's RGB values independently.
- **PCM Library**: In the project, the PCM library is used to play sound effects and alarm tones through the speaker, adding auditory feedback and enhancing user interaction. The sounds were edited and optimized in Audacity before being implemented.

### Audio Integration using Audacity and EncodeAudio.exe
To integrate sound into the project, I started with an MP3 version of the desired audio file. Using Audacity I converted the file into a 16-bit PCM format with an 8000 Hz sampling frequency to ensure compatibility with the Arduino and PCM library. Afterward, I utilized an audio encoder tool to convert the audio into a numeric array format required by the code. The generated data was then copied directly to the clipboard and integrated into the Arduino sketch, allowing the speaker to play the processed sound seamlessly.

### Sensor Calibration
To ensure accurate motion detection, I calibrated the PIR sensor by introducing a 60-second delay in the setup phase of the Arduino code. This delay allows the sensor to stabilize and adjust to the ambient environment, reducing false triggers and ensuring reliable performance during operation.

### Custom Characters using DeepBlueEmbedded
To create custom emojis for the LCD, I used the [DeepBlueEmbedded Custom Character Generator](https://deepbluembedded.com/lcd-custom-character-generator/). This tool simplifies the process of designing and generating the byte arrays required for custom characters on an LCD.

### Project Structure
1. Included Libraries: LiquidCrystal, Adafruit_NeoPixel, PCM and Arduino.h.
2. Pin Definitions: LCD Pins, Sensor Pin, LED Strip Pin, Speaker Pin and Button Pins.
3. Arrays of custom characters.
4. Sound Data: Alarm Sound and Music.
5. Global Variables: Toggle Flags, Debounce Variables, Timer Variables and State Variables.
6. Functions: 
- emojiPattern(): Creates a dynamic pattern of custom characters on an LCD screen.
- toggleMusic(): A function that handles the toggling of music play state when the music button is pressed.
- playSound(): Plays a given sound on the speaker by generating tones.
- playMusic(): Starts the music playback using playSound().
- stopMusic(): Stops the music and playback.
- handleMusicPlayback(): Manages the playback of the song.
- turnOnLedStrip(): Turns on the LED strip with a white color.
- turnOffLedStrip(): Turns off the LED strip.
- alarmLedAnimation(): Creates an animation with the LED strip for the alarm state (using pink, blue, and purple colors).
- debounceButton(): A function for debouncing button presses to prevent multiple triggers.
- selectTimeForAlarm(): Allows the user to cycle through different alarm time options using button presses.
- toggleAlarm(): Toggles the alarm state between start and stop.
- startAlarm(): Starts the alarm, based on the selected time.
- stopAlarm(): Stops the alarm and resets its state.
- runAlarm(): Runs the alarm logic, updating the display and checking if the alarm time has expired.
7. Setup Function: Serial Communication, LCD Initialization, Button Initialization, LED Strip Initialization, Sensor Initialization and Initial Display.
8. Loop Function: Motion Detection, Button Handling, Alarm Control, Music Control and Alarm Running.

### Lab Functionalities in the Project
**Debugging with Serial Communication:** I used serial communication for debugging, as learned in the lab. This allowed me to monitor the system's behavior in real-time, identify potential errors, and track the status of alarms and music.

**Interrupts for Button Presses:** Interrupts were used to handle button presses, as demonstrated in the lab. The buttons for starting/stopping the alarm and for controlling the music are configured to trigger interrupts. This allows the program to respond immediately when a button is pressed, without continuously checking the button state in the main loop. 

**Timers for Alarm:** Timers, as taught in the lab, were used to implement a timing mechanism for the alarm. The system tracks the remaining time for the alarm to sound, updating the display and triggering actions accordingly.

**GPIO Pins for Connections:** As part of the project, I used General Purpose Input/Output (GPIO) pins for connecting various components, such as the motion sensor, buttons, LED strip, and speaker.

## Results
The project successfully achieved the intended functionality, with all components working to create an interactive mirror. The results of the implementation are as follows:
- **Motion Detection and LED Control:** The motion sensor correctly detects motion and activates the LED strip.
  
- **Alarm System:** The alarm system works as expected, with the ability to set various timers (7 seconds, 5 minutes, and 10 minutes). The alarm is triggered based on the selected timer and runs for the specified duration. When the alarm time is completed, the system automatically stops the alarm and provides feedback to the user via both the LCD and sound. The alarm LED animation successfully plays different colors in a sequence to provide visual alerts.
  
- **Music Playback:** The music control feature functions correctly. Pressing the dedicated button toggles the music state between playing and stopped. The system uses a speaker to play a predefined song.
  
- **Button Interaction and Interrupts:** The interrupt-driven button press mechanism works reliably. The buttons used for starting/stopping the alarm and toggling the music respond instantly to presses, and debounce functionality ensures that button presses are registered without noise or false triggering.
  
- **Display Feedback:** The LCD correctly displays messages to inform the user about the system's status. This includes showing the time remaining for the alarm, the selected timer, and messages for starting or stopping the alarm. The display also shows system status messages, such as "Hello, World!" during initialization and "Alarm Stopped!" when the alarm is deactivated.

- **Overall System Performance:** The system operates smoothly, with minimal delays and interruptions. All components, including the sensor, LEDs, speaker, and buttons, function together as expected.
  
## Conclusions
The **Intelligent Mirror** project successfully integrates various technologies and concepts learned in the lab.

## Source Code
### Directory Structure  
- **src/**: Contains all source code files.  
- **hardware/**: Contains schematics and diagrams.  
- **images/**: Contains project images linked in this README. 

## Journal
**12/3/2024**: Started documenting the Intelligent Mirror project, focusing on initial setup and planning.

**12/10/2024**: Implemented the hardware components of the Intelligent Mirror, including the PIR motion sensor, LCD display, speaker, buttons, and power supply.

**12/17/2024**: Completed the circuit schematic, block diagram, and detailed hardware description for the documentation.

**1/1/2025**: I finalized the hardware assembly, soldering the pins to the LED strip and ensuring all connections were secure. After completing the assembly, I tested the LED strip and the entire hardware setup to confirm everything functions correctly.

**1/4/2025**: I implemented and tested the code for the PIR sensor, ensuring it detects motion correctly, and also verified the functionality of the buttons.

**1/6/2025**: I implemented the code for the speaker to work with the previously configured alarm button. Additionally, I used Audacity to adjust and optimize the sound before playing it through the speaker.

**1/9/2025**: I connected a battery to power up the project.

**1/14/2025**: I created custom characters using Generator and displayed them on LCD using a pattern.

**1/15/2025**: Final project adjustments of software and documentation.

#### See It in Action
Watch the demo video to see how the project works and explore its features in action!

[Watch Demo Video](https://github.com/mariaxadina/Intelligent-Mirror/blob/main/images/DemoVideo.mp4)

[Watch Demo Video with Sensor](https://github.com/mariaxadina/Intelligent-Mirror/blob/main/images/DemoSensorAndFunctions.mp4)
## Bibliography/Resources
1. https://highlowtech.org/?p=1963
2. https://www.youtube.com/watch?v=tNNycZpvg-Y&ab_channel=AndrobotTECH
3. https://arduinointro.com/articles/projects/create-custom-characters-for-the-i2c-lcd-easily
## License
This project is licensed under the [MIT License](./LICENSE).
