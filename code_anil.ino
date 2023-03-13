#include <LiquidCrystal.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 12, TXPin = 13;//GPS PINS AND GSM RX 1 AND TX 0...
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
float l,m;
char h,i,j;

int analogPin = A0; // Analog input pin connected to VOUT of ZMPT101B module
float Vin_max = 50.0; // Maximum voltage to be measured (50V DC in this case)
float Vout_max = 5.0; // Maximum output voltage range of voltage divider circuit (5V for Arduino analog input)
float Rdiv = 10.0; // Equivalent resistance of voltage divider circuit (10kohm + 10kohm in this case)

int sensorValue;
float Vout;
float Vin;

int mappedVal;
String t;
String phoneNumber;


void setup() {
  Serial.begin(9600);
 
  ss.begin(GPSBaud);
  
  delay(5000);
  while(l<1)
  {
   while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
      delay(100);
  }
  
   Serial.print("AT+CMGF=1"); 
  delay(100);
 
  Serial.print("AT+CNMI=2,2,0,0,0");
  delay(1000);
  
}

void loop() {
 
  if(Serial.available())
  { 
     t=Serial.readString();
    int firstQuoteIndex = t.indexOf('"') + 1;
    int secondQuoteIndex = t.indexOf('"', firstQuoteIndex);
    phoneNumber = t.substring(firstQuoteIndex, secondQuoteIndex);
    if(t.indexOf(phoneNumber)>=0){
    for(int ch=0;ch<1;ch++){
     send2();
     serialflush();
       }
      }
//     else if(t.indexOf("SOC")){
//      sendsoc();
//     
//  }
//if(mappedVal<10){
//  sendsoc();
//  }

  
  
  delay(1000);
}
}
void displayInfo()
{
  if (gps.location.isValid())
  {
    l=gps.location.lat();
    m=gps.location.lng();
   
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
void send1(String s)
{
   Serial.println("AT\r");
  
  delay(100);

  Serial.println("AT+CMGF=1\r"); 
  delay(100);
  Serial.println("AT+CMGS=\"+917032325283\""); //enter mobilenumber
  delay(1000);
  Serial.println(s); 
  delay(1000);
  

  Serial.println((char)26); 
  delay(1000);
  //delay(1000);  
}

void send2(){

  delay(1000);
   Serial.println("AT\r");
  
  delay(1000);

  Serial.println("AT+CMGF=1\r"); 
  delay(1000);
 
  Serial.println("AT+CMGS=\"" +phoneNumber + "\""); //enter mobilenumber
  delay(1000);
 
 
   Serial.print("http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=");
   Serial.print(String(l , 6));
   Serial.print("+");              //28.612953, 77.231545   //28.612953,77.2293563
   Serial.print(String(m , 6));
   delay(1000);
   Serial.println("");
   delay(1000);
//  Serial.print("battery voltage");
//  delay(1000);
//  Serial.print(" ");
//  Serial.print(Vin);
//  delay(1000); 
  Serial.println(""); 
  Serial.print("Battery percentage");
   delay(1000);
   Serial.print(" ");
  Serial.print(mappedVal);
  delay(1000);
  Serial.print("%");
  delay(1000);
  Serial.println((char)26); 
  delay(1000);
  delay(1000);  
}
void sendsoc(){
 delay(1000);
   Serial.println("AT\r");
  
  delay(1000);

  Serial.println("AT+CMGF=1\r"); 
  delay(1000);
 
  Serial.println("AT+CMGS=\"+917032325283\""); //enter mobilenumber
  delay(1000);
//  Serial.print("battery voltage");
//  delay(1000);
//  Serial.print(Vin);
//  delay(1000);  
  Serial.print("Alert battery");
   delay(1000);
  Serial.print(mappedVal);
  delay(1000);
  Serial.print("%");
  delay(1000);
  Serial.print("left");
  delay(1000);
  Serial.println("");
  delay(1000);
  Serial.print("Charge Battery");
  Serial.println("");
  Serial.println("Team Chargekart");
  delay(1000);
  
  Serial.println((char)26); 
  delay(1000);
  }

void Vvalue(){

  sensorValue = analogRead(analogPin); // Read analog input value
   Vout = sensorValue * 5.0 / 1023.0; // Convert analog input value to voltage
   Vin = Vout / Vscale(); // Calculate input voltage using scaling factor
//  Serial.print("Input voltage: ");
//  Serial.print(Vin);
//  Serial.println(" V");
  delay(1000); // Wait for 1 second}
  mappedVal=map(Vin,0,100,1,50);

  
}

float Vscale() {
  return Vin_max / Vout_max / Rdiv;
}
void serialflush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}
