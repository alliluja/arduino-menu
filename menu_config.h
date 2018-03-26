/*
 ====== Configuration for CMenu class ======
*/

#pragma once

/*==============USING TYPES=================*/
typedef unsigned short int uint;

/*==============USING TYPES END=============*/



/*=============GLOBAL VARIABLES=============*/
#define DIGIT_INCREMENT 0.1                  //increment digit value in menu


//#define ARDUINO                                   //to compile for arduino
#ifdef ARDUINO
#   define LCD_1602
#      ifdef LCD_1602
#         define LCD_STR_LENGTH 16                    //symbols in row
#         define LCD_NUM_ROWS   2                     //rows in display
#      else
           //if not 1602 lcd display
#      endif

#   define I2C_FLAG
#      ifdef I2C_FLAG
            //if LCD using I2C Protocol
            #include <LiquidCrystal_I2C.h> ///??????
#      else
            //else using 4bit wire??
            #include <LiquidCrystal.h>
#      endif
#else                                        //compile for windows (for example)
#   define LCD_STR_LENGTH  256

#endif

#define ON             "ON"                  //string, to show status of bool value - true
#define OFF            "OFF"                 //string, to show status of bool value - false
/*=============GLOBAL VARIABLES END=========*/


/*=============CODE OPTIMIZATION============*/
//#define ARRAY_ON                            //to use string array in menu, comment if don't need

//#define EXEC_ON                             //to use exec function in menu, comment if don't need
#   ifdef EXEC_ON
#      define FUNC_P void (*func)()
#   endif
/*=============CODE OPTIMIZATION END========*/


/*===========CONFIG BUTTONS=================*/
#define BTN_UP     72                       //move up in menu or increment vriable
#define BTN_DOWN   80                       //move down in menu or decrement vriable
#define BTN_BACK   8                       //move back in menu or exit in parent menu
#define BTN_ENTER  13                       //enter in to menu or execute function
/*===========CONFIG BUTTONS END=============*/
