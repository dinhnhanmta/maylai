#include "def_io.h"
long time_now=0;                       
int angle_pre=0;                       //  GOC THUC TE TREN MAN HINH
long err_now,blink_now;                          // thoi diem xuat hien su co
#define PERIOD_ADC 10       // CHU KY DICH CHUYEN CUA KIM (moi lan dich 1 do)
#define ERR_PERIOD 10000               // trong 10s neu chuyen che do se hoat dong binh thuong 
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
  pinMode(bt_source_err,INPUT_PULLUP);         //  NUT NHAN BAO LOI NGUON
  pinMode(bt_phase_err_1,INPUT_PULLUP); 
  pinMode(bt_phase_err_2,INPUT_PULLUP);         //  NUT NHAN BAO LOI PHA
  pinMode(bt_oil_err_1,INPUT_PULLUP); 
  pinMode(bt_oil_err_2,INPUT_PULLUP);         //  NUT NHAN BAO LOI DAU
  pinMode(bt_overload_1,INPUT_PULLUP); 
  pinMode(bt_overload_2,INPUT_PULLUP);         //  NUT NHAN BAO LOI QUA TAI
  pinMode(sw_source_backup,INPUT_PULLUP);     // SU DUNG NGUON DU PHONG 

  pinMode(led_source_1,OUTPUT);         //  LED SANG KHI CHON NGUON
  pinMode(led_source_2,OUTPUT); 
  pinMode(led_pump_1,OUTPUT);         //  LED SANG KHI CHON BOM
  pinMode(led_pump_2,OUTPUT);
  pinMode(led_start_1,OUTPUT);         //  LED SANG KHI CHON BOM
  pinMode(led_start_2,OUTPUT);

  pinMode(led_source_err,OUTPUT);         //  LED BAO LOI NGUON
  pinMode(led_phase_err_1,OUTPUT);         //  LED BAO LOI PHA
  pinMode(led_phase_err_2,OUTPUT);
  pinMode(led_oil_err_1,OUTPUT);         //  LED BAO LOI DAU
  pinMode(led_oil_err_2,OUTPUT);
  pinMode(led_overload_1,OUTPUT);         //  LED BAO LOI QUA TAI
  pinMode(led_overload_2,OUTPUT);
  pinMode(led_alert,OUTPUT);         //  LED BAO DONG NHAP NHAY
  pinMode(led_backup,OUTPUT);        // LED SU DUNG NGUON DU PHONG
}

void loop() {
  updateStateMachine();
  updateLed();
  updateError();
}



