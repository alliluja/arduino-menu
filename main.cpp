#include "../menu.h"
#include <iostream>

using namespace std;

void myFunc()
{
   cout<<"EXEC Function";
}


void main()
{
//create menu
   CMenu menu("Main menu");
//level 0 menu
   menu.addSubMenu("M1", 0); //item1
   menu.addSubMenu("M2", 0); //item2
//level 1 menu
   menu.addSubMenu("M1.1", 1); //item3
   menu.addSubMenu("M1.2", 1); //item4
   menu.addSubMenu("M2.1", 2); //item5
   menu.addSubMenu("M2.2", 2); //item6
//level 2 menu
   float d = 25; //при изменении в меню - это значение будет меняться и здесь!!!
   CAction item(&d, DIGIT);
   menu.addEditableItem("FLOAT", 3, &item); //item 7

   bool b = true; //при изменении в меню - это значение будет меняться и здесь!!!
   CAction item2(&b, SWITCH);
   menu.addEditableItem("BOOL", 4, &item2); //item 8

#ifdef ARRAY_ON
   uint iter = 0;
   vector<string> arr(3);
      arr[0] = "item one";
      arr[1] = "item two";
      arr[2] = "item three";
   CAction item3(&arr, ARRAY, &iter);
   menu.addEditableItem("ARRAY", 5, &item3); //item 9
#endif ARRAY_ON

#ifdef EXEC_ON
   FUNC_P = myFunc; //FUNC_P declared in menu_config.h
   CAction item4(func, EXEC);
   menu.addEditableItem("FUNCTION", 6, &item4); //item 10
#endif EXEC_ON


   menu.Flush(&menu);
   char c = 0;
   while (c != 'q')
   {
   c = getchar();
   switch(c)
      {
         case BTN_UP: menu.Up(); break;
         case BTN_DOWN: menu.Down(); break;
         case BTN_ENTER: menu.Enter(); break;
         case BTN_BACK: menu.Back(); break;
         case 'd': menu.Flush(&menu); break;
      }
   }
}