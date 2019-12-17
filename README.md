# Atherosclerosis_Arduino_Code

This readme file will help you in navigating the code we wrote to run the plaque simulator exhibit. There are two files: servo.ino and second_lcd.ino. THe servo.ino file is the main driver that controls the buttons and their interactions with the servo motor and the two LCD screens. We found that it was extremely difficult to power a second LCD screen using the same Ardunio board so we used a second board. This second board is controlled by the first board and the script for this board is in the file second_lcd.ino. 

The servo.ino file controls these specific functions:
1. Initialize the system and the two LCD screens 
2. When plaque buildup button is pressed, disable the buttons and move the servo motor to the correct position to build plaque 
3. Power the buzzer when plaque builds up 
4. Use a sampling schedule to show pressure readings from the Honeywell pressure sensor on the second LCD
5. Enable the buttons 
6. When drug release button is pressed, the servo motor is reset 
7. System reset to be used again

The second_lcd.ino file controls:
1. Show pressure readings on the second lcd 
2. Show pressure is high when it crosses 3 PSI 

