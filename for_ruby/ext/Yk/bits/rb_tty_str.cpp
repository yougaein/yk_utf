	
#include <ruby.h>
#include <new>
#include <string>
#include <Yk/utf/unicodeStr.hpp>

static VALUE rb_mYk;


using namespace std;

static Yk::UTF::UnicodeStr* ttyStr(VALUE self){
    Yk::UTF::UnicodeStr* p;
    Data_Get_Struct(self, Yk::UTF::UnicodeStr, p);
    return p;
}



static void ttyStr_free(Yk::UTF::UnicodeStr* p){
    p->Yk::UTF::UnicodeStr::~UnicodeStr();
    ruby_xfree(p);
}


static VALUE ttyStr_alloc(VALUE klass){
    void* p = ruby_xmalloc(sizeof(Yk::UTF::UnicodeStr));
    new(p) Yk::UTF::UnicodeStr();
    return Data_Wrap_Struct(klass, NULL, ttyStr_free, p);
}

static VALUE ttyStr_init(VALUE self, VALUE arg){
	Yk::UTF::UnicodeStr* p = ttyStr(self);
    p->Yk::UTF::UnicodeStr::~UnicodeStr();
    Check_Type(arg, T_STRING);
    new(p) Yk::UTF::UnicodeStr(std::string(StringValuePtr(arg), RSTRING_LEN(arg)));
    return self;
}

static VALUE ttyStr_height(VALUE self, VALUE width, VALUE tab){
	Yk::UTF::UnicodeStr* p = ttyStr(self);
    Check_Type(width, T_FIXNUM);
    Check_Type(tab, T_FIXNUM);
    size_t res = p->lineCount(FIX2INT(width), FIX2INT(tab));
    return INT2FIX(res);
}


struct Func_for_ttyStr_each_line{
    void operator()(std::string s){
        rb_yield(rb_str_new(s.c_str(), s.size()));
    }
};


static VALUE ttyStr_each_line(VALUE self, VALUE width, VALUE tab, VALUE regexp, VALUE attr){
	Yk::UTF::UnicodeStr* p = ttyStr(self);
    Check_Type(width, T_FIXNUM);
    Check_Type(tab, T_FIXNUM);
    Check_Type(regexp, T_STRING);
    Check_Type(attr, T_FIXNUM);
    p->eachLineWithMatch(FIX2INT(width), FIX2INT(tab), std::string(StringValuePtr(regexp), RSTRING_LEN(regexp)), Yk::UTF::TTYAttr(FIX2INT(attr)), Func_for_ttyStr_each_line());
    return self;
}

static VALUE ttyStr_has_match(VALUE self, VALUE regexp){
	Yk::UTF::UnicodeStr* p = ttyStr(self);
    Check_Type(regexp, T_STRING);
    if(p->hasRegexMatch(Yk::UTF::UnicodeStr::to_U(std::string(StringValuePtr(regexp), RSTRING_LEN(regexp)))))
        return Qtrue;
    else
        return Qfalse;
}

extern "C" void Init_TTYStr(void){
    rb_mYk = rb_define_module("Yk");
	VALUE cTTYStr = rb_define_class_under(rb_mYk, "TTYStr", rb_cObject);
	rb_define_alloc_func(cTTYStr, ttyStr_alloc);
	rb_define_method(cTTYStr, "initialize", RUBY_METHOD_FUNC(ttyStr_init), 1);
	rb_define_method(cTTYStr, "height", RUBY_METHOD_FUNC(ttyStr_height), 2);
	rb_define_method(cTTYStr, "each_line", RUBY_METHOD_FUNC(ttyStr_each_line), 4);
    rb_define_method(cTTYStr, "has_match", RUBY_METHOD_FUNC(ttyStr_has_match), 1);
    rb_define_const(cTTYStr, "FgBlack", INT2FIX(Yk::UTF::TTYAttr::i_fgBlack));
    rb_define_const(cTTYStr, "FgRed", INT2FIX(Yk::UTF::TTYAttr::i_fgRed));
    rb_define_const(cTTYStr, "FgGreen", INT2FIX(Yk::UTF::TTYAttr::i_fgGreen));
    rb_define_const(cTTYStr, "FgYellow", INT2FIX(Yk::UTF::TTYAttr::i_fgYellow));
    rb_define_const(cTTYStr, "FgBlue", INT2FIX(Yk::UTF::TTYAttr::i_fgBlue));
    rb_define_const(cTTYStr, "FgPurple", INT2FIX(Yk::UTF::TTYAttr::i_fgPurple));
    rb_define_const(cTTYStr, "FgCyan", INT2FIX(Yk::UTF::TTYAttr::i_fgCyan));
    rb_define_const(cTTYStr, "FgWhite", INT2FIX(Yk::UTF::TTYAttr::i_fgWhite));
    rb_define_const(cTTYStr, "FgDefault", INT2FIX(Yk::UTF::TTYAttr::i_fgDefault));
    rb_define_const(cTTYStr, "BgBlack", INT2FIX(Yk::UTF::TTYAttr::i_bgBlack));
    rb_define_const(cTTYStr, "BgRed", INT2FIX(Yk::UTF::TTYAttr::i_bgRed));
    rb_define_const(cTTYStr, "BgGreen", INT2FIX(Yk::UTF::TTYAttr::i_bgGreen));
    rb_define_const(cTTYStr, "BgYellow", INT2FIX(Yk::UTF::TTYAttr::i_bgYellow));
    rb_define_const(cTTYStr, "BgBlue", INT2FIX(Yk::UTF::TTYAttr::i_bgBlue));
    rb_define_const(cTTYStr, "BgPurple", INT2FIX(Yk::UTF::TTYAttr::i_bgPurple));
    rb_define_const(cTTYStr, "BgCyan", INT2FIX(Yk::UTF::TTYAttr::i_bgCyan));
    rb_define_const(cTTYStr, "BgWhite", INT2FIX(Yk::UTF::TTYAttr::i_bgWhite));
    rb_define_const(cTTYStr, "BgDefault", INT2FIX(Yk::UTF::TTYAttr::i_bgDefault));
    rb_define_const(cTTYStr, "Bold", INT2FIX(Yk::UTF::TTYAttr::i_bold));
    rb_define_const(cTTYStr, "Shallow", INT2FIX(Yk::UTF::TTYAttr::i_shallow));
    rb_define_const(cTTYStr, "Italic", INT2FIX(Yk::UTF::TTYAttr::i_italic));
    rb_define_const(cTTYStr, "Underline", INT2FIX(Yk::UTF::TTYAttr::i_underline));
    rb_define_const(cTTYStr, "Blink", INT2FIX(Yk::UTF::TTYAttr::i_blink));
    rb_define_const(cTTYStr, "FastBlink", INT2FIX(Yk::UTF::TTYAttr::i_fastBlink));
    rb_define_const(cTTYStr, "Reverse", INT2FIX(Yk::UTF::TTYAttr::i_reverse));
    rb_define_const(cTTYStr, "Hide", INT2FIX(Yk::UTF::TTYAttr::i_hide));
    rb_define_const(cTTYStr, "Strike", INT2FIX(Yk::UTF::TTYAttr::i_strike));

}
