/*This code was written for the 2017 PolyHacks event.
  The code below is the intellectual property of Samuel Roberti, Caleb Riggs, and Brian Walsh.
  Use for all baby-saving purposes is authorized.
 */



#include <CurieBLE.h>


BLEPeripheral blePeripheral;  // BLE Peripheral Device 
BLEService BSService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE Baby-Saving Service



BLEUnsignedCharCharacteristic occCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);// This characteristic is read by the Android app.  It is always either a 0 or 1.

#define soundPin A0// The sound sensor
#define pressPin 4// The button sensor
#define tempPin A2// The temperature sensor
#define beepPin 3// The beeping alarm



void setup() {
  pinMode(soundPin, INPUT);// Initialize pin modes.
  pinMode(pressPin, INPUT);
  pinMode(tempPin, INPUT);
  pinMode(beepPin, OUTPUT);

  blePeripheral.setLocalName("BBYSAV");                     //Sets the name of the device, to be broadcast over BLE.
  blePeripheral.setAdvertisedServiceUuid(BSService.uuid()); // Assigns the main service to be advertised over BLE.

  blePeripheral.addAttribute(BSService);                    //Adds the main service and characteristic as attributes of the peripheral. 
  blePeripheral.addAttribute(occCharacteristic);
  
  blePeripheral.begin();                                    // Begin broadcasting.
                           
  
}

void loop() {
  
  
  
  if(analogRead(soundPin)>900){    // If a noise above a certain volume is detected(which, in most situations, would be the car door closing), check pressure sensors to see if the vehicle still has baby inside.
   if(digitalRead(pressPin)==HIGH){
     occCharacteristic.setValue(1);
  }
   else{
     occCharacteristic.setValue(0);
  }
 }
   int a = analogRead(tempPin);  // Calculate current temperature.
   int B = 4275;

   float R = 1023.0/((float)a)-1.0;
   R = 100000.0*R;

   float temperature=1.0/(log(R/100000.0)/B+1/298.15)-273.15;
  if(temperature > 90){                                         // If the temperature is above the threshhold of danger, check pressure sensor.  If the baby is present, sound a loud beeper.
    if(digitalRead(pressPin)==HIGH){
      digitalWrite(beepPin, HIGH);
      delay(200);
      digitalWrite(beepPin, LOW);
      delay(200);
      digitalWrite(beepPin, HIGH);
      delay(200);
      digitalWrite(beepPin, LOW);
      delay(200);
      digitalWrite(beepPin, HIGH);
      delay(200);
      digitalWrite(beepPin, LOW);
      delay(200);
      digitalWrite(beepPin, HIGH);
      delay(200);
      digitalWrite(beepPin, LOW);
      delay(200);
      digitalWrite(beepPin, HIGH);
      delay(500);
      digitalWrite(beepPin, LOW);
      delay(200);
      
    }
    
  }

  
  }

  

  



