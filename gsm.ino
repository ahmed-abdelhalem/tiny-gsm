#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>
const char apn[]  = "internet.vodafone.net";
const char user[] = "";
const char pass[] = "";

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
#define BLYNK_TEMPLATE_ID "TMPLWj-GYoI0"
#define BLYNK_DEVICE_NAME "LDR Value"
#define BLYNK_AUTH_TOKEN "3QzuIQCtllQDKofHYEmdBsnk20yts2Zw"
TinyGsm modem(SerialAT);
BLYNK_WRITE(virtual_pin1) {
  state_power = param.asInt();
  if(state_power==0){
      digitalWrite(pin_power, !state_power);
      Serial.println("Power Off");
    }
  else{
      digitalWrite(pin_power, !state_power);
      Serial.println("Power On");
    }
}

BLYNK_WRITE(virtual_pin2) {
  state_data = param.asInt();
  if(state_data==0){
      digitalWrite(pin_data, !state_data);
      Serial.println("Data Off");
    }
  else if(state_data==1 && state_power==1){
      digitalWrite(pin_data, !state_data);
      Serial.println("Data On");
    }
}
void setup() {
  // put your setup code here, to run once:
SerialMon.println("Initializing modem...");
  modem.restart();
  Blynk.begin("3QzuIQCtllQDKofHYEmdBsnk20yts2Zw",modem,apn,user, pass, "ny3.blynk.cloud", 8080);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  msg = RecieveMessage();
  if(msg.indexOf("power on")>=0 || msg.indexOf("Power on")>=0){
      digitalWrite(pin_power,HIGH);
      Blynk.virtualWrite(virtual_pin1,1);
      Serial.println("Power On");}
   else if(msg.indexOf("power off")>=0 || msg.indexOf("Power off")>=0){
      digitalWrite(pin_power,LOW);
      Blynk.virtualWrite(virtual_pin1,0);
      Serial.println("Power Off");}
   else if(msg.indexOf("data on")>=0 || msg.indexOf("Data on")>=0){
      digitalWrite(pin_data,HIGH);
      Blynk.virtualWrite(virtual_pin2,1);
      Serial.println("Data On");}
   else if(msg.indexOf("data off")>=0 || msg.indexOf("Data off")>=0){
      digitalWrite(pin_data,LOW);
      Blynk.virtualWrite(virtual_pin2,0);
      Serial.println("Data Off");}
}
String RecieveMessage()
{
  delay(500);
  while(SerialAT.available())
  {
     SerialAT.println("AT+CMGF=1\r");
     return SerialAT.readString();
    }
}
