#include <sstream>

namespace utils
{
   std::string to_string(unsigned short int val)
   {
      std::stringstream ss;
      ss << val;
      std::string str = ss.str();
      return str;
   }

   std::string to_string(float val)
   {
      std::stringstream ss;
      ss << val;
      std::string str = ss.str();
      return str;
   }
}