#ifndef def_io_h
#define def_io_h
#define GAUSE         "z0.val="
#define PRESS         LOW
#define RELEASE       HIGH

#define SELECT         LOW
#define UNSELECT       HIGH
#define ON            HIGH
#define OFF           LOW
#define sw_source_1   8            //CONG TAC CHON NGUON 1
#define sw_source_2   9            //CONG TAC CHON NGUON 2
#define sw_pump_1     10            //CONG TAC CHON BOM 1
#define sw_pump_2     11            //CONG TAC CHON BOM 2
#define sw_steering_1 12           //CONG TAC CHON LAI 1
#define sw_steering_2 13            //CONG TAC CHON LAI 2

#define bt_start_1   2            //NUT KHOI DONG M1
#define bt_start_2   5            //NUT KHOI DONG M2
#define bt_stop_1    3           //NUT DUNG M1
#define bt_stop_2    4            //NUT DUNG M2

#define led_source_1  30            //LED SANG KHI CHON NGUON 1
#define led_source_2  31            //LED SANG KHI CHON NGUON 2
#define led_pump_1    32            //LED SANG KHI CHON BOM 1
#define led_pump_2    33            //LED SANG KHI CHON BOM 2
#define led_start_1   47            //LED SANG KHI BAM NUT KHOI DONG 1
#define led_start_2   52            //LED SANG KHI BAM NUT KHOI DONG 2  
 
#define adc_steering_1    A1            //LAI M1
#define adc_steering_2    A2            //LAI M2
/*------------ chan vao ra bao su co ---------*/
#define bt_source_err 26
#define bt_phase_err_1 27
#define bt_phase_err_2 28
#define bt_oil_err_1   24
#define bt_oil_err_2   25
#define bt_overload_1  22
#define bt_overload_2  23

#define led_source_err 39
#define led_phase_err_1 40
#define led_phase_err_2 41
#define led_oil_err_1   43
#define led_oil_err_2   46
#define led_overload_1  44
#define led_overload_2  45
#define led_alert       49
#define led_backup      48

#define sw_source_backup 29
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
enum stateError{
NORMAL,                      // BINH THUONG
ERROR_SOURCE,                // SU CO NGUON
ERROR_PHASE1,                // SU CO PHA 1
ERROR_PHASE2,                // SU CO PHA 2
ERROR_OIL1,                  // SU CO DAU 1
ERROR_OIL2,                  // SU CO DAU 2
ERROR_OVERLOAD1,             // SU CO QUA TAI 1
ERROR_OVERLOAD2              // SU CO QUA TAI 2 
};
void updateStateMachine(void);    // CAP NHAT TRANG THAI MAY  
void updateLed(void);             // CAP NHAT TRANG THAI LED
void updateADC(int control);      // CAP NHAT ADC
void sendAngle(int angle);         // GUI GOC LAI
void updateError(void);           /// CAP NHAT SU CO
enum stateMayLai state=BEGIN;
enum stateError  state_err=NORMAL;
#endif
