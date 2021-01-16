#include <LiquidCrystal_I2C.h>       
LiquidCrystal_I2C lcd(0x27,16,2);  //for 16x2 lcd display

int buzzer = 10;
int GASA0 = A0;
int gasvalue;


void setup() {
  
lcd.begin();     // initiate the lcd                  
 lcd.backlight(); 
 Serial.begin(9600);
 pinMode(buzzer, OUTPUT); 
 lcd.setCursor(2,0);
 lcd.print("Gas leakage"); 
 lcd.setCursor(4,1);
 lcd.print("Detector"); 
 delay(3500);    
 lcd.clear(); 
}

void loop() {
  int sen = analogRead(GASA0);
  int gasvalue = (sen - 35)/50;
 
  lcd.setCursor(0,0);
  lcd.print("Gas Level:");
  lcd.setCursor(10,0);
  lcd.print(gasvalue);
  lcd.setCursor(12,0);
  lcd.print("%");
  
  // Checks if it has reached the threshold value
  if (gasvalue >= 8)              //gas percentage alert
  {
    lcd.setCursor(0,1);
  lcd.print("Gas Leaked");
    digitalWrite(buzzer, HIGH);
  }
  else
  {
  lcd.setCursor(0,1);
  lcd.print("NORMAL");
    noTone(buzzer);
    
  }
  delay(500);
  lcd.clear();
}
