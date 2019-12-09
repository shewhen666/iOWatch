
#include <Wire.h>                    // library for communication with I2C - DS3231
                                     // https://www.arduino.cc/en/Reference/Wire
#include "RTClib.h"                  // library for Real Time Clock
                                     // https://github.com/adafruit/RTClib.git
#include "LowPower.h"                // library for deep sleep
                                     // https://github.com/rocketscream/Low-Power.git
#include "OneButton.h"               // library for button (short press /double press /long press)
                                     // https://github.com/mathertel/OneButton.git


RTC_DS3231 rtc;                      // RealTimeClock object

byte hours;                          // hours variable       
byte minutesFive;                    // minutes variable
byte minutesOne;                     // minutes variable
byte minutesOnFive;                  // minutes variable
byte temperatures;                   // temperature variable
byte temperaturesOnFive;             // temperature variable

byte settingHours = 0;               // variable initialization
byte settingMinutes = 0;             // variable initialization
byte settingMinutesToFive = 0;       // variable initialization

const byte leds[24] = {10, A0, A1, A2, A3, 13, 4, 5, 6, 7, 8, 9};  // 12 LED's array pin assigning

static byte buttonPin = 2;                           // assigning button pin value
static byte buttonPin2 = 3;                           // assigning button pin value

boolean timeSettingMode = false;               // time setting mode
boolean timeSettingModeHours = false;          // time setting mode hours [0, 11]
boolean timeSettingModeMinutes = false;        // time setting mode minutes [0, 5, 10, .., 55]
boolean timeSettingModeMinutesToFive = false;  // time setting mode minutes [0-4]

OneButton button(2, true);      // button
OneButton button2(3, true);      // button

void setup () {
  Serial.begin(9600);         //enabling serial communication at 9600 boud rate

  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    // following line sets the RTC to the date & time this sketch was compiled
  rtc.adjust(DateTime(2019, 1, 1, 0, 0, 0));           //year, month, day, hour, minute, second

  for (int i=0; i<=12; i++){
    pinMode(leds[i], OUTPUT);             // assigning all pins in array as output
  }

  allOn();          //bootup all LED's turning
  allOff();         //turning all LED's off

  delay(40);

  attachInterrupt(0, wakeFunction, FALLING);        //interrupt for waking up
  attachInterrupt(1, wakeFunction, FALLING);        //interrupt for waking up
  button.attachDoubleClick(doubleclick);            // link the function to be called on a doubleclick event.
  button.attachClick(singleclick);                  // link the function to be called on a singleclick event.
  button.attachLongPressStop(longclick);            // link the function to be called on a longpress event.
  button2.attachDoubleClick(doubleclick);            // link the function to be called on a doubleclick event.
  button2.attachClick(singleclick);                  // link the function to be called on a singleclick event.
  button2.attachLongPressStop(longclick);            // link the function to be called on a longpress event.
  shutdownNow();      //calling deep sleep function
}

void loop (){
  
   button.tick();     //checking if button is pressed and long
   delay(10);         //needed for stable operation and for button ticking
   button2.tick();     //checking if button is pressed and long
   
   
}

void wakeFunction(){  //interrupt function when button is presse
  
}

void singleclick(){   //single Click button
 if(!timeSettingMode){

    unsigned int DelayHoursLedON = 500;           // how long will hour LED light up after getting time (in microseconds)
    unsigned int DelayHoursLedOFF = 300;          // how long will hour LED stay off after showing time (in microseconds)
    unsigned int DelayMinutesLedON = 150;         // how long will minutes LED light up after getting time in microseconds
    unsigned int DelayMinutesLedOFF = 280;        // how long will minutes LED stay off after showing time in microseconds
    
    DateTime now = rtc.now();     //gets the current time from DST

    hours = now.hour();

    minutesOne = now.minute();
    minutesFive = minutesOne/5;

    if(hours >= 12){
      hours = hours - 12;
    }
      
    digitalWrite(leds[hours],HIGH);
    delay(DelayHoursLedON);
    digitalWrite(leds[hours],LOW);
    delay(DelayHoursLedOFF);
  
    digitalWrite(leds[minutesFive],HIGH);
    delay(DelayHoursLedON);
    digitalWrite(leds[minutesFive],LOW);
    delay(DelayHoursLedOFF);
            
     minutesOnFive = minutesOne - (minutesFive * 5);
          
    for (int i=1; i <= minutesOnFive ; i++){   
       digitalWrite(leds[i], HIGH);
       delay(DelayMinutesLedOFF);
    } 
    for (int i=1; i <= minutesOnFive ; i++){       
      digitalWrite(leds[i], LOW);
      delay(DelayMinutesLedON);
    }
   shutdownNow();
 }else{
  if(timeSettingModeHours){         //hours scrolling trough LED's
    digitalWrite(leds[settingHours], LOW);
    if(settingHours == 11){
      settingHours = 0;
      digitalWrite(leds[settingHours], HIGH);
    }else{
      settingHours++;
      digitalWrite(leds[settingHours], HIGH);
    }
  }
  if(timeSettingModeMinutes){       //minutes scrolling trough LED's
    digitalWrite(leds[settingMinutes], LOW);
    if(settingMinutes == 11){
      settingMinutes = 0;
      digitalWrite(leds[settingMinutes], HIGH);
    }else{
      settingMinutes++;
      digitalWrite(leds[settingMinutes], HIGH);
    }
  }
  if(timeSettingModeMinutesToFive){       //minutes to five scrolling trough LED's
    digitalWrite(leds[settingMinutesToFive], LOW);
    if(settingMinutesToFive == 4){
      settingMinutesToFive = 0;
      digitalWrite(leds[settingMinutesToFive], HIGH);
    }else{
      settingMinutesToFive++;
      digitalWrite(leds[settingMinutesToFive], HIGH);
    }
  }
 }
}

