#include <ezButton.h>

#include <LiquidCrystal_I2C.h>

#include <Wire.h>

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x27;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
int nPulses = 0;
float nmeterperpedalstroke = .628648;
float nmileperpedalstroke = .000390625;
int nmeterstraveled;
float nMilesTraveled;
float nSeconds;
float nCalories;

//calculations
//magnet radius ~ .054 meters
//circumference = pi*2*r = .33929 meters
//gear ratio = 3.2857

ezButton button1(7);  // create ezButton object that attach to pin 7;
//ezButton button2(7);  // create ezButton object that attach to pin 7;

void setup() {
  //SPLASH SCREEN AT STARTUP
  lcd.init(); // initialize the lcd
  lcd.backlight();

  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  lcd.print("734 BOYS ||--||"); // print message at (0, 0)
  delay(3000);
  lcd.clear();
  Serial.begin(115200);
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds

  while (!button1.isPressed())
    button1.loop(); // MUST call the loop() function first

  //button2.setDebounceTime(50); // set debounce time to 50 milliseconds
  pinMode(8, INPUT);


}

void loop() {
  button1.loop(); // MUST call the loop() function first

  //int btn1State = button1.getState();
  // cd.print("Start Pedaling!");

  //if(button1.isReleased())
  //delay(3000);
  // lcd.clear();

  while (digitalRead(8) == LOW)
    delay(10);
  while (digitalRead(8) == HIGH)
    delay(10);
  //------------Elaborations--------------
  nPulses++;
  nmeterstraveled = nPulses * nmeterperpedalstroke;
  nMilesTraveled = nPulses * nmileperpedalstroke;
  nSeconds = millis() / 1000;
  nCalories = nPulses / 77.9150666;
  //----------Screen-----------------
  lcd.setCursor(0, 0);
  lcd.print("Rotations: ");
  lcd.print(nPulses);
  lcd.setCursor(0, 1);
  lcd.print("Meters: ");
  lcd.print(nmeterstraveled);
  lcd.setCursor(0, 2);
  lcd.print("Cals: ");
  lcd.print(nCalories);
  lcd.setCursor(0, 3);
  lcd.print("Mi: ");
  lcd.print(nMilesTraveled);

  delay(10);
}
