// #include <LiquidCrystal.h>

#include "menu.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace value_type;
/*TODO: 
/
/добавить возможность указать постфикс значения
/
/добавить проверки при добавлении нового элемента
/           как меню, так и конечного (корректность родителя, отсутствие или наоборот присутствие  определенных значений)
/
/
/
*/

   template <typename T> //to convert digit value in to string
   static std::string int_to_string(T val)
   {
      std::stringstream ss;
      ss << val;
      std::string str = ss.str();
      return str;
   }


   CAction::CAction(void *value, uint action, uint *iter)
   {
      memset(this, 0, sizeof(CAction));

      switch(action)
      {
         case SWITCH:
            {
               _switch = reinterpret_cast<bool*>(value);
               _action = action;
               break;
            }

         case DIGIT:
            {
               _digit = reinterpret_cast<float*>(value);
               _action = action;
               break;
            }
#ifdef ARRAY_ON
         case ARRAY:
            {
               _strArr = reinterpret_cast<vector<string>*>(value);
               _action = action;
               _currentArrayItem = iter;
               break;
            }
#endif
#ifdef EXEC_ON
         case EXEC:
            {
               func = reinterpret_cast<void(*)()>(value);
               _action = action;
               break;
            }
#endif EXEC_ON
         //default: cout<<"Nothing to do"; break;
      }
   }

   string CAction::getValue()
   {
      string result = "";
      switch(_action)
      {
         case SWITCH:
            {
               result = (*_switch)? ON: OFF; //defined in menu_config.h (GLOBAL VARIABLES)
               break;
            }

         case DIGIT:
            {
               result = /*"Value = " + */int_to_string((*_digit));
               break;
            }
#ifdef ARRAY_ON
         case ARRAY:
            {
               result = (*_strArr)[(*_currentArrayItem)];
               break;
            }
#endif ARRAY_ON
#ifdef EXEC_ON
         case EXEC:
            {
               result = "EXEC Function";
               break;
            }
#endif EXEC_ON

         //default: cout<<"ERROR value type"; break;
      }
      return result;
   }

   bool CAction::Up(bool isUP)
   {
      switch(_action)
      {
         case SWITCH:
            {
               (*_switch) = !(*_switch);
               break;
            }

         case DIGIT:
            {
               (*_digit) = isUP? (*_digit) + static_cast<float>(DIGIT_INCREMENT): (*_digit) - static_cast<float>(DIGIT_INCREMENT);
               break;
            }
#ifdef ARRAY_ON
         case ARRAY:
            {
               if (isUP)
               {
                  if ((*_currentArrayItem) > 0) --(*_currentArrayItem);
               }
               else
               {
                  if ((*_currentArrayItem) < _strArr->size()-1) ++(*_currentArrayItem);
               }
               break;
            }
#endif ARRAY_ON
#ifdef EXEC_ON
         case EXEC: break;
#endif EXEC_ON
         //default: cout<<"ERROR value type"; break;
      }

      return true;
   }

   bool CAction::Down()
   {
      return Up(false);
   }

#ifdef EXEC_ON
   bool CAction::Exec()
   {
      func();
      return true;
   }
#endif

