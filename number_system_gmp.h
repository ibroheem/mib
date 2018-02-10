#ifndef NUMBER_SYSTEM_H
#define NUMBER_SYSTEM_H

using std::string;

struct mpz_div_t
{
   mpz_div_t() = default;

   mpz_div_t(const mpz_class& num, uint den) : quot(num / den), rem(num % den) { }

   mpz_div_t& operator()(const mpz_class& num, uint den)
   {
      quot = num / den;
      rem  = num % den;
      return *this;
   }

   mpz_div_t& operator()(const mpz_class& num, const mpz_class& den)
   {
      quot = num / den;
      rem  = num % den;
      return *this;
   }
   mpz_class quot;	/* Quotient.  */
   mpz_class rem;		/* Remainder.  */
};

/** Number system class support arbitrary values of up to base  36 */
class number_system
{
   public:
      enum base {bin = 2, oct = 8, dec = 10, hex = 16, base32 = 32};

      number_system() = default;
      number_system(cchar* val, base _base = dec) : m_value_str(val), m_value_num(from_base(_base)), m_base(_base)
      {
        //;
      }

      number_system(string&  val, base _base = dec) : m_value_str(val), m_value_num(from_base(_base)), m_base(_base)
      {
        //;
      }

      number_system(string&& val, base _base = dec) : m_value_str(std::move(val)),
                                                      m_value_num(std::move(from_base(_base))), m_base(_base)
      {
      }

      /*number_system(number_system&  lhs) : m_value_str(lhs.m_value_str), m_value_num(lhs.m_value_num),
                                           m_base(lhs.m_base) {cout << "CPC.."; }

      number_system(number_system&& lhs) : m_value_str(std::move(lhs.m_value_str)),
                                           m_value_num(std::move(lhs.m_value_num)), m_base(lhs.m_base)
                                           { cout << "MVC.."; }*/

      number_system& set_base(base _base) { m_base = _base ; return *this; }

      number_system& set_value(string&, base);
      number_system& set_value(string&&, base);

      base&  number_base() { return m_base; }
      cchar* number_base_str();

      string to_base(base);

      string& value_str() { return m_value_str; }
      mpz_class& value_num() { return m_value_num; }

      number_system& operator+=(number_system& rhs)
      {
         m_value_num += rhs.m_value_num;
         m_value_str = m_value_num.get_str(number_base());
         return *this;
      }

      friend number_system operator+(number_system& lhs, number_system& rhs)
      {
         number_system result = lhs;
         lhs += rhs;
         return lhs;
      }

      number_system& operator-=(number_system& rhs)
      {
         m_value_num -= rhs.m_value_num;
         m_value_str = m_value_num.get_str(number_base());
         return *this;
      }

      friend number_system operator-(number_system& lhs, number_system& rhs)
      {
         number_system result = lhs;
         lhs -= rhs;
         return lhs;
      }

      number_system& operator*=(number_system& rhs)
      {
         m_value_num *= rhs.m_value_num;
         m_value_str  = m_value_num.get_str(number_base());
         return *this;
      }

      friend number_system operator*(number_system& lhs, number_system& rhs)
      {
         number_system result = lhs;
         lhs *= rhs;
         return lhs;
      }

      number_system& operator/=(number_system& rhs)
      {
         m_value_num /= rhs.m_value_num;
         m_value_str = m_value_num.get_str(number_base());
         return *this;
      }

      friend number_system operator/(number_system& lhs, number_system& rhs)
      {
         number_system result = lhs;
         lhs /= rhs;
         return lhs;
      }

      number_system& operator%=(number_system& rhs)
      {
         m_value_num %= rhs.m_value_num;
         m_value_str = m_value_num.get_str(number_base());
         return *this;
      }

      friend number_system operator%(number_system& lhs, number_system& rhs)
      {
         number_system result = lhs;
         lhs %= rhs;
         return lhs;
      }

   private:
      mpz_class from_base(base);

   private:
      string    m_value_str, digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //up to base36
      mpz_class m_value_num;
      base      m_base = dec;
};

number_system operator"" _bin(cchar* num)
{
   return number_system(num, number_system::bin);
}

number_system operator"" _oct(cchar* num)
{
   return number_system(num, number_system::oct);
}

number_system operator"" _dec(cchar* num)
{
   return number_system(num, number_system::dec);
}

number_system operator"" _hex(cchar* num)
{
   return number_system(num, number_system::hex);
}

mpz_class number_system::from_base(base _base)
{
   mpz_class result(m_value_str, _base);
   return result;
}

cchar* number_system::number_base_str()
{
   switch (m_base)
   {
      case bin:
         return "bin";
      break;

      case oct:
         return "oct";
      break;

      case dec:
         return "dec";
      break;

      case hex:
         return "hex";
      break;

      default:
         break;
   }
   return "";
}

inline number_system& number_system::set_value(string& val, base _base = dec)
{
   set_base(_base);
   m_value_str = val;
   m_value_num.set_str(m_value_str, _base);
   return *this;
}

inline number_system& number_system::set_value(string&& val, base _base = dec)
{
   set_base(_base);
   m_value_str = std::move(val);
   m_value_num.set_str(m_value_str, _base);
   return *this;
}

string number_system::to_base(base _base)
{
   if (_base == m_base)
      return m_value_str;

   return m_value_num.get_str(_base);
}

void print_values(number_system& obj)
{
   using namespace mvc_utils::io;
   print_w_tab_ln("value: ", obj.value_num());
   print_w_tab_ln("internal rep: ", obj.value_num());
   print_w_tab_ln("interface rep: ", obj.value_str(), obj.number_base_str());
   print_w_tab_ln("bin:", obj.to_base(number_system::bin));
   print_w_tab_ln("oct:", obj.to_base(number_system::oct));
   print_w_tab_ln("dec:", obj.to_base(number_system::dec));
   print_w_tab_ln("hex:", obj.to_base(number_system::hex)); NL
}

void usage_number_system(uint ctrl)
{
   switch (ctrl)
   {
      case 1:
      {
         string num("200");
         number_system nsys(string("200"), number_system::base::hex);
         print_values(nsys);

         auto nsys2(nsys);
         print_values(nsys2);

         nsys.set_value("10011", number_system::dec);
         print_values(nsys);

         auto nsys3 = nsys2 * nsys; // uses nsys2's base unless stated otherwise i.e nsys3.set_base();
         nsys3.set_base(number_system::dec); // Not A good Idea use nsys2's, it's the one initiating  operator*
         nsys3.set_base(nsys2.number_base());
         print_values(nsys3);
      } break;

      case 2:
      {

      } break;

      case 3:
      {

      } break;

      default:
         break;
   }

}

#endif//NUMBER_SYSTEM_H
