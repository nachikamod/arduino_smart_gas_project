#define enable_ckt 12
#define enable_flame_det 11
#define sonic_trig 6
#define sonic_echo 7
#define gas_det A0
#define turn_off_gas 2
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

long duration, cm, inches;

int __knob_check__ = 0, __pos_cont__, __flame_check__ = 1, __enable_pir__, __motion_detect__ = 0, __enable_gas_sensor__, __gas_detect__;
int timer_flame = 0, timer_pir = 0;

void setup() {

  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(INPUT, enable_ckt);
  pinMode(INPUT, enable_flame_det);
  pinMode(INPUT, gas_det);
  pinMode(OUTPUT, sonic_trig);
  pinMode(INPUT, sonic_echo);
  pinMode(OUTPUT, turn_off_gas);
  digitalWrite(turn_off_gas, LOW);
}

void loop() {

  __knob_check__ = digitalRead(enable_ckt);

  if(__knob_check__ == 1) {

    //start sensing
    __pos_cont__ = 1;
    //Serial.println("1st Hello");
    
  }

  if(__pos_cont__ == 1) {

    __flame_check__ = digitalRead(enable_flame_det);

    
    if (__flame_check__ == 0) {

       Serial.println("gas on");
       timer_flame = 0;
       __pos_cont__ = 0;
       __flame_check__ = 1;
       __enable_pir__ = 1;
        
    }

    else if (__flame_check__ == 1){
       Serial.println("gas is off");  
    }
    
    timer_flame = 1 + timer_flame;

    //hold flame detector for 30s
    if(timer_flame == 100) {

      timer_flame = 0;
      __pos_cont__ = 0;
      Serial.println("Gas shut down");
      __enable_gas_sensor__  = 1;
    
    }
    
   }

   gas_sense();
   pir_sense();


  delay(100);

}

void pir_sense(){

  if(__enable_pir__ == 1){

    
     digitalWrite(sonic_trig, LOW);
     delayMicroseconds(5);
     digitalWrite(sonic_trig, HIGH);
     delayMicroseconds(10);
     digitalWrite(sonic_trig, LOW);
    
    
    
     pinMode(sonic_echo, INPUT);
     duration = pulseIn(sonic_echo, HIGH);
 
     // Convert the time into a distance
     cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
    
     if(cm < 500){

        timer_pir = 0;
        
      }
    //5min logic
    timer_pir = 1 + timer_pir;
    Serial.println(timer_pir);
    if(timer_pir == 100){
      Serial.println("No one in the room shutting down the system");
      //send msg
      //turn off gas
      mySerial.println("AT+CMGF=1");
      delay(1000);
      mySerial.println("AT+CMGS=\"+919011225075\"\r");
      delay(1000);
      mySerial.println("You left the gas on turning off the gas");
      delay(100);
      mySerial.println((char)26);
      delay(1000);
      digitalWrite(turn_off_gas, HIGH);
      delay(7000);
      digitalWrite(turn_off_gas, LOW);
      timer_pir = 0;
      __enable_pir__ = 0;
    }
    
   }
  
}

void gas_sense(){

  if(__enable_gas_sensor__ == 1) {

      __gas_detect__ = analogRead(gas_det);
      Serial.println(__gas_detect__);
      if (__gas_detect__ > 150) {
          Serial.println("Turning of gas");
          __enable_gas_sensor__ = 0;
          mySerial.println("AT+CMGF=1");
          delay(1000);
          mySerial.println("AT+CMGS=\"+919011225075\"\r");
          delay(1000);
          mySerial.println("Gas leakage detected turning off the gas");
          delay(100);
          mySerial.println((char)26);
          delay(1000);
          digitalWrite(turn_off_gas, HIGH);
          delay(7000);
          digitalWrite(turn_off_gas, LOW);
        
        }
    
    }
    
}
