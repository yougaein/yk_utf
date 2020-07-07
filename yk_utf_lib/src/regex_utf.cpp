#include "../include/regex_utf.hpp"


namespace Yk{
namespace UTF{


struct CNameMaskData{
    std::basic_string<char32_t> name;
    size_t size;
    CType mask;
};


CType yk_lookup_classname(const char32_t* p1, const char32_t* p2){
   static std::vector<CNameMaskData> cNameMaskList = {
        {U"d", 1, Yk::UTF::ctDigit},
        {U"w", 1, ctWord},
        {U"h", 1, ctHorizontalSpace},
        {U"l", 1, ctLower},
        {U"s", 1, ctSpace},
        {U"u", 1, ctUpper},
        {U"v", 1, ctVerticalSpace},
        {U"alnum", 5, ctAlnum},
        {U"alpha", 5, ctAlpha},
        {U"ascii", 5, ctAscii},
        {U"blank", 5, ctBlank},
        {U"cntrl", 5, ctCntrl},
        {U"digit", 5, ctDigit},
        {U"graph", 5, ctGraph},
        {U"lower", 5, ctLower},
        {U"print", 5, ctPrint},
        {U"punct", 5, ctPunct},
        {U"space", 5, ctSpace},
        {U"upper", 5, ctUpper},
        {U"xdigit", 6, ctXdigit},
        {U"word", 4, ctWord},
   };
   int i = 0;
    for(const CNameMaskData& d : cNameMaskList){
        if(d.size == p2 - p1){
            for(const char32_t* p = p1 ; p != p2 ; ++p)
                if(d.name[p - p1] != *p)
                    goto brk;
            return d.mask;
        }
brk:
         ++i;
    }
    return 0;
}


boost::regex_constants::syntax_type yk_syntax_type(char32_t c){
   static boost::regex_constants::syntax_type char_syntax[] = {
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_newline,     /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /**/
      boost::regex_constants::syntax_char,        /* */    // 32
      boost::regex_constants::syntax_not,        /*!*/
      boost::regex_constants::syntax_char,        /*"*/
      boost::regex_constants::syntax_hash,        /*#*/
      boost::regex_constants::syntax_dollar,        /*$*/
      boost::regex_constants::syntax_char,        /*%*/
      boost::regex_constants::syntax_char,        /*&*/
      boost::regex_constants::escape_type_end_buffer,  /*'*/
      boost::regex_constants::syntax_open_mark,        /*(*/
      boost::regex_constants::syntax_close_mark,        /*)*/
      boost::regex_constants::syntax_star,        /***/
      boost::regex_constants::syntax_plus,        /*+*/
      boost::regex_constants::syntax_comma,        /*,*/
      boost::regex_constants::syntax_dash,        /*-*/
      boost::regex_constants::syntax_dot,        /*.*/
      boost::regex_constants::syntax_char,        /*/*/
      boost::regex_constants::syntax_digit,        /*0*/
      boost::regex_constants::syntax_digit,        /*1*/
      boost::regex_constants::syntax_digit,        /*2*/
      boost::regex_constants::syntax_digit,        /*3*/
      boost::regex_constants::syntax_digit,        /*4*/
      boost::regex_constants::syntax_digit,        /*5*/
      boost::regex_constants::syntax_digit,        /*6*/
      boost::regex_constants::syntax_digit,        /*7*/
      boost::regex_constants::syntax_digit,        /*8*/
      boost::regex_constants::syntax_digit,        /*9*/
      boost::regex_constants::syntax_colon,        /*:*/
      boost::regex_constants::syntax_char,        /*;*/
      boost::regex_constants::escape_type_left_word, /*<*/
      boost::regex_constants::syntax_equal,        /*=*/
      boost::regex_constants::escape_type_right_word, /*>*/
      boost::regex_constants::syntax_question,        /*?*/
      boost::regex_constants::syntax_char,        /*@*/
      boost::regex_constants::syntax_char,        /*A*/
      boost::regex_constants::syntax_char,        /*B*/
      boost::regex_constants::syntax_char,        /*C*/
      boost::regex_constants::syntax_char,        /*D*/
      boost::regex_constants::syntax_char,        /*E*/
      boost::regex_constants::syntax_char,        /*F*/
      boost::regex_constants::syntax_char,        /*G*/
      boost::regex_constants::syntax_char,        /*H*/
      boost::regex_constants::syntax_char,        /*I*/
      boost::regex_constants::syntax_char,        /*J*/
      boost::regex_constants::syntax_char,        /*K*/
      boost::regex_constants::syntax_char,        /*L*/
      boost::regex_constants::syntax_char,        /*M*/
      boost::regex_constants::syntax_char,        /*N*/
      boost::regex_constants::syntax_char,        /*O*/
      boost::regex_constants::syntax_char,        /*P*/
      boost::regex_constants::syntax_char,        /*Q*/
      boost::regex_constants::syntax_char,        /*R*/
      boost::regex_constants::syntax_char,        /*S*/
      boost::regex_constants::syntax_char,        /*T*/
      boost::regex_constants::syntax_char,        /*U*/
      boost::regex_constants::syntax_char,        /*V*/
      boost::regex_constants::syntax_char,        /*W*/
      boost::regex_constants::syntax_char,        /*X*/
      boost::regex_constants::syntax_char,        /*Y*/
      boost::regex_constants::syntax_char,        /*Z*/
      boost::regex_constants::syntax_open_set,        /*[*/
      boost::regex_constants::syntax_escape,        /*\*/
      boost::regex_constants::syntax_close_set,        /*]*/
      boost::regex_constants::syntax_caret,        /*^*/
      boost::regex_constants::syntax_char,        /*_*/
      boost::regex_constants::syntax_char,        /*`*/
      boost::regex_constants::syntax_char,        /*a*/
      boost::regex_constants::syntax_char,        /*b*/
      boost::regex_constants::syntax_char,        /*c*/
      boost::regex_constants::syntax_char,        /*d*/
      boost::regex_constants::syntax_char,        /*e*/
      boost::regex_constants::syntax_char,        /*f*/
      boost::regex_constants::syntax_char,        /*g*/
      boost::regex_constants::syntax_char,        /*h*/
      boost::regex_constants::syntax_char,        /*i*/
      boost::regex_constants::syntax_char,        /*j*/
      boost::regex_constants::syntax_char,        /*k*/
      boost::regex_constants::syntax_char,        /*l*/
      boost::regex_constants::syntax_char,        /*m*/
      boost::regex_constants::syntax_char,        /*n*/
      boost::regex_constants::syntax_char,        /*o*/
      boost::regex_constants::syntax_char,        /*p*/
      boost::regex_constants::syntax_char,        /*q*/
      boost::regex_constants::syntax_char,        /*r*/
      boost::regex_constants::syntax_char,        /*s*/
      boost::regex_constants::syntax_char,        /*t*/
      boost::regex_constants::syntax_char,        /*u*/
      boost::regex_constants::syntax_char,        /*v*/
      boost::regex_constants::syntax_char,        /*w*/
      boost::regex_constants::syntax_char,        /*x*/
      boost::regex_constants::syntax_char,        /*y*/
      boost::regex_constants::syntax_char,        /*z*/
      boost::regex_constants::syntax_open_brace,        /*{*/
      boost::regex_constants::syntax_or,        /*|*/
      boost::regex_constants::syntax_close_brace,        /*}*/
      boost::regex_constants::syntax_char,        /*~*/
   };
    if(c <= U"~"[0])
        return char_syntax[c];
    else
        return boost::regex_constants::syntax_char;
}


boost::regex_constants::escape_syntax_type yk_escape_syntax_type(char32_t c){
   static boost::regex_constants::escape_syntax_type char_syntax[] = {
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,     /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /**/
      boost::regex_constants::escape_type_identity,        /* */    // 32
      boost::regex_constants::escape_type_identity,        /*!*/
      boost::regex_constants::escape_type_identity,        /*"*/
      boost::regex_constants::escape_type_identity,        /*#*/
      boost::regex_constants::escape_type_identity,        /*$*/
      boost::regex_constants::escape_type_identity,        /*%*/
      boost::regex_constants::escape_type_identity,        /*&*/
      boost::regex_constants::escape_type_end_buffer,        /*'*/
      boost::regex_constants::syntax_open_mark,        /*(*/
      boost::regex_constants::syntax_close_mark,        /*)*/
      boost::regex_constants::escape_type_identity,        /***/
      boost::regex_constants::syntax_plus,                 /*+*/
      boost::regex_constants::escape_type_identity,        /*,*/
      boost::regex_constants::escape_type_identity,        /*-*/
      boost::regex_constants::escape_type_identity,        /*.*/
      boost::regex_constants::escape_type_identity,        /*/*/
      boost::regex_constants::escape_type_decimal,        /*0*/
      boost::regex_constants::escape_type_backref,        /*1*/
      boost::regex_constants::escape_type_backref,        /*2*/
      boost::regex_constants::escape_type_backref,        /*3*/
      boost::regex_constants::escape_type_backref,        /*4*/
      boost::regex_constants::escape_type_backref,        /*5*/
      boost::regex_constants::escape_type_backref,        /*6*/
      boost::regex_constants::escape_type_backref,        /*7*/
      boost::regex_constants::escape_type_backref,        /*8*/
      boost::regex_constants::escape_type_backref,        /*9*/
      boost::regex_constants::escape_type_identity,        /*:*/
      boost::regex_constants::escape_type_identity,        /*;*/
      boost::regex_constants::escape_type_left_word,        /*<*/
      boost::regex_constants::escape_type_identity,        /*=*/
      boost::regex_constants::escape_type_right_word,        /*>*/
      boost::regex_constants::syntax_question,              /*?*/
      boost::regex_constants::escape_type_identity,         /*@*/
      boost::regex_constants::escape_type_start_buffer,     /*A*/
      boost::regex_constants::escape_type_not_word_assert,  /*B*/
      boost::regex_constants::escape_type_C,                /*C*/
      boost::regex_constants::escape_type_not_class,        /*D*/
      boost::regex_constants::escape_type_E,                /*E*/
      boost::regex_constants::escape_type_not_class,        /*F*/
      boost::regex_constants::escape_type_G,                /*G*/
      boost::regex_constants::escape_type_not_class,        /*H*/
      boost::regex_constants::escape_type_not_class,        /*I*/
      boost::regex_constants::escape_type_not_class,        /*J*/
      boost::regex_constants::escape_type_reset_start_mark, /*K*/
      boost::regex_constants::escape_type_not_class,        /*L*/
      boost::regex_constants::escape_type_not_class,        /*M*/
      boost::regex_constants::escape_type_named_char,       /*N*/
      boost::regex_constants::escape_type_not_class,        /*O*/
      boost::regex_constants::escape_type_not_property,     /*P*/
      boost::regex_constants::escape_type_Q,                /*Q*/
      boost::regex_constants::escape_type_line_ending,      /*R*/
      boost::regex_constants::escape_type_not_class,        /*S*/
      boost::regex_constants::escape_type_not_class,        /*T*/
      boost::regex_constants::escape_type_not_class,        /*U*/
      boost::regex_constants::escape_type_not_class,        /*V*/
      boost::regex_constants::escape_type_not_class,        /*W*/
      boost::regex_constants::escape_type_X,                /*X*/
      boost::regex_constants::escape_type_not_class,        /*Y*/
      boost::regex_constants::escape_type_Z,                /*Z*/
      boost::regex_constants::escape_type_identity,        /*[*/
      boost::regex_constants::escape_type_identity,        /*\*/
      boost::regex_constants::escape_type_identity,        /*]*/
      boost::regex_constants::escape_type_identity,        /*^*/
      boost::regex_constants::escape_type_identity,        /*_*/
      boost::regex_constants::escape_type_start_buffer,        /*`*/
      boost::regex_constants::escape_type_control_a,        /*a*/
      boost::regex_constants::escape_type_word_assert,        /*b*/
      boost::regex_constants::escape_type_ascii_control,        /*c*/
      boost::regex_constants::escape_type_class,        /*d*/
      boost::regex_constants::escape_type_e,        /*e*/
      boost::regex_constants::escape_type_control_f,       /*f*/
      boost::regex_constants::escape_type_extended_backref,  /*g*/
      boost::regex_constants::escape_type_class,        /*h*/
      boost::regex_constants::escape_type_class,        /*i*/
      boost::regex_constants::escape_type_class,        /*j*/
      boost::regex_constants::escape_type_extended_backref, /*k*/
      boost::regex_constants::escape_type_class,        /*l*/
      boost::regex_constants::escape_type_class,        /*m*/
      boost::regex_constants::escape_type_control_n,       /*n*/
      boost::regex_constants::escape_type_class,           /*o*/
      boost::regex_constants::escape_type_property,        /*p*/
      boost::regex_constants::escape_type_class,           /*q*/
      boost::regex_constants::escape_type_control_r,       /*r*/
      boost::regex_constants::escape_type_class,           /*s*/
      boost::regex_constants::escape_type_control_t,       /*t*/
      boost::regex_constants::escape_type_class,         /*u*/
      boost::regex_constants::escape_type_control_v,       /*v*/
      boost::regex_constants::escape_type_class,           /*w*/
      boost::regex_constants::escape_type_hex,             /*x*/
      boost::regex_constants::escape_type_class,           /*y*/
      boost::regex_constants::escape_type_end_buffer,      /*z*/
      boost::regex_constants::syntax_open_brace,           /*{*/
      boost::regex_constants::syntax_or,                   /*|*/
      boost::regex_constants::syntax_close_brace,          /*}*/
      boost::regex_constants::escape_type_identity,        /*~*/
    };
    if(c <= U"~"[0])
        return char_syntax[c];
    else
        return boost::regex_constants::escape_type_identity;
}



boost_regex_traits<char32_t>::string_type boost_regex_traits<char32_t>::transform_primary(const charT* p1, const charT* p2) const
{
    string_type tmp;
    tmp.reserve(p2 - p1);
    for(const charT* p = p1 ; p != p2 ; ++p)
        tmp[p - p1] = getLowerCase(*p);
    return tmp;
}


int boost_regex_traits<char32_t>::toi(const charT*& p, const charT* p2, int radix)const{
    int i = -1;
    if(radix <= 10){
        for( ; p != p2 ; ++p){
        if(*p < U"0"[0] || U"9"[0] < *p)
            break;
        if(i == -1)
            i = *p - U"0"[0];
        else
            i = i * radix + *p - U"0"[0];
        }
    }else if(radix <= 36){
        for( ; p != p2 ; ++p){
        if(*p < U"0"[0] || (U"9"[0] < *p && *p < U"A"[0]) || (U"A"[0] + radix - 11 < *p && *p < U"a"[0]) || U"a"[0] + radix - 11 < *p)
            break;
        if(i == -1)
            i = 0;
        if(*p <= U"9"[0])
            i = i * radix + *p - U"0"[0];
        else if(*p <= U"Z"[0])
            i = i * radix + *p - U"A"[0];
        else
            i = i * radix + *p - U"a"[0];
        }
    }else
        i = -1;
    return i;
}

}
}