uint CAction::GetAction()
{
   return _action;
}





   CMenu::CMenu( const string Title, const uint Item )
   {
      memset(this, 0, sizeof(CMenu));
      if (Title.length() < LCD_STR_LENGTH)
      {
         _title = Title;
         _item = Item;
      }
   }

   bool CMenu::addSubMenu(const string Title, const uint Parent)
   {
     if (Title.length() < LCD_STR_LENGTH)
     {
         CMenu *subMenu = findSub(Parent);
         if (subMenu != nullptr)
         {
            _itemCount++;
            subMenu->addItem(Title, _itemCount);
         }
         else return false;
     }
     
     else return false;
     
     return true;
   }

   bool CMenu::addItem(const std::string Title, const uint Item, bool editable, CAction *action)
   {
      CMenu *subMenu = new CMenu(Title, Item);
      if (subMenu != nullptr)
      {
         subMenu->_parent = this->_item;
         subMenu->_editable = editable;
         subMenu->_action = action;
         _subMenu.push_back(subMenu);
         return true;
      }
      else return false;
   }

  CMenu* CMenu::findSub(const uint Parent)
   {
      if (this == nullptr) return nullptr;
      if (this->_item == Parent) return this;
      else
      {
         for(uint i = 0; i < _subMenu.size(); i++)
         {
            CMenu *result = nullptr;
            result = _subMenu[i]->findSub(Parent);
            if (result != nullptr) return result;
         }
         return nullptr;
      }
   }

   void CMenu::Down()
   {
      
      if (_currentMenuID + 1 <= _itemCount)
      {
         
         CMenu *tempM = findSub(_currentMenuID + 1);
         if(tempM->_parent == _currentMenuParent)
         {
            ++_currentMenuID;
            Draw(tempM);
         }
         else
         {
            CMenu *tempM = findSub(_currentMenuID);
            if (tempM->_editable) tempM->_action->Down();
            Draw(tempM);
         }
      }
      else
      {
         CMenu *tempM = findSub(_currentMenuID);
         if (tempM->_editable)
         {
            tempM->_action->Down();
            Draw(tempM);
         }

      }
   }

   void CMenu::Up()
   {
      if(_currentMenuID > 0)
      {
         
         CMenu *tempM = findSub(_currentMenuID - 1);
         if (tempM->_parent == _currentMenuParent)
         {
            --_currentMenuID;
            Draw(tempM);
         }
         else
         {
            CMenu *tempM = findSub(_currentMenuID);
            if (tempM->_editable) tempM->_action->Up();
            Draw(tempM);
         }
      }
      else if (_currentMenuID == 0)
      {
            CMenu *tempM = findSub(_currentMenuID);
            Draw(tempM);
      }
   }

   void CMenu::Draw(CMenu* subMenu)
   {
      system("cls");
      CMenu *tempM = findSub(_currentMenuParent);

      cout<<tempM->_title<<"\n";
      cout<<subMenu->_title<<"  ";
      if (subMenu->_editable)
      {
         cout<<subMenu->_action->getValue();
      }
   }

   void CMenu::Enter()
   {
      CMenu *tempM = findSub(_currentMenuID);
      
      if (!tempM->_editable) //sub Menu
      {
         if (tempM->_subMenu.size() != 0) //menu not empty
         {
         _currentMenuParent = _currentMenuID;
         _currentMenuID = tempM->_subMenu[0]->_item;
         }
         else//if menu empty
         {
            system("cls");
            cout<<tempM->_title<<"\n";
            cout<<"menu is empty\n";
         }
      }
      else //End item, not menu
      {
#ifdef EXEC_ON
         if (EXEC == tempM->_action->GetAction()) tempM->_action->Exec();
#endif
      }
      Draw(findSub(_currentMenuID));
   }

   void CMenu::Back()
   {
      _currentMenuID = _currentMenuParent;
      CMenu *tempM = findSub(_currentMenuID);
      
      _currentMenuParent = tempM->_parent;

      Draw(findSub(_currentMenuID));
   }

   bool CMenu::addEditableItem(const string title, const uint parent, CAction *action)
   {
      bool state = title.length() < LCD_STR_LENGTH;
      if (state)
      {
         CMenu *subMenu = findSub(parent);
         if (subMenu != nullptr)
         {
            if ((subMenu->_subMenu.size() == 0) && (subMenu->_action == nullptr))
            {
               state = subMenu->addItem(title, _itemCount, true, action);
               if (state) _itemCount++;
               else return state;
            }
         }
         else return false;
      }
      else return state;

      return true;
   }

   void CMenu::Flush(CMenu *menu) //сбрасывает меню в начальное состояние
   {
      menu->_currentMenuID = 1;
      menu->_currentMenuParent = 0;
      CMenu *tempM = findSub(_currentMenuID);
      Draw(tempM);
   }