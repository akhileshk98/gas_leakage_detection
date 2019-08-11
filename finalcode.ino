#include <SoftwareSerial.h> 
SoftwareSerial mySerial(9, 10); 
 
int led_pin=13; 
int buz_pin=11; 
int analog_pin=A0; 
int smscount=0; //new comment
int sms_led=12; 
int button=7; 
 
void setup() { 
  mySerial.begin(9600);  
  Serial.begin(9600); 
  pinMode(led_pin,OUTPUT); 
  pinMode(buz_pin,OUTPUT); 
  pinMode(sms_led,OUTPUT); 
} 
  void SendMessage() { 
    mySerial.println("AT+CMGF=1");     
delay(1000);  
  mySerial.println("AT+CMGS=\"+919400424449\"\r");  
  delay(1000); 
  mySerial.println("FIRE HAZARD! Gas leak detected."); 
  delay(100); 
   mySerial.println((char)26); 
  delay(1000); 
   Serial.println("message sent to user"); 
}
   void sendsms()   { 
    if(smscount<1){ 
    Serial.println("preparing message"); 
    digitalWrite(sms_led,HIGH); 
    SendMessage(); 
    smscount++; 
    }  
 
   void smsreset() { 
    Serial.println("SMS RESET");   
    smscount=0; 
    digitalWrite(sms_led,LOW); 
    } 
 
    void loop() { 
  int temp; 
  temp=analogRead(analog_pin); 
   if (digitalRead(button)==HIGH) 
  { 
  smsreset(); 
  } 
  if(temp>512) 
  { 
    Serial.println("LPG LEAK ALERT!!");  
    int i;  
   for(i=0;i<=10;i++) 
   { 
    digitalWrite(led_pin,HIGH); 
    digitalWrite(buz_pin,HIGH); 
    delay(250); 
    digitalWrite(led_pin,LOW); 
    digitalWrite(buz_pin,LOW); 
    delay(250); 
   } 
 
     sendsms(); 
     smscount++; 
   } 
   else 
   { 
      Serial.println("SAFE");  
      digitalWrite(led_pin,HIGH); 
      digitalWrite(buz_pin,LOW); 
      delay(2000); 
   } 
} 
    
