/*
====== Configuration for CMenu class ======
*/

/*==============USING TYPES=================*/
typedef unsigned short int uint;

/*==============USING TYPES END=============*/


/*=============GLOBAL VARIABLES=============*/
#define DIGIT_INCREMENT 0.1                  //comment this
   #ifndef DIGIT_INCREMENT
      float DIGIT_INCREMENT = 0.1;           //and use &DIGIT_INCREMENT when create menu to modify this in menu
   #endif

#define LCD_STR_LENGTH 16                    //symbols in row
#define LCD_NUM_ROWS   2                     //rows in display
/*=============GLOBAL VARIABLES END=========*/

/*=============CODE OPTIMIZATION============*/
#define ARRAY_ON                            //to use string array in menu, comment if don't need

#define EXEC_ON                             //to use exec function in menu, comment if don't need
   #ifdef EXEC_ON
      #define FUNC_P void (*func)()
   #endif
/*=============CODE OPTIMIZATION END========*/

/*===========CONFIG BUTTONS=================*/
#define BTN_UP     'w'                       //move up in menu or increment vriable
#define BTN_DOWN   's'                       //move down in menu or decrement vriable
#define BTN_BACK   'r'                       //move back in menu or exit in parent menu
#define BTN_ENTER  'e'                       //enter in to menu or execute function
/*===========CONFIG BUTTONS END=============*/