/*namespace Yk{
   namespace UTF{
      struct Property {
         std::basic_string<char32_t> name, value;
         Property(std::basic_string<char32_t> n, v) : name(n), value(v){ }
      };
      struct YkCType {
         enum Mode {
            mNeg, mAnd, mOr, mProp, mPosix
         } mode;
         union {
            CType ctype;
            Property prop;
            struct{
               YkCType* left, * right;
            };
         };
         struct Tokenizer{
            YkCType* parent;
            Tokenizer(YkCType* p) : parent(p){ }
            struct Token{
               virtual void add(YkCType* toAnal) = 0;
            }
            struct TokenWord : Token{
               void add(Tokenizer* toAnal){
                  toAnal->tpStack.emplace_back(TokenList());
               }
            }
            struct TokenPOpen : Token{
               TokenList* nextLevel;
               void add(Tokenizer* toAnal){
                  toAnal->tpStack.back().emplace_back(this);
                  nextLevel = new TokenList;
                  toAnal->tpStack.emplace_back(nextLevel);
               }
            };
            struct TokenPClose : Token{
               void add(Tokenizer* toAnal){
                  if(toAnal->tpStack.size() <= 1)
                     throw Error.new("isolated closing parenthesis");
                  toAnal->tpStack.pop_back();
               }
            };
            typedef std::list<std::auto_ptr<Token>> TokenList;
            std::list<TokenList> tpStack;
            void addToken(std::basic_string<char32_t>::iterator it, std::basic_string<char32_t>::iterator jt){
               if(it - jt >= 3 && *it == U'0' && (*(it + 1) == U'x' || *(it + 1) == U'X')){ //0x12ABC
                  (new TokenHex(it + 1, jt))->add(this);
               }else if(isAsciiNum(*it)){
                  (new TokenDec(it, jt))->add(this);
               }else if(isAsciiWord(*it)){
                  (new TokenWord(it, jt))->add(this);
               }else if(isAsciiSpace(*it)){
                  ;//ignore space
               }else{
                  switch(*it){               
                  case U'(':
                     (new TokenPOpen)->add(this);
                     break;
                  case U')':
                     (new TokenPClose)->add(this);
                     break;
                  case U'&':
                     (new TokenAmp)->add(this);
                     break;
                  case U'|':
                     (new TokenVert)->add(this);
                     break;
                  case U'=':
                     (new TokenEql)->add(this);
                     break;
                  case U'!':
                     if(jt - it >= 2)
                        (new TokenNotEql)->add(this);
                     else
                        (new TokenNot)->add(this);
                     break;
                  }
               }
            }
         };
         YkCType(std::basic_string<char32_t> str){
            Tokenizer tkn(this);
            auto it = str.begin(), jt = it;
            while(1){
               if(isAsciiSpace(*it)){
                  if(jt != it) tkn.addToken(jt, it);
                  jt = it;
                  do{
                     ++it;
                     if(it == str.end())
                        break;
                  }while(isAsciiSpace(*it));
               }else if(isAsciiWord(*it)){ //digit, hex
                  if(jt != it) tkn.addToken(jt, it);
                  jt = it;
                  do{
                     ++it;
                     if(it == str.end())
                        break;
                  }while(isAsciiWord(*it));
               }else{
                  switch(*it){
                  case U"("[0]:
                  case U")"[0]:
                  case U"&"[0]:
                  case U"|"[0]:
                  case U"="[0]:
                     if(jt != it) tkn.addToken(jt, it);
                     jt = it;
                     ++it;
                     if(it == str.end())
                        break;
                     break;
                  case U"!"[0]:
                     if(jt != it) tkn.addToken(jt, it);
                     jt = it;
                     ++it;
                     if(it == str.end())
                        break;
                     if(*it == U"="[0])
                        ++it;
                  default:
                     throw ErrorUnknowChar(*it);
                     break;
                  }
               }
               ++jt;
            }
         } 
         YkCType(Mode m, const YkCType&& l) : mode(m), left(l), right(0){ }
         YkCType(Mode m, const YkCType&& l, const YkCType&& r) : mode(m), left(l), right(r){ }
         YkCType(CType ct) : mode(mPosix), ctype(ct){ }
         YkCType(Property p) : mode(mProp), prop(p){ }
         YkCType(const YkCType& arg) : mode(arg.mode) {
            switch(mode){
            case mNeg:
            case mAnd:
            case mOr:
               if(arg.left) left = new YkCType(*arg.left);
               if(arg.right) right = new YkCType(*arg.right);
               break;
            case mProp:
               prop = arg.prop;
               break;
            case mPosix:
               ctype = arg.ctype;
               break;
            }
         }
         void deletePointer(){
            switch(mode){
            case mNeg:
            case mAnd:
            case mOr:
               if(left) delete left;
               if(right) delete right;
            }
         }
         ~YkCType(){
            deletePointer();
         }
         YkCType& operator=(const YkCType& arg){
            deletePointer();
            mode = arg.mode;
            switch(mode){
            case mNeg:
            case mAnd:
            case mOr:
               if(arg.left) left = new YkCType(*arg.left);
               if(arg.right) right = new YkCType(*arg.right);
            case mProp:
               prop = arg.prop;
               break;
            case mPosix:
               ctype = arg.ctype;
               break;

            }
            return *this;
         }
         YkCType& operator|=(const YkCType& arg){
            YkCType* l, * r;
            l = new YkCType(*this);
            r = new YkCType(arg);
            deletePointer();
            mode = mOr;
            left = l
            right = r;
            return *this;
         }
         YkCType& operator&=(const YkCType& arg){
            YkCType* l, * r;
            l = new YkCType(*this);
            r = new YkCType(arg);
            deletePointer();
            mode = mAnd;
            left = l
            right = r;
            return *this;
         }
         YkCType&& operator|(const YkCType&& arg)const{
            return YkCType(mOr, *this, arg);
         }
         YkCType&& operator&(const YkCType&& arg)const{
            return YkCType(mAnd, *this, arg);
         }
         YkCType operator~()const{
            return YkCType(mNeg, *this);
         }
      }
   }
}*/


