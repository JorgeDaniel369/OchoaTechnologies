#include <Arduino.h>
#include <Avr/wdt.h>


#define Motor_dosificador   4
#define Motor_aspersor      5
#define Led_fed             6
#define led_online          7
#define led_offline         8 

//variables//
byte control_sw,control_if;
unsigned long previousMillis = 0;
const long interval = 1000;
int ledState = LOW;

//interrups mega 2, 3, 18, 19, 20, 21//

void setup()
{
    Serial.begin(9600);     //Debugger//
    Serial1.begin(19200);    //GPS//
    Serial2.begin(9600);    //Comunication Devices//

    for (int i=4; i<=9; i++){
        pinMode(i,OUTPUT);	


    }

        //Check if all is good//
    while (!Serial1.available()){
        Serial.println("Tracking Gps");
        delay(2000);
    
    } 
       //Go to setup for check func  main devices//
        
        InitFunc();
    Serial.println("sali de la funcion init");
}
void InitFunc(){
    while (control_if == 0){
            switch (control_sw)
    {
    case 0:{
    Serial.print("Enciende el led"); 
    digitalWrite(Led_fed, HIGH);
    delay (1000);
    control_sw = 1; 
    Serial.println(control_sw);   
        break;
    }
    
    case 1:{
    Serial.println("Enciende Motor Dosificador");
    digitalWrite(Motor_aspersor, HIGH);
    delay(1000);
    control_sw = 2;
    break;
    }
    
    case 2:{
    Serial.println("Enciende Motor Aspersor");
    digitalWrite(Motor_dosificador, HIGH);
    delay(1000);
    control_sw = 3;
    break;
    }

    case 3:{
    Serial.println("Se apaga todo");
    for (int i=6; i>=3; i--){
        digitalWrite(i,LOW);
        delay(1000);
        
    }
    control_if = 1;
    break;
    }
    }//switch
    }
}


void loop()
{

unsigned long currentMillis = millis();
 //actually value - 0 = 1
 if (currentMillis - previousMillis >= interval){
     previousMillis = currentMillis;
    if (ledState == LOW){
        ledState = HIGH;
    Serial.println("HIGH");
    }
    else {
        ledState = LOW;
        Serial.println("LOW");
    }
    digitalWrite(led_online, ledState);
 }
	
}
