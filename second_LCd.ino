#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
// COM4

int starter_pin = 4;
int stopper_pin = 5;
int starter_pin_state = LOW;
int stopper_pin_state = LOW;
float pressure = 0;
float randNum;
int start = 0;
int stopp = 0;
int count = 0;
int sensor_value = 0;

void setup() {
  // put your setup code here, to run once:

  // lcd
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  //lcd.backlight();// To Power OFF the back light

  pinMode(starter_pin, INPUT);
  pinMode(stopper_pin, INPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("System Pressure");
  lcd.setCursor(0,1);
  lcd.print("Monitor");

  delay(5000);
  


}

void loop() {
  count = count + 1;
  if (count > 100){
  count = 0;
  sensor_value = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  pressure = sensor_value * (5.0 / 1023.0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("System Pressure");
  lcd.setCursor(0,1);
  lcd.print(pressure);
  lcd.setCursor(6,1);
  lcd.print("PSI");
  delay(1000);


  
}
  
//  if (start == 0){
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("System Pressure");
//    lcd.setCursor(0,1);
//    lcd.print(random(20,25)/100.0);
//    lcd.setCursor(6,1);
//    lcd.print("PSI");
//    delay(1000);
//  }
//
//  starter_pin_state = digitalRead(starter_pin);
//  Serial.println(starter_pin_state);
//  
//  if (starter_pin_state == HIGH && stopp == 0){
//    start = 1;
//    for(pressure = 0.3; pressure <= 2.5; pressure += random(1, 5)/10.0){                 
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("System Pressure");
//    lcd.setCursor(0,1);
//    lcd.print(pressure);
//    lcd.setCursor(5,1);
//    lcd.print("PSI");           
//    delay(1000);                       
//  }
//  stopp = 1;
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Pressure HIGH!");
//  }
//
//  stopper_pin_state = digitalRead(stopper_pin);
//
//  if (stopper_pin_state == HIGH && start == 1){
//    for(float pressure_new = pressure; pressure_new >= 0.22; pressure_new -= random(1, 5)/10.0){    
//    Serial.println(pressure_new);               
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("System Pressure");
//    lcd.setCursor(0,1);
//    lcd.print(pressure_new);
//    lcd.setCursor(5,1);
//    lcd.print("PSI");           
//    delay(750);                       
//  }
//  start = 0;
//  stopp = 0;
//  }
//  
  

}