void updateStateMachine(void)
{
switch (state)
{
case BEGIN:
  
  if (digitalRead(sw_source_1)==SELECT) state=SW_SOURCE1_SELECTED;  // KIEM TRA CONG TAC CHON NGUON
  if (digitalRead(sw_source_2)==SELECT) state=SW_SOURCE2_SELECTED;
  break;
case SW_SOURCE1_SELECTED:
 
  if (digitalRead(sw_pump_1)==SELECT) state=SW_PUMP1_SELECTED;      // KIEM TRA CONG TAC CHON BOM
  if (digitalRead(sw_source_1)==UNSELECT) state=BEGIN;              // KIEM TRA CONG TAC CHON NGUON BI THAY DOI
  break;
case SW_SOURCE2_SELECTED:
 
  if (digitalRead(sw_pump_2)==SELECT) state=SW_PUMP2_SELECTED;
  if (digitalRead(sw_source_2)==UNSELECT) state=BEGIN; 
  break;
case SW_PUMP1_SELECTED:
  
  if (digitalRead(bt_start_1)==PRESS) state=BT_START1_PRESSED;
  if (digitalRead(sw_source_1)==UNSELECT) state=BEGIN; 
  if (digitalRead(sw_pump_1)==UNSELECT) state=SW_SOURCE1_SELECTED; 
  break;
case SW_PUMP2_SELECTED:
  
  if (digitalRead(bt_start_2)==PRESS) state=BT_START2_PRESSED;
  if (digitalRead(sw_source_2)==UNSELECT) state=BEGIN; 
  if (digitalRead(sw_pump_2)==UNSELECT) state=SW_SOURCE2_SELECTED; 
  break;
case BT_START1_PRESSED:

  if (digitalRead(sw_steering_1)==SELECT) state=ADC_CONTROL1;
  if (digitalRead(sw_pump_1)==UNSELECT) state=SW_SOURCE1_SELECTED; 
  if (digitalRead(sw_source_1)==UNSELECT) state=BEGIN;
  break; 
case BT_START2_PRESSED:

  if (digitalRead(sw_steering_2)==SELECT) state=ADC_CONTROL2;
  if (digitalRead(sw_pump_2)==UNSELECT) state=SW_SOURCE2_SELECTED; 
  if (digitalRead(sw_source_2)==UNSELECT) state=BEGIN; 
  break;
case ADC_CONTROL1:

  if (digitalRead(sw_steering_1)==UNSELECT) state=BT_START1_PRESSED;
  if (digitalRead(sw_pump_1)==UNSELECT) state=SW_SOURCE1_SELECTED; 
  if (digitalRead(sw_source_1)==UNSELECT) state=BEGIN; 
  if (digitalRead(bt_stop_1)==PRESS) state=BEGIN;
  if (state_err==NORMAL) updateADC(1);
  break;
case ADC_CONTROL2:

  if (digitalRead(sw_steering_2)==UNSELECT) state=BT_START2_PRESSED;
  if (digitalRead(sw_pump_2)==UNSELECT) state=SW_SOURCE2_SELECTED; 
  if (digitalRead(sw_source_2)==UNSELECT) state=BEGIN; 
  if (digitalRead(bt_stop_2)==PRESS) state=BEGIN;
  if (state_err==NORMAL) updateADC(2);
  break;
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
  if ((state==BT_START1_PRESSED||state==ADC_CONTROL1)&&state_err==NORMAL) digitalWrite(led_start_1,ON);
  else digitalWrite(led_start_1,OFF);
  if ((state==BT_START2_PRESSED||state==ADC_CONTROL2)&&state_err==NORMAL) digitalWrite(led_start_2,ON);
  else digitalWrite(led_start_2,OFF);
// hoat dong binh thuong den bao dong tat
if (state_err==NORMAL) digitalWrite(led_alert,OFF);
//-------------led su co nguon--------------
  if (state_err==ERROR_SOURCE)
  {
       digitalWrite(led_source_err,ON);
       if (digitalRead(sw_source_backup)==SELECT)
       {
        digitalWrite(led_backup,ON);
        state_err=NORMAL;
       }
  }
  else digitalWrite(led_source_err,OFF);

//-----------led su co mat pha 1--------------
if (state_err==ERROR_PHASE1)
{
   digitalWrite(led_phase_err_1,ON);          // bat den bao loi
   if (millis()-blink_now>500)
   {digitalWrite(led_alert,!digitalRead(led_alert));
   blink_now=millis();}
   if (state==ADC_CONTROL2) {state_err=NORMAL; return;}
   if (millis()-err_now>ERR_PERIOD) while (1) digitalWrite(led_alert,OFF);  // sau 10s chua chuyen che do se ngung hoat dong
}
else digitalWrite(led_phase_err_1,OFF);

//-----------------------led su co mat pha 2---------
if (state_err==ERROR_PHASE2)
{
   digitalWrite(led_phase_err_2,ON);          // bat den bao loi
   if (millis()-blink_now>500)
   {digitalWrite(led_alert,!digitalRead(led_alert));
   blink_now=millis();}
   if (state==ADC_CONTROL1) {state_err=NORMAL; return;}
   if (millis()-err_now>ERR_PERIOD) while (1) digitalWrite(led_alert,OFF);  // sau 10s chua chuyen che do se ngung hoat dong
}
else digitalWrite(led_phase_err_1,OFF);

//--------------led su co dau 1-----------------
if (state_err==ERROR_OIL1)
{
   digitalWrite(led_oil_err_1,ON);          // bat den bao loi
   if (millis()-blink_now>500)
   {digitalWrite(led_alert,!digitalRead(led_alert));
   blink_now=millis();}
   if (state==ADC_CONTROL2) {state_err=NORMAL; return;}
   if (millis()-err_now>ERR_PERIOD) while (1) digitalWrite(led_alert,OFF);  // sau 10s chua chuyen che do se ngung hoat dong
}
else digitalWrite(led_oil_err_1,OFF);

//----------------led su co dau 2 ----------------
if (state_err==ERROR_OIL2)
{
   digitalWrite(led_oil_err_2,ON);          // bat den bao loi
   if (millis()-blink_now>500)
   {digitalWrite(led_alert,!digitalRead(led_alert));
   blink_now=millis();}
   if (state==ADC_CONTROL1) {state_err=NORMAL; return;}
   if (millis()-err_now>ERR_PERIOD) while (1) digitalWrite(led_alert,OFF);  // sau 10s chua chuyen che do se ngung hoat dong
}
else digitalWrite(led_oil_err_2,OFF);

//------------------led su co qua tai 1-------------
if (state_err==ERROR_OVERLOAD1)
{
   digitalWrite(led_overload_1,ON);          // bat den bao loi
   if (millis()-blink_now>500)
   {digitalWrite(led_alert,!digitalRead(led_alert));
   blink_now=millis();}
   if (state==ADC_CONTROL2) {state_err=NORMAL; return;}
   if (millis()-err_now>ERR_PERIOD) while (1) digitalWrite(led_alert,OFF);  // sau 10s chua chuyen che do se ngung hoat dong
}
else digitalWrite(led_overload_1,OFF);

//----------------led su co qua tai 2 -------------
if (state_err==ERROR_OVERLOAD2)
{
   digitalWrite(led_overload_2,ON);          // bat den bao loi
   if (millis()-blink_now>500)              // nhay led bao dong
   {digitalWrite(led_alert,!digitalRead(led_alert));
   blink_now=millis();}
   if (state==ADC_CONTROL1) {state_err=NORMAL; return;}
   if (millis()-err_now>ERR_PERIOD) while (1) digitalWrite(led_alert,OFF);  // sau 10s chua chuyen che do se ngung hoat dong
}
else digitalWrite(led_overload_2,OFF);

}

//--------------------------------------------
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
  int adc_value,angle,angle_err,i;
if (control==1)
{ 
  adc_value=analogRead(adc_steering_1);
}
if (control==2)
{
  adc_value=analogRead(adc_steering_2);
}
angle=map(adc_value,0,1023,0,220);        //DONG HO QUAY VOI GOC 220 DO tu 340 den 200 do 
  if ((angle_pre<angle)&&(millis()-time_now>PERIOD_ADC))
  {
        angle_pre+=1;  
        sendAngle(angle_pre);
        //delay
        time_now=millis();
  }
 if ((angle_pre>angle)&&(millis()-time_now>PERIOD_ADC))
  {
        angle_pre-=1; 
        sendAngle(angle_pre);
        time_now=millis();
  }
  
}
//---------------------------------------------------
void updateError(void)
{
  if (digitalRead(bt_source_err)==PRESS)
  { 
      state_err=ERROR_SOURCE;

  }
  if (digitalRead(bt_phase_err_1)==PRESS) 
  {
      err_now=millis();
      blink_now=millis();
      state_err=ERROR_PHASE1;
  }
  if (digitalRead(bt_phase_err_2)==PRESS) 
  {
      err_now=millis();
      blink_now=millis();
      state_err=ERROR_PHASE2;
  }
  if (digitalRead(bt_oil_err_1)==PRESS) 
  {
      err_now=millis();
      blink_now=millis();
      state_err=ERROR_OIL1;
  }
  if (digitalRead(bt_oil_err_2)==PRESS) 
  {
      err_now=millis();
      blink_now=millis();
      state_err=ERROR_OIL2;
  }
  if (digitalRead(bt_overload_1)==PRESS) 
  {
      err_now=millis();
      blink_now=millis();
      state_err=ERROR_OVERLOAD1;
  }
  if (digitalRead(bt_overload_1)==PRESS) 
  {
      err_now=millis();
      blink_now=millis();
      state_err=ERROR_OVERLOAD2;
  }
  
}

