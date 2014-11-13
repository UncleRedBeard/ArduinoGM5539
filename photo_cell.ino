/****************************************************************
 * File:    photo_cell                                          *
 * Author:  Uncle Red Beard (Shawn Kelley)                      *
 * Date:    12-NOV-2014                                         *
 * Desc:    Connect photocell  resistor GM 5539 5539 to arduino *
 *          and log data to file and serial                     *
 * **************************************************************/
 
 #include <SD.h>
 
 File tFile;
 const int chipSelect = 4;
 const int photocellPin = 0;
 int photocellReading;         // the analog reading from the sensor divider
 const int LEDpin = 11;        // connect Red LED to pin 11 (PWM pin)
  int LEDbrightness;           //
 unsigned long timer = 60000;  //1 minute
 
 
 void setup(void)
 {
   Serial.begin(9600);
   
   //SD card setup
   Serial.println("\nInitialzing SD card...");
   pinMode(10, OUTPUT);
   
   if (!SD.begin(4))
   {
     Serial.println("\ninitialization failed!!");
     Serial.println("did you remember to insert the SD card, dumbass???");
     return;
   }
   Serial.println("\nIT IS ALIIIIIIVE!!!\n");
   
   if (SD.exists("lumin.csv")){
     SD.remove("lumin.csv");
   }
     
 }
 
 void loop(void)
 {
   // photocell 
   photocellReading = analogRead(photocellPin);
   
   Serial.print("\nAnalog reading = ");
   Serial.println(photocellReading);    // the raw reading
   
   // LED gets brighter the darker it is at the sensor
   // that means we have to -invert- the reading from 0-1023 back to 1023-0
   photocellReading = 1023 - photocellReading;
   // now we have to map 0-1023 to 0-255 sing that's the range analogWrite uses
   LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
   analogWrite(LEDpin, LEDbrightness);
   
   delay(timer);
 }
