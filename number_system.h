
#include <string>

using namespace mvc_utils::io;
using namespace mvc_utils::math;

namespace math
{
   namespace number_system
   {
      enum number_base {bin, oct, dec, hex, base32, base64};
      class Hex;

      template <class T>
      char hex_alpha(T num)
      {
         switch (num)
         {
            case 10: return 'A';
            case 11: return 'B';
            case 12: return 'C';
            case 13: return 'D';
            case 14: return 'E';
            case 15: return 'F';
            default: return 'X';
         }
      }

      int hex_num(char num)
      {
         /*int i = 0;
         for (char c = 'A'; c <= 'F'; ++c, ++i)
            if (c == num)
               return 10 + i;
         return -1;*/
         switch (num)
         {
            case 'A': return 10;
            case 'B': return 11;
            case 'C': return 12;
            case 'D': return 13;
            case 'E': return 14;
            case 'F': return 15;
         }
         return -1;
      }

      template <class T_RET = int, class T_NUM>
      T_RET to_dec(T_NUM num, int base)
      {
         T_RET res= 0;
         string s = to_string(num);
         for (size_t i = 0, power = s.size() - 1; i != s.size(); ++i, --power)
         {
            if (base == 16 && isalpha(s[i]))
               res += hex_num(s[i]) * exponent<T_RET>(base, power);
            else
               res += to_num(s[i])  * exponent<T_RET>(base, power);
         }
         return res;
      }

      template <class T_RET>
      T_RET to_dec(char num, int base)
      {
         T_RET res= 0;
         size_t power = 0;

         if (base == 16 && isalpha(num))
            res += hex_num(num);
         else
            res += to_num(num)  * exponent<T_RET>(base, power);

         return res;
      }

      template <class T_RET>
      T_RET to_dec(const string& num, int base)
      {
         T_RET res= 0;

         for (size_t i = 0, power = num.size() - 1; i != num.size(); ++i, --power)
         {
            if (base == 16 && isalpha(num[i]))
               res += hex_num(num[i]) * exponent<T_RET>(base, power);
            else
               res += to_num(num[i])  * exponent<T_RET>(base, power);
         }

         return res;
      }

      template <class T_RET>
      T_RET to_dec(const char* num, int base)
      {
         return to_dec<T_RET>(static_cast<string>(num), base);
      }

      void usages()
      {
         print_ln(to_dec<int>(24, 32));
         print_ln(to_dec<int>(24, 16));
         print_ln(to_dec<int>('B', 16));
         print_ln(to_dec<int>('6', 16));
         print_ln(to_dec<int>("BB", 16));
         print_ln(to_dec<int>("4C", 16));
         print_ln(to_dec<int>("4CDC", 16));
         print_ln(to_dec<int>(10, 2));
      }
   }

   class number_system::Hex
   {
      public:
         Hex(int val, number_base bs = hex) : i_val(val), m_base(bs) { }
         Hex(char cval, number_base bs = hex) : c_val(cval), m_base(bs)  { }
         Hex(const string& , number_base = hex);

         template <class T>
         T convert(number_system::number_base);

         void set_value(int);
         void set_value(char);
         void set_value(const string&);

         int& to_int() { return i_val; }
         c_string& to_string() { return s_val; }

         int& operator+(int);
         int& operator+(char);
         int operator+(c_string&);

      private:
         int i_val;
         char c_val;
         string s_val;
         number_base m_base = hex;
   };

   using namespace math::number_system;

   Hex::Hex(const string& sval, number_base bs) : i_val(to_num<long>(sval)), s_val(sval), m_base(bs)
   {
   }

   int& Hex::operator+(int rhs)
   {
      return i_val = (0x0 + (i_val + rhs));
   }

   int& Hex::operator+(char rhs)
   {
      return i_val = 0x0 + (i_val + (rhs - '0'));
   }

   int Hex::operator+(c_string& rhs)
   {
      //
   }

   template <class T>
   T Hex::convert(number_system::number_base base)
   {
      switch(base)
      {
         case bin:
            break;

         case oct:
            break;

         case dec:
            return to_dec<T>(s_val);
            break;
      }
   }

   void Hex::set_value(int val)
   {
      i_val = val;
   }

   void Hex::set_value(c_string &val)
   {
      s_val = val;
      i_val = to_num<long>(s_val);
   }

   void usage_hex()
   {
      Hex h(12);

      h + 12;

      print_ln(h.to_int());
   }
}


