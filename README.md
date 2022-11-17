# Pocket Air Quality Index Monitor

## Why AQI Monitor is needed?
Carry Air Pocket Monitor before stepping out of your house in order to know the quality of the air you’re breathing. The pocket-sized air monitoring device is handy and easy to carry around.

It helps you understand the level of Particulate Matter 2.5 of your location. Works as both – real-time indoor and outdoor air quality monitoring sensor; the LCD display shows you PM reading indicating if the air is safe or not.

Having a desktop friendly version helps to determine the quality of air which can help you improving your life and work quality.

<br>

## Features of our AQI Monitor
- Shows the value of PM2.5 along with the safety level.
- Shows simultaneous value of PM1.0, PM2.5 and PM10.
- Plots the graph of PM2.5 on a graph in difference of 5 minutes.
- Approx. 1.5 hours Battery Backup.
- Type C charging support.

<br>

## How to assemble the project
1. Download the latest version of firmware from the /Firmware folder
2. Edit the Firmware as per the requirement with the help of guide provided in /Firmware/README.md
3. Order the components from the Bill of Materials as per the requirement.
4. Make the Hardware circuit
   1.  Solder them on General Purpose PCB Board using the design below (or)
   2.  Order the PCB by providing the PCB Developer with the gerber file available in /Hardware/PCB_Gerber.zip and solder all the component on it
5.  Upload the firmware on the the hardware

<br>

## Schematic Design
<img width="500px" align="center" alt="Circuit Schematic" src="Hardware/Schematic.png" />
<br><br>

<!-- ## PCB Design
<img width="500px" align="left" alt="PCB Design" src="Hardware/PCB Design.png">
<br><br><br><br> -->

## How to use the device
1. Press the push button to turn on the device.
2. The device will start with a bootup screen with the company logo.
3. The landing page will show the value of PM 2.5 of screen.
4. Press the change screen button to switch between pages. The device works in 3 modes:
   1. Live PM 2.5 data screen.
   2. Live PM 1.0, PM 2.5, PM 10 data screen.
   3. PM 2.5 graph screen which plots the value of PM 2.5 in bar graph at an interval of 5 mins.

<br>

## Bill of Materials
| Component | Buy Link | Quantity |
|-----------|----------|----------|
|Arduino Nano|https://www.electronicscomp.com/arduino-nano-3.0-development-board?search=arduino%20nano|1|
|PMS Air Particle Dust Sensor|https://www.electronicscomp.com/pms7003-sensor-module-pm2.5-air-particle-dust-sensor?search=pms%20sensor|1|
|TM1637 4 x 7 Segment Display|https://www.electronicscomp.com/tm1637-4-digits-7-segment-led-display-module-with-clock-for-arduino?search=tm1637|1|
|1.8" TFT LCD (128 x 160 pixels)|https://www.electronicscomp.com/1.8-inch-tft-lcd-module-128x160-with-4-io?search=1.8%20tft|1|
|1k Ohm 1/4 Watt THT Resistor|https://www.electronicscomp.com/1k-ohm-resistance?search=1k%20resistor|4|
|XL6009 Boost Converter|https://www.electronicscomp.com/xl6009-dc-dc-adjustable-step-up-boost-power-converter-module-india?search=xl6009|1|
|1N4007 1A Diode|https://www.electronicscomp.com/1n4007-diode?search=1n4007|2|
|TP4056 Module (Type C)|https://www.electronicscomp.com/tp4056-1a-li-ion-lithium-battery-charging-module-with-current-protection-type-c?search=tp4056|1|
|7 x 7 mm Push Switch|https://www.electronicscomp.com/push-switch-non-locking-6pin?gclid=Cj0KCQiAq7COBhC2ARIsANsPATHrl1eFRUm9aj9fV5nQhOWSY-DTgY14UJ8K7TpmNlkErdsdw3PRDSMaAhYHEALw_wcB|1|
|5 x 5 mm Push Button Switch|https://www.electronicscomp.com/push-button-switch-2-pin-5mm?search=push%20button|1|
|3500 mAH Li-Po Battery|https://www.electronicscomp.com/3.7v-3500mah-lipo-battery-model-kp-406090-india?search=500%20mAh|1|
|2mm Blue LED|https://www.roboelements.com/product/5pcs-3mm-blue-led/?gclid=Cj0KCQiAq7COBhC2ARIsANsPATGL7wa7CufQcjKscsp10lo9DEvm4cgmpSG2u2ZRz8-nCg5U4CRUbyAaAhBfEALw_wcB|1|

<br>

<!-- ## Photographs
<img width="500px" align="left" alt="Device Photograph 1" src="/Resources/Device Images/image1.png">
<br><br><br><br> -->

## Tools Used
<img width="40px" align="left" alt="Arduino" src="Resources/Logos/Arduino Logo.png">
<img width="30px" align="left" alt="C" src="Resources/Logos/C Logo.jpeg">
<img width="25px" align="left" alt="CPP" src="Resources/Logos/CPP Logo.jpeg">
<img width="80px" align="left" alt="Git" src="Resources/Logos/Git Logo.jpeg">
<img width="35px" align="left" alt="GitHub" src="Resources/Logos/GitHub Logo.jpeg">
<img width="35px" align="left" alt="VS Code" src="Resources/Logos/VS Code.jpeg">
<img width="30px" align="left" alt="Eagle" src="Resources/Logos/Eagle Logo.png">
<img width="22px" align="left" alt="Fusion 360" src="Resources/Logos/Fusion 360 Logo.png">

<br><br>

## Design Details
- Designed for: Ecologic Pvt. Ltd.
- Designed by: [Parth Patel](mailto:parth.pmech@gmail.com)