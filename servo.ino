#include <Servo.h>             //Servo library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

// COM3
 
Servo servo_test;        //initialize a servo object for the connected servo  
                
int angle = 0;    
int buttonPin = 2;
int servoPin = 9;
int buttonState = 0;
int OPEN = 0;
int drugRelease = 3;
int buttonStateDrug = 0;
int speaker = 8;
int second_lcd_pin = 4;
int stopper_pin = 5;
int relay_pin = 6;
int sensor_value = 0;
float pressure = 0.0;
int count = 0;
 
void setup() 
{ 
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW);
  // buttons
  servo_test.attach(servoPin); // attach the signal pin of servo to pin9 of arduino
  pinMode(buttonPin, INPUT);
  pinMode(drugRelease, INPUT);
  pinMode(second_lcd_pin, OUTPUT);
  pinMode(stopper_pin, OUTPUT);

  Serial.begin(9600);

  // lcd
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  //lcd.backlight();// To Power OFF the back light

  // speaker
  pinMode(speaker, OUTPUT);

  // initializing
  lcd.setCursor(0,0);
  lcd.print("Initializing...");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press Button");
  lcd.setCursor(0,1);
  lcd.print("To Build Plaque");

  digitalWrite(relay_pin, HIGH);
} 
  
void loop() 
{ 

  if (count > 500){
    count = 0;
    sensor_value = analogRead(A0);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    pressure = sensor_value * (5.0 / 1023.0);
  
    if (pressure > 4){
    digitalWrite(relay_pin, LOW);
    delay(5000);
    sensor_value = analogRead(A0);
    pressure = sensor_value * (5.0 / 1023.0);
    if (pressure < 4){
      digitalWrite(relay_pin, HIGH);
      
    }
    }
    
  }

  count = count + 1;

  

  buttonState = digitalRead(buttonPin);
  buttonStateDrug = digitalRead(drugRelease);

  
  Serial.println(pressure);
  
  // button for plaque build up pressed
  
  if (buttonState == HIGH && OPEN == 0) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Please Wait...");
    for(angle = 0; angle < 180; angle += 1){                            
    servo_test.write(angle);                 
    delay(20);                       
  } 
  digitalWrite(second_lcd_pin, HIGH);
  OPEN = 1;
  lcd.clear();
  for(int i = 0; i < 100; i += random(1, 15)){                               
  lcd.setCursor(0,0);
  lcd.print("% blockage");
  lcd.setCursor(0,1);
  lcd.print(i);                 
  delay(750);                       
  }
  digitalWrite(second_lcd_pin, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PROBLEM!");
  lcd.setCursor(0,1);
  lcd.print("Inject Drug!");
  digitalWrite(speaker, HIGH);
  }

// button for reset pressed
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH && OPEN == 1) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Resetting...");
    digitalWrite(speaker, LOW);
    for (angle = 180; angle >= 0; angle -= 1){
      servo_test.write(angle);
      delay(5);
    }
  OPEN = 0;
  digitalWrite(stopper_pin, HIGH);
  lcd.clear();
  digitalWrite(stopper_pin, LOW);
//  for(int i = 90; i >=0 ; i -= random(1,15)){                               
//  lcd.setCursor(0,0);
//  lcd.print("% blockage");
//  lcd.setCursor(0,1);
//  lcd.print(i);                 
//  delay(20);                       
  //}
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("System Ready");
  }

// button pressed to release drug
  buttonState = digitalRead(buttonPin);

  if (buttonStateDrug == HIGH && OPEN == 1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Releasing Drug");
    digitalWrite(speaker, LOW);
    digitalWrite(stopper_pin, LOW);
    for (angle = 180; angle >= 0; angle -= 1){
      servo_test.write(angle);
      delay(20);
    }
  OPEN = 0;
  digitalWrite(stopper_pin, HIGH);
  lcd.clear();
  digitalWrite(stopper_pin, LOW);
//  for(int i = 90; i >=0 ; i -= random(1,15)){                               
//  lcd.setCursor(0,0);
//  lcd.print("% blockage");
//  lcd.setCursor(0,1);
//  lcd.print(i);                 
//  delay(1);                       
  //}
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("System Ready");
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("Press Button");
  lcd.setCursor(0,1);
  lcd.print("To Build Plaque");
  }
  
}
