#include <Servo.h>
#include <Wire.h>     
#include <LiquidCrystal_I2C.h> 

Servo myServo; 

int red1 = 3;
int green1 = 5;
int red2 = 10;
int green2 = 11;

const int ir1 = 2;
const int ir2 = 4;
const int ir3 = 7;

int posisiservo = 0;

int objectir1 = 0;
int objectir2 = 0;
int objectir3 = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);  
  myServo.attach(9);   
  myServo.write(0);    
  lcd.init();                  
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" SMART PARKING ");  
  lcd.setCursor(0, 1);
  lcd.print("   MANAGEMENT ");       
}

void loop() {
  
  objectir1 = digitalRead(ir1);
  objectir2 = digitalRead(ir2);
  objectir3 = digitalRead(ir3);

  if(objectir3 == LOW){
    if(posisiservo == 0){
      for (posisiservo = 0; posisiservo <= 90; posisiservo += 1) { 
      myServo.write(posisiservo);
      delay(10); 
      }
    }
    posisiservo = 90;  
    Serial.println("Servo ke 90 derajat"); 
  }else{
    if(posisiservo == 90){
      for (posisiservo = 90; posisiservo >= 0; posisiservo -= 1) { 
      myServo.write(posisiservo);
      delay(10); 
      }
    }
    posisiservo = 0;
    Serial.println("Servo ke 0 derajat");
  }
 
  if(objectir1 == HIGH && objectir2 == HIGH){
    

    lcd.setCursor(0, 0);
    lcd.print(" SMART PARKING ");  
    lcd.setCursor(0, 1);
    lcd.print(" 2 EMPTY SLOT  ");
    analogWrite(red1, 0);
    analogWrite(green1, 255);
    analogWrite(red2, 0);
    analogWrite(green2, 255);
    Serial.flush();
    
    if (Serial.available() > 0) {
      char command = Serial.read(); 
      
      if (command == '1') {
        if(posisiservo == 0){
          for (posisiservo = 0; posisiservo <= 90; posisiservo += 1) { 
          myServo.write(posisiservo);
          delay(10); 
          }
        }
        posisiservo = 90;  
        Serial.println("Servo ke 90 derajat");
        delay(5000);  
      } 
      else if (command == '0') {
          
        if(posisiservo == 90){
          for (posisiservo = 90; posisiservo >= 0; posisiservo -= 1) { 
          myServo.write(posisiservo);
          delay(10); 
          }
        }
        posisiservo = 0;
        Serial.println("Servo ke 0 derajat");
      }
      
    }
  }
  else if(objectir1 == LOW && objectir2 == HIGH){
    

    lcd.setCursor(0, 0);
    lcd.print(" SMART PARKING ");  
    lcd.setCursor(0, 1);
    lcd.print(" 1 EMPTY SLOT  ");
    analogWrite(red1, 255);
    analogWrite(green1, 0);
    analogWrite(red2, 0);
    analogWrite(green2, 255);

    if (Serial.available() > 0) {
      char command = Serial.read(); 
      
      if (command == '1') {
        if(posisiservo == 0){
          for (posisiservo = 0; posisiservo <= 90; posisiservo += 1) { 
          myServo.write(posisiservo);
          delay(10); 
          }
        }
        posisiservo = 90;  
        Serial.println("Servo ke 90 derajat");
        delay(5000);  
      } 
      else if (command == '0') {
          
        if(posisiservo == 90){
          for (posisiservo = 90; posisiservo >= 0; posisiservo -= 1) { 
          myServo.write(posisiservo);
          delay(10); 
          }
        }
        posisiservo = 0;
        Serial.println("Servo ke 0 derajat");
      }
      

    }
  }
  else if(objectir1 == HIGH && objectir2 == LOW){
    

    lcd.setCursor(0, 0);
    lcd.print(" SMART PARKING ");  
    lcd.setCursor(0, 1);
    lcd.print(" 1 EMPTY SLOT  ");
    analogWrite(red1, 0);
    analogWrite(green1, 255);
    analogWrite(red2, 255);
    analogWrite(green2, 0);

    if (Serial.available() > 0) {
      char command = Serial.read(); 
      
      if (command == '1') {
        if(posisiservo == 0){
          for (posisiservo = 0; posisiservo <= 90; posisiservo += 1) { 
          myServo.write(posisiservo);
          delay(10); 
          }
        }
        posisiservo = 90;  
        Serial.println("Servo ke 90 derajat"); 
        delay(5000); 
      } 
      else if (command == '0') {
          
        if(posisiservo == 90){
          for (posisiservo = 90; posisiservo >= 0; posisiservo -= 1) { 
          myServo.write(posisiservo);
          delay(10); 
          }
        }
        posisiservo = 0;
        Serial.println("Servo ke 0 derajat");
      }
      

    }
  }
  else{
    Serial.flush();
    lcd.setCursor(0, 0);
    lcd.print(" SMART PARKING ");  
    lcd.setCursor(0, 1);
    lcd.print(" PARKING FULL  ");

    analogWrite(red1, 255);
    analogWrite(green1, 0);
    analogWrite(red2, 255);
    analogWrite(green2, 0);
    if (Serial.available() > 0) {
      char command = Serial.read(); 
      
      if (command == '1') {
        if(posisiservo == 90){
          for (posisiservo = 90; posisiservo >= 0; posisiservo -= 1) { 
          myServo.write(posisiservo);
          delay(10); 
          }
        }
        posisiservo = 0;
        Serial.println("Servo ke 0 derajat");  
      } 
      else if (command == '0') {
          
        if(posisiservo == 90){
          for (posisiservo = 90; posisiservo >= 0; posisiservo -= 1) { 
          myServo.write(posisiservo);
          delay(10); 
          }
        }
        posisiservo = 0;
        Serial.println("Servo ke 0 derajat");
      }
    }  
  }

}