void longclick(){         //longclick function for time setting
  if(timeSettingModeMinutesToFive && !timeSettingModeMinutes){
    timeSettingModeMinutes = true;  // pass
  }

  if(timeSettingMode){
    if(timeSettingModeMinutes){
      if(timeSettingModeMinutesToFive){
        rtc.adjust(DateTime(2018, 12, 16, settingHours, (settingMinutes *5) + settingMinutesToFive,0 )); // setting desiered time
        /*
        Serial.print("Changing TIME to ");
        Serial.print(settingHours);
        Serial.print("h ");
        Serial.print((settingMinutes*5)+settingMinutesToFive);
        Serial.println("min ");
        */
        timeSettingMode = false;                  // exiting timeSetting MODE
        timeSettingModeMinutesToFive = false;     // exiting minutes to five MENU
        timeSettingModeMinutes = false;           // exiting minutes MENU
        settingMinutesToFive = 0;                 // reseting MinutesToFive
        settingMinutes = 0;                       // reseting Minutes
        settingHours = 0;                         // reseting hours
        allOn();                                  // turning all LED's on
        allOff();                                 // turning all LED's off
        singleclick();                            // showing time
        
      }else{
        timeSettingModeMinutesToFive = true;      // entering minutesToFive MENU (rest of the minutes)
        timeSettingModeMinutes = false;           // exiting minutes MENU
        allOff();                                 // turning all LED's off
        digitalWrite(leds[settingMinutesToFive], HIGH);
      }
    }else{
     timeSettingModeMinutes = true;     // entering minutes MENU
     timeSettingModeHours = false;      // exiting hours MENU
     allOff();          //turning all LED's off
     digitalWrite(leds[settingMinutes], HIGH);
    }
    }else{
    timeSettingMode = true;         // activating timeSetting mode
    timeSettingModeHours = true;    // entering hours MENU
    digitalWrite(leds[settingHours], HIGH);
  }
}

void doubleclick(){           //function displaying the temperature
  if(!timeSettingMode){

    allOff();         //turning all LED's off
    
    unsigned int DelayTemperatureLedON = 150;     // how long will minutes LED light up after getting time in microseconds
    unsigned int DelayTemperatureLedOFF = 280;    // how long will minutes LED stay off after showing time in microseconds
      
    temperatures = rtc.getTemperature();
    temperaturesOnFive = temperatures / 5;
    for (int i=0; i <= temperaturesOnFive ; i++){ 
      digitalWrite(leds[i], HIGH);
      delay(500);
    } 
    for (int i=0; i <= temperaturesOnFive ; i++){  
     digitalWrite(leds[i], LOW);
     delay(200);
    }
    delay(500);
    temperatures = temperatures - (temperaturesOnFive * 5);
    for (int i=1; i <= temperatures ; i++){
      digitalWrite(leds[i], HIGH);
      delay(500);
    }
    for (int i=1; i <= temperatures ; i++){       
     digitalWrite(leds[i], LOW);
     delay(200);
    }
    
     shutdownNow();
  }
}

void allOff(){
  for (int i=0; i<=12; i++){
    digitalWrite(leds[i], LOW);       //turning all LED's off
  }  
}

void allOn(){         //function turning all LED's on in specific pattern
  digitalWrite(leds[3], HIGH);
  digitalWrite(leds[6], HIGH);
  digitalWrite(leds[9], HIGH);
  digitalWrite(leds[0], HIGH);
  delay(300);
  for (int i=1; i<=2; i++){
    digitalWrite(leds[i], HIGH);
    delay(150);
  }
  for(int i=11; i>=10; i--){
    digitalWrite(leds[i], HIGH);
    delay(150);  
  }
  for(int i=5; i>=4; i--){
    digitalWrite(leds[i], HIGH);
    delay(150);  
  }
  for (int i=7; i<=8; i++){
    digitalWrite(leds[i], HIGH);
    delay(150);
  }
}

void shutdownNow(){
    allOff();
//  Serial.println("going to sleep");
    delay(500);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); //deep sleep
}

