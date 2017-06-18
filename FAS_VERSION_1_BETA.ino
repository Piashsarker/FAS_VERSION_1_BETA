#include <SoftwareSerial.h>
#include <dht.h>
SoftwareSerial mySerial(9, 10);
dht DHT;
#define LED_1_PIN 2
#define LED_2_PIN 3
#define FAN_1_PIN 4
#define LED_3_PIN 5
#define LED_4_PIN 6
#define LIGHT_SENSOR_PIN A5
#define HUMIDITY_SENSOR_PIN 7


String statusMessage ;
boolean allAppilanceOn = false;
boolean humiditySensorOn = false ;
boolean lightIntensityOn = false ;
boolean ledOneOn  = false ;
boolean ledTwoOn = false ;
boolean ledThreeOn = false ;
boolean ledFourOn = false ;
boolean fanOneOn = false ;
boolean ledTwoForceOff = false ;
boolean fanOneForceOff = false ;
boolean commandArrive = false  ;
int temprature = 0 ;
int humidity = 0 ;
int lightIntensity = 0 ;
char command ;
String msg ;
int totalOn = 0 ; 
int totalOff = 7 ; 

void setup()
{
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(FAN_1_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(HUMIDITY_SENSOR_PIN, INPUT);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println("GSM SIM900A BEGIN");
  Serial.println();
  mySerial.println("AT+CNMI=2,2,0,0,0");
  delay(100);
}

void loop()
{


  //GSM Message Command
  if (mySerial.available() > 0) {
    command = mySerial.read();
    delay(100);
    Serial.print(command);
    commandArrive = true ;
    if (commandArrive) {
      if (command == '#') {
        command = mySerial.read();
        if (command == 'a') {
          command = mySerial.read();
          if (command == '1') {
            if (!ledOneOn) {
              pinHigh(LED_1_PIN);
              commandArrive = false;
              ledOneOn = true;
              totalOn = totalOn+1; 
              totalOff = totalOff-1 ;
             // sendMessage(" Request ON"  , " Light 1" , " ON", totalOn,totalOff) ;
            }

          }
          if (command == '0') {
            if (ledOneOn) {
              pinLow(LED_1_PIN);
              commandArrive = false;
              ledOneOn = false;
             // sendMessage(" Request OFF"  , " Light 1" , " OFF", --totalOn , ++totalOff) ;
            }

          }
        }

        if (command == 'b') {
          command = mySerial.read();

          if (command == '1') {
            if (!ledTwoOn) {
              pinHigh(LED_2_PIN);
              ledTwoForceOff = false ;
              commandArrive = false;
              ledTwoOn = true;
             // sendMessage(" Request ON"  , " Light 2" , " ON", ++totalOn , --totalOff) ;
            }

          }
          if (command == '0') {
            if (ledTwoOn) {
              pinLow(LED_2_PIN);
              ledTwoForceOff = true ;
              commandArrive = false;
              ledTwoOn = false;
             // sendMessage(" Request OFF"  , " Light 2" , " OFF", --totalOn , ++totalOff) ;
            }

          }
        }

        if (command == 'c') {
          command = mySerial.read();

          if (command == '1') {
            if (!fanOneOn) {
              pinHigh(FAN_1_PIN);
              commandArrive = false;
              fanOneOn = true;
              fanOneForceOff = false ;
             // sendMessage(" Request ON"  , " Fan 1 " , " ON", ++totalOn , --totalOff) ;
            }

          }
          if (command == '0') {
            if (fanOneOn) {
              pinLow(FAN_1_PIN);
              commandArrive = false;
              fanOneOn = false;
              fanOneForceOff = true;
             // sendMessage(" Request OFF"  , " Fan 1" , " OFF", --totalOn , ++totalOff) ;
            }

          }
        }
        if (command == 'd') {
          command = mySerial.read();

          if (command == '1') {
            if (!ledThreeOn) {
              pinHigh(LED_3_PIN);
              commandArrive = false;
              ledThreeOn = true;
             // sendMessage(" Request ON"  , " LED 3 " , " ON", ++totalOn , --totalOff) ;
            }

          }
          if (command == '0') {
            if (ledThreeOn) {
              pinLow(LED_3_PIN);
              commandArrive = false;
              ledThreeOn = false;
             // sendMessage(" Request OFF"  , " LED 3" , " OFF", --totalOn , ++totalOff) ;
            }

          }
        }

        if (command == 'e') {
          command = mySerial.read();

          if (command == '1') {
            if (!ledFourOn) {
              pinHigh(LED_4_PIN);
              commandArrive = false;
              ledFourOn = true;
            
            //  sendMessage(" Request ON"  , " LED 4 " , " ON", ++totalOn , --totalOff) ;
            }

          }
          if (command == '0') {
            if (ledFourOn) {
              pinLow(LED_4_PIN);
              commandArrive = false;
              ledFourOn = false;
            //  sendMessage(" Request OFF"  , " LED 4" , " OFF", --totalOn , ++totalOff) ;
            }

          }
        }

        if (command == 'h') {
          command = mySerial.read();

          if (command == '1') {
            humiditySensorOn = true ;
           // sendMessage(" Request ON"  , " Humidity Sensor" , " ON", ++totalOn , --totalOff) ;
          }
          if (command == '0') {
            humiditySensorOn = false ;
           // sendMessage(" Request Off" , "Humidity Sensor" , " OFF" , --totalOn , ++totalOff);

          }
        }
        if (command == 'l') {
          command = mySerial.read();

          if (command == '1') {
            lightIntensityOn = true ;
           // sendMessage(" Request OFF"  , " Light Sensor" , " ON", ++totalOn , --totalOff) ;
          }
          if (command == '0') {
            lightIntensityOn = false ;
           // sendMessage(" Request ON" , "Light Sensor" , " OFF" , --totalOn , ++totalOff);

          }
        }
        if (command == '#') {
          command = mySerial.read();

          if (command == '#') {
            sendReport(); 
          }



        }


        if (command == '1') {
          command = mySerial.read();

          if (command == '1') {
            if (fanOneOn || ledOneOn || ledTwoOn ) {
              pinLow(FAN_1_PIN);
              pinLow(LED_1_PIN);
              pinLow(LED_2_PIN);
              commandArrive = false;
              fanOneOn = false;
              ledOneOn = false ;
              ledTwoOn = false ;
            //  sendMessage(" Request "  , " Device ALL " , " OFF ", totalOn - 3 , totalOff + 3) ;
            }

          }

        }




      }
    }
  }




  //Temprature AutoMation
  if (humiditySensorOn) {
    DHT.read11(HUMIDITY_SENSOR_PIN);
    delay(150);
    temprature = DHT.temperature ;
    humidity = DHT.humidity ;
    if (temprature > 20 && temprature < 40) {
      if (!fanOneOn) {
        totalOn++ ;
        totalOff--;
        pinHigh(FAN_1_PIN);
        fanOneOn = true;
      }

    }
    else {
      if (fanOneOn) {
        pinLow(FAN_1_PIN);
        totalOff++;
        totalOn--;
        fanOneOn = false;
      }
    }
  }
  else {
    pinLow(FAN_1_PIN);
    totalOff++;
    totalOn--;
  }


  if (lightIntensityOn) {
    //DAY_NIGHT AUTOMATION
    lightIntensity = analogRead(LIGHT_SENSOR_PIN);
    if (lightIntensity <= 20) {
      if (!ledTwoOn) {
        pinHigh(LED_2_PIN);
        ledTwoOn = true;
       // sendMessage(" NIGHT "  , " Light 2" , " ON", ++totalOn , --totalOff) ;
      }
    }
    else {
      if (ledTwoOn) {
        pinLow(LED_2_PIN);
        ledTwoOn = false;
       // sendMessage(" DAY"  , " Light 2" , " OFF", --totalOn , ++totalOff) ;
      }


    }
  }
  else{
    pinLow(LED_2_PIN);
    totalOff++;
    totalOn--;
  }






}

void pinHigh(int pin) {
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)                      // wait for a second
  // turn the LED off by making the voltage LO
}
void pinLow(int pin) {
  digitalWrite(pin, LOW);
}

