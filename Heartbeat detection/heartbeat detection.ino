


#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <LiquidCrystal_I2C.h>       
LiquidCrystal_I2C lcd(0x27,16,2);  //for 16x2 lcd display

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
const int buzzer = 8;                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   

  Serial.begin(9600);          // For Serial Monitor
 lcd.begin();
 lcd.backlight();
 lcd.setCursor(2,0);
 lcd.print("Heart Attack"); 
 lcd.setCursor(3,1);
 lcd.print("Detection"); 
 delay(2400);    
 lcd.clear(); 
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
 
}



void loop() {

 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
 lcd.setCursor(0,0);
 lcd.print("Beats Per Minute");                                                // "myBPM" hold this BPM value now. 
  lcd.setCursor(0,1);
 lcd.print("BPM=");
  
if (pulseSensor.sawStartOfBeat()) {  
    // Constantly test to see if "a beat happened". 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);   // Print the value inside of myBPM. 
  lcd.setCursor(4,1);
  lcd.print(myBPM);
  delay(980); 
  lcd.clear(); 
 
  if (myBPM > 120 || myBPM < 40)
  {
     lcd.setCursor(0,0);
 lcd.print("Abnormal BPM !!!"); 
     lcd.setCursor(0,1);
 lcd.print("BPM="); 
  lcd.setCursor(4,1);
 lcd.print(myBPM); 
     digitalWrite(buzzer,HIGH);
     delay(1800);
  digitalWrite(buzzer,LOW);
  lcd.clear();

  }
}

  delay(20);                    // considered best practice in a simple sketch.

}

  
