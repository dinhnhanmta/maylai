#ifndef def_io_h
#define def_io_h
#define GAUSE         "z0.val="
#define PRESS         LOW
#define RELEASE       HIGH

#define SELECT         LOW
#define UNSELECT       HIGH
#define ON            HIGH
#define OFF           LOW
#define sw_source_1   22            //CONG TAC CHON NGUON 1
#define sw_source_2   23            //CONG TAC CHON NGUON 2
#define sw_pump_1     24            //CONG TAC CHON BOM 1
#define sw_pump_2     25            //CONG TAC CHON BOM 2
#define sw_steering_1 26            //CONG TAC CHON LAI 1
#define sw_steering_2 27            //CONG TAC CHON LAI 2

#define bt_start_1   28            //NUT KHOI DONG M1
#define bt_start_2   29            //NUT KHOI DONG M2
#define bt_stop_1    30            //NUT DUNG M1
#define bt_stop_2    31            //NUT DUNG M2

#define led_source_1  32            //LED SANG KHI CHON NGUON 1
#define led_source_2  33            //LED SANG KHI CHON NGUON 2
#define led_pump_1    34            //LED SANG KHI CHON BOM 1
#define led_pump_2    35            //LED SANG KHI CHON BOM 2
#define led_start_1   36            //LED SANG KHI BAM NUT KHOI DONG 1
#define led_start_2   37            //LED SANG KHI BAM NUT KHOI DONG 2  
 
#define adc_steering_1    A0            //LAI M1
#define adc_steering_2    A1            //LAI M2

enum stateMayLai {
BEGIN,                       // TRANG THAI BAN DAU
SW_SOURCE1_SELECTED,         // DA CHON NGUON 1
SW_SOURCE2_SELECTED,         // DA CHON NGUON 2
SW_PUMP1_SELECTED,           // DA CHON BOM 1
SW_PUMP2_SELECTED,           // DA CHON BOM 2
BT_START1_PRESSED,           // NUT KHOI DONG M1 DUOC NHAN
BT_START2_PRESSED,           // NUT KHOI DONG M2 DUOC NHAN
SW_STEERING1_SELECTED,       // DA CHON LAI 1
SW_STEERING2_SELECTED,       // DA CHON LAI 2 
ADC_CONTROL1,                // DANH LAI M1
ADC_CONTROL2                 // DANH LAI M2
};

void updateStateMachine(void);    // CAP NHAT TRANG THAI MAY  
void updateLed(void);             // CAP NHAT TRANG THAI LED
void updateADC(int control);      // CAP NHAT ADC
void sendAngle(int angle);         // GUI GOC LAI
enum stateMayLai state=BEGIN;

#endif
