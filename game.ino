#include <LiquidCrystal_I2C.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 16, 2);
int positionX = 8;
int positionY = 1;
int xAxisPin = 0;           // define X pin of Joystick  
int yAxisPin = 1;           // define Y pin of Joystick 
int zAxisPin = 8;           // define Z pin of Joystick 
int xVal, yVal, zVal; 

void setup() {
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();                // initialize the lcd
  lcd.backlight();           // Turn on backlight
  lcd.print("The game");// Print a message to the LCD
  pinMode(zAxisPin, INPUT_PULLUP);    // initialize the port to pull-up input 
  Serial.begin(9600);         // initialize the serial port with baud rate 9600 
  delay(1000);
  lcd.clear();
  lcd.print("GAME START!");
  delay(500);
  lcd.clear();
  lcd.setCursor(8, 1);// set the cursor to column 0, line 1
  lcd.print("o");
}

void loop() {
  xVal = analogRead(xAxisPin); 
  yVal = analogRead(yAxisPin);   
  zVal = digitalRead(zAxisPin);

  if(zVal != 1) {
    lcd.setCursor(0, 0);
    lcd.print("X: ");
    lcd.print(xVal);
    lcd.print(",");
    lcd.setCursor(0, 1);
    lcd.print("Y: ");
    lcd.print(yVal);
    lcd.print("Z: ");
    lcd.print(zVal);

    lcd.clear();
  } else {

    lcd.setCursor(10, 1);
    lcd.print("|");

    if(positionY == 1 && positionX == 10) {
      bool isEnd = true; 
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("GAME OVER!");
      delay(1000);
      lcd.clear();
      while(isEnd) {
        xVal = analogRead(xAxisPin); 
        lcd.setCursor(0, 0);
        lcd.print("SX continua");
        lcd.setCursor(0, 1);
        lcd.print("DX esci");

        if (xVal < 510) {
          lcd.clear();
          lcd.print("GAME START!");
          delay(500);
          lcd.clear();
          positionX = 8;
          positionY = 1;
          lcd.setCursor(8, 1);// set the cursor to column 0, line 1
          lcd.print("o");
          isEnd = false;
        } 
        if(xVal > 530) {
          while(true) {
            lcd.clear();
            lcd.print("SEE YOU LATER!");
            delay(300);
          }
        }
      }
    }

    // DOWN position
    if( yVal > 525 && xVal > 510 && xVal < 530){
      positionY = 1;

      lcd.clear();
      lcd.setCursor(positionX, positionY);
      lcd.print("o");
    }

    // UP position
    if( yVal < 510 && xVal > 510 && xVal < 530){
      positionY = 0;

      lcd.clear();
      lcd.setCursor(positionX, positionY);
      lcd.print("o");
    }

    // LEFT position
    if(xVal < 510 && yVal > 510 && yVal < 525){
      positionX--;
      if(positionX < 0) {
        positionX = 0;
      }
      lcd.clear();
      lcd.setCursor(positionX, positionY);
      lcd.print("o");
    }

    // RIGHT position
    if(xVal > 530 && yVal > 510 && yVal < 525) {
      positionX++;
      if(positionX > 15) {
        positionX = 15;
      }
      lcd.clear();
      lcd.setCursor(positionX, positionY);
      lcd.print("o");
    }

    delay(150);
  }

}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}