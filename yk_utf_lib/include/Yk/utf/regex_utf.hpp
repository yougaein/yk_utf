#ifndef YK_UTF_REGEX_UTF_HPP
#define YK_UTF_REGEX_UTF_HPP

#include "cType.hpp"
#include "lowerCase.hpp"
#include "upperCase.hpp"

namespace boost{
	inline std::size_t hash_value(const char32_t& c){
		std::size_t h;
//		boost::hash_combine(h, *(int32_t*)&c);
		return h;
	}
}


#include <boost/functional/hash.hpp>
#include <boost/regex.hpp>


namespace Yk{
namespace UTF{


CType yk_lookup_classname(const char32_t* p1, const char32_t* p2);
boost::regex_constants::syntax_type yk_syntax_type(char32_t c);
boost::regex_constants::escape_syntax_type yk_escape_syntax_type(char32_t c);


template <class charT>
class boost_regex_traits;

template <>
class boost_regex_traits<char32_t>
{
private:
   typedef std::ctype<char32_t>         ctype_type;
public:
   typedef char32_t                     char_type;
   typedef char32_t                     charT;
   typedef std::size_t                  size_type;
   typedef std::basic_string<char_type> string_type;
   typedef std::locale                  locale_type;
   typedef CType        char_class_type;
   std::locale cur_locale;
   struct boost_extensions_tag{};

   boost_regex_traits()
   { }
   static size_type length(const char_type* p)
   {
      return std::char_traits<charT>::length(p);
   }
   boost::regex_constants::syntax_type syntax_type(charT c)const
   {
      return yk_syntax_type(c);
   }
   boost::regex_constants::escape_syntax_type escape_syntax_type(charT c) const
   {
      return yk_escape_syntax_type(c);
   }
   charT translate(charT c) const
   {
      return c;
   }
   charT translate_nocase(charT c) const
   {
      return getLowerCase(c);
   }
   charT translate(charT c, bool icase) const
   {
      return icase ? getLowerCase(c) : c;
   }
   charT tolower(charT c) const
   {
      return getLowerCase(c);
   }
   charT toupper(charT c) const
   {
      return getUpperCase(c);
   }
   string_type transform(const charT* p1, const charT* p2) const
   {
      return string_type(p1, p2 - p1);
   }
   string_type transform_primary(const charT* p1, const charT* p2) const;
   char_class_type lookup_classname(const charT* p1, const charT* p2) const
   {
      return yk_lookup_classname(p1, p2);
   }
   string_type lookup_collatename(const charT* p1, const charT* p2) const
   {
      return string_type();
   }
   bool isctype(charT c, char_class_type f) const
   {
      return getCType(c) & f;
   }
   int toi(const charT*& p, const charT* p2, int radix)const;
   int value(charT c, int radix)const
   {
      const charT* pc = &c;
      return toi(pc, pc + 1, radix);
   }
   locale_type imbue(locale_type l)
   {
      std::locale result(getloc());
      cur_locale = l;
      return result;
   }
   locale_type getloc()const
   {
      return cur_locale;
   }
   std::string error_string(boost::regex_constants::error_type n) const
   {
      return boost::re_detail::get_default_error_string(n);
   }

   //
   // extension:
   // set the name of the message catalog in use (defaults to "boost_regex").
   //
   static std::string catalog_name(const std::string& name);
   static std::string get_catalog_name();

/*private:
   //
   // catalog name handler:
   //
   static std::string& get_catalog_name_inst();*/

#ifdef BOOST_HAS_THREADS
   static boost::static_mutex& get_mutex_inst();
#endif
};

using Regex = boost::basic_regex<char32_t, boost_regex_traits<char32_t>>;

}
}

#endif