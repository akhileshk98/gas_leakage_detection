#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);                             // To Enalbe Serial Communication on Rx and Tx Pins

int led_pin=13;                                             //Status and Alert LED
int buz_pin=11;                                             //Buzzer
int analog_pin=A0;                                          //Gas Sensor
int smscount=0;
int sms_led=12;                                             //Status for LED
int button=7;                                               //Reset Button

void setup() {
    mySerial.begin(9600); 
    Serial.begin(9600);
    pinMode(led_pin, OUTPUT);
    pinMode(buz_pin, OUTPUT);
    pinMode(sms_led, OUTPUT);
}

void sendsms() {
    if (smscount < 1) {
        Serial.println("Preparing message");
        digitalWrite(sms_led,HIGH);
        SendMessage();
        smscount++;
    }
}

void SendMessage() {
    mySerial.println("AT+CMGF=1");                            // Change to Sending Mode
    delay(1000);  
    mySerial.println("AT+CMGS=\"+PhoneNumberHere\"\r");       // Replace PhoneNumberHere with Your Phone Number
    delay(1000);
    mySerial.println("Leakage Detected!.");                   //Serial Monitor Print Statement, to Debug the Code.
    delay(100);
    mySerial.println((char)26);                               // Back or Ctrl- Z
    delay(1000);
    Serial.println("message sent to user");
}

void smsreset() {                                             //Reset the Variable
    Serial.println("SMS RESET");  
    smscount=0;
    digitalWrite(sms_led,LOW);
}

void loop() {
    int temp;
    temp=analogRead(analog_pin);

    if(temp > 512) {                                          //Taking the Threshold as 512
        Serial.println("LPG LEAK ALERT!!"); 
        int i; 
        for(i=0; i <= 10; i++) {                              //This Loop is for Visual and Audio Alert
            digitalWrite(led_pin,HIGH);
            digitalWrite(buz_pin,HIGH);
            delay(250);
            digitalWrite(led_pin,LOW);
            digitalWrite(buz_pin,LOW);
            delay(250);
        }
    sendsms();
    smscount++;
    } else {
        Serial.println("SAFE"); 
        digitalWrite(led_pin,HIGH);
        digitalWrite(buz_pin,LOW);
        delay(2000);
    }

    if (digitalRead(button) == HIGH) {                        //Reset SMS Button
        smsreset();
    }
}
