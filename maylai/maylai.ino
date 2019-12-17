#include "def_io.h"
int angle_pre=0;                       //  GOC THUC TE TREN MAN HINH
int period=50;
void setup() {
  // put your setup code here, to run once:
  //khai bao chan vao ra
  
  Serial.begin(9600);
  pinMode(sw_source_1,INPUT_PULLUP);       // CONG TAC CHON NGUON
  pinMode(sw_source_2,INPUT_PULLUP);

  pinMode(sw_pump_1,INPUT_PULLUP);         // CONG TAC CHON BOM
  pinMode(sw_pump_2,INPUT_PULLUP); 

  pinMode(sw_steering_1,INPUT_PULLUP);         // CONG TAC CHON LAI
  pinMode(sw_steering_2,INPUT_PULLUP);  

  pinMode(bt_start_1,INPUT_PULLUP);         //  NUT NHAN KHOI DONG
  pinMode(bt_start_2,INPUT_PULLUP);  

  pinMode(bt_stop_1,INPUT_PULLUP);         //  NUT NHAN DUNG
  pinMode(bt_stop_2,INPUT_PULLUP); 

  pinMode(led_source_1,OUTPUT);         //  LED SANG KHI CHON NGUON
  pinMode(led_source_2,OUTPUT); 
  pinMode(led_pump_1,OUTPUT);         //  LED SANG KHI CHON BOM
  pinMode(led_pump_2,OUTPUT);
  pinMode(led_start_1,OUTPUT);         //  LED SANG KHI CHON BOM
  pinMode(led_start_2,OUTPUT);
}

void loop() {
  
  
}



void updateStateMachine(void)
{
switch (state)
{
case BEGIN:
  if (digitalRead(sw_source_1)==SELECT) state=SW_SOURCE1_SELECTED;  // KIEM TRA CONG TAC CHON NGUON
  if (digitalRead(sw_source_2)==SELECT) state=SW_SOURCE2_SELECTED;

case SW_SOURCE1_SELECTED: 
  if (digitalRead(sw_pump_1)==SELECT) state=SW_PUMP1_SELECTED;      // KIEM TRA CONG TAC CHON BOM
  if (digitalRead(sw_source_1)==UNSELECT) state=BEGIN;              // KIEM TRA CONG TAC CHON NGUON BI THAY DOI

case SW_SOURCE2_SELECTED:
  if (digitalRead(sw_pump_2)==SELECT) state=SW_PUMP2_SELECTED;
  if (digitalRead(sw_source_2)==UNSELECT) state=BEGIN; 

case SW_PUMP1_SELECTED:
  if (digitalRead(bt_start_1)==PRESS) state=BT_START1_PRESSED;
  if (digitalRead(sw_source_1)==UNSELECT) state=BEGIN; 
  if (digitalRead(sw_pump_1)==UNSELECT) state=SW_SOURCE1_SELECTED; 
 
case SW_PUMP2_SELECTED:
  if (digitalRead(bt_start_2)==PRESS) state=BT_START2_PRESSED;
  if (digitalRead(sw_source_2)==UNSELECT) state=BEGIN; 
  if (digitalRead(sw_pump_2)==UNSELECT) state=SW_SOURCE2_SELECTED; 

case BT_START1_PRESSED:
  if (digitalRead(sw_steering_1)==SELECT) state=ADC_CONTROL1;
  if (digitalRead(sw_pump_1)==UNSELECT) state=SW_SOURCE1_SELECTED; 
  if (digitalRead(sw_source_1)==UNSELECT) state=BEGIN; 
case BT_START2_PRESSED:
  if (digitalRead(sw_steering_2)==SELECT) state=ADC_CONTROL2;
  if (digitalRead(sw_pump_2)==UNSELECT) state=SW_SOURCE2_SELECTED; 
  if (digitalRead(sw_source_2)==UNSELECT) state=BEGIN; 
case ADC_CONTROL1:
  if (digitalRead(sw_steering_1)==UNSELECT) state=BT_START1_PRESSED;
  if (digitalRead(sw_pump_1)==UNSELECT) state=SW_SOURCE1_SELECTED; 
  if (digitalRead(sw_source_1)==UNSELECT) state=BEGIN; 
  if (digitalRead(bt_stop_1)==PRESS) state=BEGIN;
  updateADC(1);
 
case ADC_CONTROL2:
  if (digitalRead(sw_steering_2)==UNSELECT) state=BT_START2_PRESSED;
  if (digitalRead(sw_pump_2)==UNSELECT) state=SW_SOURCE2_SELECTED; 
  if (digitalRead(sw_source_2)==UNSELECT) state=BEGIN; 
  if (digitalRead(bt_stop_2)==PRESS) state=BEGIN;
  updateADC(2);
}
  
}



void updateLed(void)
{
  // led nguon
  if (digitalRead(sw_source_1)==SELECT) digitalWrite(led_source_1,ON);
  else digitalWrite(led_source_1,OFF);
  if (digitalRead(sw_source_2)==SELECT) digitalWrite(led_source_2,ON);
  else digitalWrite(led_source_2,OFF);
  //led bom
  if (digitalRead(sw_pump_1)==SELECT) digitalWrite(led_pump_1,ON);
  else digitalWrite(led_pump_1,OFF);
  if (digitalRead(sw_pump_2)==SELECT) digitalWrite(led_pump_2,ON);
  else digitalWrite(led_pump_2,OFF);

  // sau khi an nut khoi dong -> den van hanh sang
  if (state==BT_START1_PRESSED||state==ADC_CONTROL1) digitalWrite(led_start_1,ON);
  else digitalWrite(led_start_1,OFF);
  if (state==BT_START2_PRESSED||state==ADC_CONTROL2) digitalWrite(led_start_2,ON);
  else digitalWrite(led_start_2,OFF);
}
void sendAngle(int angle)
{
 String text;
 if (angle<20) angle=340+angle;
  else angle-=20;
  text=GAUSE+String(angle);
  Serial.print(text);
  Serial.write(0xff); 
  Serial.write(0xff);
  Serial.write(0xff); 
}
void updateADC(int control)
{
  int adc_value,angle,angle_temp,i;
  long time_now;
if (control==1)
{ 
  adc_value=analogRead(adc_steering_1);
  angle=map(adc_value,0,1023,0,220);        //DONG HO QUAY VOI GOC 240 DO tu 340 den 200 do 
  angle_temp=abs(angle-angle_pre);
  while (angle_pre!=angle)
  {
  if (angle_pre<angle)
  {
      for(i=1;i<=angle_temp;i++)
      {
        angle_pre+=1;  
        sendAngle(angle_pre);
        //delay
        time_now=millis();
        while (millis()<time_now + period);
      }
  }
  else 
  {
    for(i=1;i<=angle_temp;i++)
      {  
        angle_pre-=1; 
        sendAngle(angle_pre);
      }
  }
  
 }
}
if (control==2)
{
  adc_value=analogRead(adc_steering_1);
  angle=map(adc_value,0,1023,0,220);        //DONG HO QUAY VOI GOC 240 DO tu 340 den 200 do 
  angle_temp=abs(angle-angle_pre);
  while (angle_pre!=angle)
  {
  if (angle_pre<angle)
  {
      for(i=1;i<=angle_temp;i++)
      {
        angle_pre+=1;  
        sendAngle(angle_pre);
        //delay
        time_now=millis();
        while (millis()<time_now + period);
      }
  }
  else 
  {
    for(i=1;i<=angle_temp;i++)
      {  
        angle_pre-=1; 
        sendAngle(angle_pre);
      }
  }
  
 }
}

}

