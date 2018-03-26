/*
   Menu class for 16x2 LCD display
   Made by Rakov Veniamin, 2018
*/
#pragma once

//#include <LiquidCrystal.h> //TODO: 
#include <string>
#include <vector>
#include "menu_config.h"

namespace value_type
{
   enum
   {
      SWITCH = 0, //switch value to ON or OFF
      DIGIT //for digital value
   #ifdef ARRAY_ON
      , ARRAY //for array of string
   #endif ARRAY_ON
   #ifdef EXEC_ON
      , EXEC //for exec functions from menu
   #endif EXEC_ON
   };
}

class CAction
{
public:
   CAction(void *value, uint action, uint *iter = nullptr);
   std::string getValue();
   bool Up(bool up = true);
   bool Down();
   uint GetAction();

#ifdef EXEC_ON
   bool Exec();
#endif EXEC_ON



private:
   uint _action;
   float *_digit;
   bool *_switch;
#ifdef ARRAY_ON
   std::vector<std::string> *_strArr;
   uint *_currentArrayItem;
#endif ARRAY_ON
#ifdef EXEC_ON
   FUNC_P;
#endif EXEC_ON
};


class CMenu
{
public:
//methods
   CMenu( const std::string Title, const uint Item  = 0 ); //constructor //TODO: 
   bool addSubMenu(const std::string Title, const uint Parent);
   bool addEditableItem(const std::string title, const uint parent, CAction *action);
   bool Down();
   bool Up();
   bool GoTo();
   bool Enter();
   bool Back();
   bool Flush(CMenu *menu);
private:
//methods
   bool addItem(const std::string Title, const uint Item, bool editable = false, CAction *action = nullptr);
   CMenu* findSub(const uint Parent);
   void Draw(CMenu* subMenu);
//properties
   bool _editable;
   std::string _title;
   uint _parent;
   uint _currentMenuID;
   uint _currentMenuParent;
   uint _itemCount;
   std::vector<CMenu *> _subMenu;
   uint _item;
   CAction *_action;
};