void sendReport(){
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(500);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+8801683193505\"\r"); // Replace x with mobile number
  delay(500);
  String reportMessage = "" ; 
   reportMessage = reportMessage + temprature ; 
   reportMessage = reportMessage+"_";
   reportMessage = reportMessage + lightIntensity ; 
   reportMessage = reportMessage+"_"; 
   reportMessage = reportMessage + 5 ; 
   mySerial.println(reportMessage);// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}

void sendMessage(String request, String applianceName , String statusMsg, int totalOn , int totalOff)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(500);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+8801683193505\"\r"); // Replace x with mobile number
  delay(500);
  msg = "4 Light 1 FAN 2 Sensors\n" ;
  msg = msg + " Current Temprature ";
  msg = msg + temprature ;
  msg = msg + "\n";
  msg = msg + " Light Intensity ";
  msg = msg + lightIntensity ;
  msg = msg + "\n";
  msg = msg + " Total OFF ";
  msg = msg + totalOff ;
  msg = msg + "\n" ;
  msg = msg + " Total ON ";
  msg = msg + totalOn ;
  msg = msg + "\n" ;
  msg = msg + request ;
  msg = msg + applianceName ;
  msg = msg + statusMsg ;
  mySerial.println(msg);// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}



void MakeCall()
{
  mySerial.println("ATD+8801683193505;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
}











