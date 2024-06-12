#include <Yk/utf/unicodeStr.hpp>
#include <Yk/utf/canonicalCombiningClass.hpp>
#include <Yk/utf/decompData.hpp>
#include <Yk/utf/lineBreakProperty.hpp>
#include <Yk/utf/generalCategoryProperty.hpp>

#define is_trail(c) (c > 0x7F && c < 0xC0)
#define SUCCESS true
#define FAILURE false

namespace Yk{
namespace UTF{

//© Masaki Kagaya.
char32_t nextCodePoint(const std::string& s, size_t *cursor)
{
    char32_t code_point;
    const unsigned char *str = (const unsigned char *)s.c_str();
    size_t str_size = s.size();
    size_t pos = *cursor;
    size_t rest_size = str_size - pos;
    unsigned char c;
    unsigned char min;
    unsigned char max;

    code_point = 0;

    if (*cursor >= str_size) {
        return 0xfffd;
    }

    c = str[pos];

    if (rest_size < 1) {
        code_point = -1;
        pos += 1;
    } else if (c < 0x80) {
        code_point = str[pos];
        pos += 1;
    } else if (c < 0xC2) {
        code_point = 0xfffd;
        pos += 1;
    } else if (c < 0xE0) {

        if (rest_size < 2 || !is_trail(str[pos + 1])) {
            code_point = 0xfffd;
            pos += 1;
        } else {
            code_point = ((str[pos] & 0x1F) << 6) | (str[pos + 1] & 0x3F);
            pos += 2;
        }

    } else if (c < 0xF0) {

        min = (c == 0xE0) ? 0xA0 : 0x80;
        max = (c == 0xED) ? 0x9F : 0xBF;

        if (rest_size < 2 || str[pos + 1] < min || max < str[pos + 1]) {
            code_point = 0xfffd;
            pos += 1;         
        } else if (rest_size < 3 || !is_trail(str[pos + 2])) {
            code_point = 0xfffd;
            pos += 2;
        } else {
            code_point = ((str[pos]     & 0x1F) << 12) 
                       | ((str[pos + 1] & 0x3F) <<  6) 
                       |  (str[pos + 2] & 0x3F);
            pos += 3;
        }

    } else if (c < 0xF5) {

        min = (c == 0xF0) ? 0x90 : 0x80;
        max = (c == 0xF4) ? 0x8F : 0xBF;

        if (rest_size < 2 || str[pos + 1] < min || max < str[pos + 1]) {
            code_point = 0xfffd;
            pos += 1;
        } else if (rest_size < 3 || !is_trail(str[pos + 2])) {
            code_point = 0xfffd;
            pos += 2;
        } else if (rest_size < 4 || !is_trail(str[pos + 3])) {
            code_point = 0xfffd;
            pos += 3;
        } else {
            code_point = ((str[pos]     &  0x7) << 18)
                       | ((str[pos + 1] & 0x3F) << 12)
                       | ((str[pos + 2] & 0x3F) << 6)
                       |  (str[pos + 3] & 0x3F);
            pos += 4;
        }
    } else {
        code_point = 0xfffd;
        pos += 1;
    }

    *cursor = pos;

    return code_point;
}


std::string TTYAttr::operator-(const TTYAttr& arg)const{
    std::vector<int> args;
    if(_bold != arg._bold && !_bold){
		args.push_back(0);
		goto resume;
	}
    if(_doubleUnderline != arg._doubleUnderline && !_doubleUnderline){
		args.push_back(0);
		goto resume;
	}
	goto pass;
resume:
	{
		if(fgColor != -1 && fgColor != colDefault)
			args.push_back(fgColorArg + colDefault);
		if(_bold)
			args.push_back(boldArg + 0);
		if(_blink)
			args.push_back(blinkArg + 0);
		if(_underline)
			args.push_back(underlineArg + 0);
		if(_italic)
			args.push_back(italicArg + 0);
		if(_shallow)
			args.push_back(shallowArg + 0);
		if(_fastBlink)
			args.push_back(fastBlinkArg + 0);
		if(_hide)
			args.push_back(hideArg + 0);
		if(_strike)
			args.push_back(strikeArg + 0);
		if(_doubleUnderline)
			args.push_back(doubleUnderlineArg + 0);
		goto skip;
	}
pass:
	if(fgColor == colDefault && arg.fgColor != -1 && arg.fgColor != colDefault)
		args.push_back(fgColorArg + colDefault);
    else if(fgColor != arg.fgColor && fgColor != -1)
        args.push_back(fgColorArg + fgColor);
	if(bgColor == colDefault && arg.bgColor != -1 && arg.bgColor != colDefault)
		args.push_back(bgColorArg + colDefault);
    else if(bgColor != arg.bgColor && bgColor != -1)
        args.push_back(bgColorArg + bgColor);
    if(_bold != arg._bold && _bold)
        args.push_back(boldArg + 0);
    if(_blink != arg._blink)
        args.push_back((!_blink ? cancelArg : 0) +  blinkArg);
    if(_underline != arg._underline)
        args.push_back((!_underline ? cancelArg : 0) +  underlineArg);
    if(_italic != arg._italic)
        args.push_back((!_italic ? cancelArg : 0) +  italicArg);
    if(_shallow != arg._shallow)
        args.push_back((!_shallow ? cancelArg : 0) +  shallowArg);
    if(_fastBlink != arg._fastBlink)
        args.push_back((!_fastBlink ? cancelArg : 0) +  fastBlinkArg);
    if(_hide != arg._hide)
        args.push_back((!_hide ? cancelArg : 0) +  hideArg);
    if(_strike != arg._strike)
        args.push_back((!_strike ? cancelArg : 0) +  strikeArg);
    if(_reverse != arg._reverse)
        args.push_back((!_reverse ? cancelArg : 0) +  reverseArg);
    if(_doubleUnderline != arg._doubleUnderline && _doubleUnderline)
		args.push_back(doubleUnderlineArg + 0);
skip:
    std::string ret("\x1b[");
    bool first = true;
    for(int n : args){
        if(!first)
            ret += ";";
        char s[3] = {(char)((n / 10) + '0'), (char)((n % 10) + '0'), '\0'};
        if(s[0] != '0')
            ret += s;
        else
            ret += &s[1];
        first = false;
    }
    ret += "m";
    return ret;
}


void TTYAttr::clear(){
    bgColor = colDefault;
    fgColor = colDefault;
    _bold = false;
    _shallow = false;
    _italic = false;
    _underline = false;
    _doubleUnderline = false;
    _blink = false;
    _fastBlink = false;
    _reverse = false;
    _hide = false;
    _strike = false;
}


void TTYAttr::setArg(const std::vector<int>& args){
    for(auto i : args){
        switch(i){
        case 0:
            clear();
            break;
        case 1:
            _bold = true;
            break;
        case 2:
            _shallow = true;
            break;
        case 3:
            _italic = true;
            break;
        case 4:
            _underline = true;
            break;
        case 5:
            _blink = true;
            break;
        case 6:
            _fastBlink = true;
            break;
        case 7:
            _reverse = true;
            break;
        case 8:
            _hide = true;
            break;
        case 9:
            _strike = true;
            break;
        case 21:
            _doubleUnderline = true;
            break;
        case 22:
            _shallow = false;
            break;
        case 23:
            _italic = false;
            break;
        case 24:
            _underline = false;
            break;
        case 25:
            _blink = false;
            break;
        case 26:
            _fastBlink = false;
            break;
        case 27:
            _reverse = false;
            break;
        case 28:
            _hide = false;
            break;
        case 29:
            _strike = false;
            break;
        case 30:
            fgColor = colBlack;
            break;
        case 31:
            fgColor = colRed;
            break;
        case 32:
            fgColor = colGreen;
            break;
        case 33:
            fgColor = colYellow;
            break;
        case 34:
            fgColor = colBlue;
            break;
        case 35:
            fgColor = colPurple;
            break;
        case 36:
            fgColor = colCyan;
            break;
        case 37:
            fgColor = colWhite;
            break;
        case 39:
            fgColor = colDefault;
            break;
        case 40:
            bgColor = colBlack;
            break;
        case 41:
            bgColor = colRed;
            break;
        case 42:
            bgColor = colGreen;
            break;
        case 43:
            bgColor = colYellow;
            break;
        case 44:
            bgColor = colBlue;
            break;
        case 45:
            bgColor = colPurple;
            break;
        case 46:
            bgColor = colCyan;
            break;
        case 47:
            bgColor = colWhite;
            break;
        case 49:
            bgColor = colDefault;
            break;
        }
    }
}


TTYAttr::TTYAttr(const std::vector<int>&& args) : 
    fgColor(-1), bgColor(-1),
    _blink(false), _underline(false), _italic(false),
    _bold(false), _shallow(false), _fastBlink(false), 
    _hide(false), _strike(false), _reverse(false), _doubleUnderline(false)

{
    setArg(args);
}


TTYAttr::TTYAttr() : 
    fgColor(-1), bgColor(-1),
    _blink(false), _underline(false), _italic(false),
    _bold(false), _shallow(false), _fastBlink(false), 
    _hide(false), _strike(false), _reverse(false), _doubleUnderline(false)
{
}


TTYAttr::TTYAttr(int f, int b) : 
    fgColor(f), bgColor(b),
    _blink(false), _underline(false), _italic(false),
    _bold(false), _shallow(false), _fastBlink(false), 
    _hide(false), _strike(false), _reverse(false), _doubleUnderline(false)
{
}


TTYAttr::TTYAttr(int f, int b, bool __blink, bool __underline, bool __italic, bool __bold, bool __shallow, bool __fastBlink, bool __hide, bool __strike, bool __reverse, bool __doubleUnderline) : 
    fgColor(f), bgColor(b),
    _blink(__blink), _underline(__underline), _italic(__italic),
    _bold(__bold), _shallow(__shallow), _fastBlink(__fastBlink), 
    _hide(__hide), _strike(__strike), _reverse(__reverse)
{
}


TTYAttr::TTYAttr(const TTYAttr& arg) : 
    fgColor(arg.fgColor), bgColor(arg.bgColor),
    _blink(arg._blink), _underline(arg._underline), _italic(arg._italic),
    _bold(arg._bold), _shallow(arg._shallow), _fastBlink(arg._fastBlink), 
    _hide(arg._hide), _strike(arg._strike), _reverse(arg._reverse), _doubleUnderline(arg._doubleUnderline)
{
}


TTYAttr::TTYAttr(unsigned int arg) {
    size_t fc = arg & ((1 << 5) - 1);
    if(1 <= fc && fc <= i_fgDefault)
        fgColor = fc - 1;
    else
        fgColor = -1;
    size_t bc = (arg & ((1 << 5) - 1) << 5) >> 5;
    if(1 <= bc && bc <= i_fgDefault)
        bgColor = bc - 1;
    else
        bgColor = -1;
    _bold = (arg & i_bold) ? 1 : 0;
    _shallow = (arg & i_shallow) ? 1 : 0;
    _italic = (arg & i_italic) ? 1 : 0;
    _underline = (arg & i_underline) ? 1 : 0;
    _blink = (arg & i_blink) ? 1 : 0;
    _fastBlink = (arg & i_fastBlink) ? 1 : 0;
    _reverse = (arg & i_reverse) ? 1 : 0;
    _hide = (arg & i_hide) ? 1 : 0;
    _strike = (arg & i_strike) ? 1 : 0;
    _doubleUnderline = (arg & i_doubleUnderline) ? 1 : 0;
}


TTYAttr& TTYAttr::operator=(const TTYAttr& arg){
    fgColor = arg.fgColor; bgColor = arg.bgColor;
    _blink = arg._blink; _underline = arg._underline; _italic = arg._italic;
    _bold = arg._bold; _shallow = arg._shallow; _fastBlink = arg._fastBlink; 
    _hide = arg._hide; _strike = arg._strike; _reverse = arg._reverse;
	_doubleUnderline = arg._doubleUnderline;
    return *this;
}

const TTYAttr TTYAttr::fgBlack(colBlack, -1);
const TTYAttr TTYAttr::fgRed(colRed, -1);
const TTYAttr TTYAttr::fgGreen(colGreen, -1);
const TTYAttr TTYAttr::fgYellow(colYellow, -1);
const TTYAttr TTYAttr::fgBlue(colBlue, -1);
const TTYAttr TTYAttr::fgPurple(colPurple, -1);
const TTYAttr TTYAttr::fgCyan(colCyan, -1);
const TTYAttr TTYAttr::fgWhite(colWhite, -1);
const TTYAttr TTYAttr::fgDefault(colDefault, -1);
const TTYAttr TTYAttr::bgBlack(-1, colBlack);
const TTYAttr TTYAttr::bgRed(-1, colRed);
const TTYAttr TTYAttr::bgGreen(-1, colGreen);
const TTYAttr TTYAttr::bgYellow(-1, colYellow);
const TTYAttr TTYAttr::bgBlue(-1, colBlue);
const TTYAttr TTYAttr::bgPurple(-1, colPurple);
const TTYAttr TTYAttr::bgCyan(-1, colCyan);
const TTYAttr TTYAttr::bgWhite(-1, colWhite);
const TTYAttr TTYAttr::bgDefault(-1, colDefault);


const TTYAttr TTYAttr::blink(-1, -1, true, false, false, false, false, false, false, false, false, false);
const TTYAttr TTYAttr::underline(-1, -1, false, true, false, false, false, false, false, false, false, false);
const TTYAttr TTYAttr::italic(-1, -1, false, false, true, false, false, false, false, false, false, false);
const TTYAttr TTYAttr::bold(-1, -1, false, false, false, true, false, false, false, false, false, false);
const TTYAttr TTYAttr::shallow(-1, -1, false, false, false, false, true, false, false, false, false, false);
const TTYAttr TTYAttr::fastBlink(-1, -1, false, false, false, false, false, true, false, false, false, false);
const TTYAttr TTYAttr::hide(-1, -1, false, false, false, false, false, false, true, false, false, false);
const TTYAttr TTYAttr::strike(-1, -1, false, false, false, false, false, false, false, true, false, false);
const TTYAttr TTYAttr::reverse(-1, -1, false, false, false, false, false, false, false, false, true, false);
const TTYAttr TTYAttr::doubleUnderline(-1, -1, false, false, false, false, false, false, false, false, false, true);

bool TTYAttr::operator!=(const TTYAttr& arg)const{
    return fgColor != arg.fgColor || bgColor != arg.bgColor ||
        _blink != arg._blink || _underline != arg._underline || _italic != arg._italic ||
        _bold != arg._bold || _shallow != arg._shallow || _fastBlink != arg._fastBlink ||
        _hide != arg._hide || _strike != arg._strike || _reverse != arg._reverse ||
		_doubleUnderline != arg._doubleUnderline;
}


bool TTYAttr::operator==(const TTYAttr& arg)const{
    return fgColor == arg.fgColor && bgColor == arg.bgColor &&
        _blink == arg._blink && _underline == arg._underline && _italic == arg._italic &&
        _bold == arg._bold && _shallow == arg._shallow && _fastBlink == arg._fastBlink &&
        _hide == arg._hide && _strike == arg._strike && _reverse == arg._reverse &&
		_doubleUnderline == arg._doubleUnderline;
}


TTYAttr TTYAttr::operator|(const TTYAttr& arg)const{
    TTYAttr ret;
    if(fgColor == -1 && arg.fgColor != -1)
        ret.fgColor = arg.fgColor;
    else
        ret.fgColor = fgColor;
    if(bgColor == -1 && arg.bgColor != -1)
        ret.bgColor = arg.bgColor;
    else
        ret.bgColor = bgColor;
    ret._blink = _blink | arg._blink;
    ret._underline = _underline | arg._underline;
    ret._italic = _italic | arg._italic;
    ret._blink = _blink | arg._blink;
    ret._bold = _bold| arg._bold;
    ret._shallow = _shallow | arg._shallow;
    ret._fastBlink = _fastBlink | arg._fastBlink;
    ret._hide = _hide | arg._hide;
    ret._strike = _strike | arg._strike;
    ret._reverse = _reverse | arg._reverse;
    ret._doubleUnderline = _doubleUnderline | arg._doubleUnderline;
    return ret;
}


void TTYStr::push(std::string s, TTYAttr a, size_t cpos){
    size_t cursor = 0;
    while(s.size() > cursor){
        elems.emplace_back(Elem(nextCodePoint(s, &cursor), a, cpos));
	}
}


void TTYStr::put_utf8(std::string& s, char32_t codepoint){
    char c[] = {'\0', '\0', '\0', '\0', '\0'};
    if (codepoint <= 0x7f) {
        c[0] = (char) codepoint;
    }else if (codepoint <= 0x7ff) {
        c[0] = (char) (0xc0 | (codepoint >> 6));
        c[1] = (char) (0x80 | (codepoint & 0x3f));
    }else if (codepoint <= 0xffff) {
        c[0] = (char) (0xe0 | (codepoint >> 12));
        c[1] = (char) (0x80 | ((codepoint >> 6) & 0x3f));
        c[2] = (char) (0x80 | (codepoint & 0x3f));
    }
    else if (codepoint <= 0x1fffff) {
        c[0] = (char) (0xf0 | (codepoint >> 18));
        c[1] = (char) (0x80 | ((codepoint >> 12) & 0x3f));
        c[2] = (char) (0x80 | ((codepoint >> 6) & 0x3f));
        c[3] = (char) (0x80 | (codepoint & 0x3f));
    }else {
        // invalid codepoint
        put_utf8(s, 0xfffd);
        return;
    }
    s += (char*)c;
}


void TTYStr::flush(std::string* outString, size_t paddingNum, std::vector<size_t>* cpPosList){
    TTYAttr bAttr;
    std::string& out(*outString);
	std::string eseq;
	out.clear();
	cpPosList->clear();
	size_t curCPPos = -1;
    for(auto e : elems){
		curCPPos = e.cpPos;
        if(e.attr != bAttr){
            eseq = e.attr - bAttr;
			out += eseq;
			for(size_t i = 0 ; i < eseq.size() ; ++i) //eseq should be ascii coded
				cpPosList->push_back(curCPPos);
            put_utf8(out, e.cp);
			cpPosList->push_back(curCPPos);
            bAttr = e.attr;
        }else{
            put_utf8(out, e.cp);
			cpPosList->push_back(curCPPos);
        }
    }
    if(TTYAttr() != bAttr){
		eseq = TTYAttr(TTYAttr::colDefault, TTYAttr::colDefault) - bAttr;
        out += eseq;
		for(size_t i = 0 ; i < eseq.size() ; ++i) //eseq should be ascii coded
			cpPosList->push_back(curCPPos);
	}
    for(size_t i = 0 ; i < paddingNum ; ++i){
        out += " ";
		cpPosList->push_back(curCPPos);
	}
	clear();
}



std::basic_string<char32_t> UnicodeStr::to_U(std::string s){
    std::basic_string<char32_t> ret;
    size_t cursor = 0;
    while(s.size() > cursor)
        ret.push_back(nextCodePoint(s, &cursor));
    return std::move(ret);
}

bool UnicodeStr::hasRegexMatch(const std::basic_string<char32_t>& regexpr, boost::match_flag_type flg, bool isCompat)const{
    ToMatch* toMatch = getToMatch(isCompat);
    Regex regex(regexpr); // 正規表現
    boost::match_results<std::basic_string<char32_t>::iterator> what;
    size_t npos = 0;
    std::basic_string<char32_t>::iterator spos(toMatch->forRegexSearch.begin());
    return boost::regex_search(spos, toMatch->forRegexSearch.end(), what, regex, flg) != 0;
}

UnicodeStr::ToMatch* UnicodeStr::getToMatch(bool isCompat)const{
    ToMatch* toMatch = !isCompat ? &const_cast<UnicodeStr*>(this)->canon : &const_cast<UnicodeStr*>(this)->compat;
    int curPos = 0;
    if(toMatch->forRegexSearch.empty())
        for(auto it = cpList.begin() ; it != cpList.end() ; ++it, ++curPos){
            auto& normalized = !isCompat ? it->cannNormalized : it->compatNormalized;
            if(!normalized.empty()){
                bool first = true;
                for(auto& e : normalized){
                    toMatch->forRegexSearch.push_back(e.codePoint);
                    auto eIt = it + e.orgPos;
                    toMatch->forRegexSearchPosBegin.push_back((eIt - eIt->graphemeClusterIndex) - cpList.begin());
                    if(first){
                        toMatch->forRegexSearchPosEnd.push_back(toMatch->forRegexSearchPosBegin.back());
                        first = false;
                    }else
                        toMatch->forRegexSearchPosEnd.push_back(it + it->ccSeqLeft + 1 - cpList.begin());
                }
                it += it->ccSeqLeft;
            }else{
                toMatch->forRegexSearch.push_back(it->codePoint);
                toMatch->forRegexSearchPosBegin.push_back((it - it->graphemeClusterIndex) - cpList.begin());
                if(it->graphemeClusterIndex == 0)
                    toMatch->forRegexSearchPosEnd.push_back(it - cpList.begin());
                else
                    toMatch->forRegexSearchPosEnd.push_back((it + it->graphemeClusterLeft + 1) - cpList.begin());
            }
        }
    return toMatch;
}

bool UnicodeStr::regexMatch(const std::basic_string<char32_t>& regexpr, std::vector<MatchResult>* mrList, boost::match_flag_type flg, bool isCompat)const{
    ToMatch* toMatch = getToMatch(isCompat);
    Regex regex(regexpr); // 正規表現

    boost::match_results<std::basic_string<char32_t>::iterator> what;
    size_t npos = 0;
    std::basic_string<char32_t>::iterator spos(toMatch->forRegexSearch.begin());
    while(boost::regex_search(spos, toMatch->forRegexSearch.end(), what, regex, flg) != 0){
        size_t f = toMatch->forRegexSearchPosBegin[what[0].first - toMatch->forRegexSearch.begin()],
               s = toMatch->forRegexSearchPosEnd[what[0].second - toMatch->forRegexSearch.begin()];
        if(what[0].matched){
            MatchResult mr = { what[0].matched, f, s - f };
            mrList->emplace_back(mr);
            spos = what[0].second;
        }
    }
    return !mrList->empty();
}


void UnicodeStr::pushDecomped(char32_t codePoint, std::vector<NormCPElem>& list, size_t pos, bool isCompat){
    DecompData dd = getDecompData(codePoint);
    if(isCompat ? dd.mode != dmNone : dd.mode == dmCanonical){
        for(auto it = dd.data.begin(); it != dd.data.end(); ++it)
            list.push_back(NormCPElem{*it, pos});
    }else{
        list.push_back(NormCPElem{codePoint, pos});
    }
}


std::vector<UnicodeStr::NormCPElem> UnicodeStr::getDecomped(std::vector<CPElem>::iterator bg, std::vector<CPElem>::iterator ed, bool isCompat){
    std::vector<NormCPElem> ret;
    bool found = false;
    for(auto it = bg ; it != ed ; ++it){
        DecompData dd = getDecompData(bg->codePoint);
        if(isCompat ? dd.mode != dmNone : dd.mode == dmCanonical){
            found = true;
            break;
        }
    }
    if(found){
        size_t i = 0;
        for(auto it = bg ; it != ed ; ++it){
            pushDecomped(it->codePoint, ret, i, isCompat);
            ++i;
        }
    }
    return std::move(ret);
}


std::vector<UnicodeStr::NormCPElem> UnicodeStr::getNormalized(std::vector<CPElem>::iterator bg, std::vector<CPElem>::iterator ed, bool isCompat){
    std::vector<NormCPElem> ret = getDecomped(bg, ed, isCompat);
    bool reordered;
    std::vector<char32_t> cccList;
    if(ret.size() > 0){
        if(ret.size() < 2)
            return std::move(ret);
        for(auto it = ret.begin() ; it != ret.end() - 1 ; ++it)
            cccList.push_back(getCanonicalCombiningClass(it->codePoint));
        do{
            reordered = false;
            for(int i = 0 ; i < ret.size() - 1 ; ++i){
                char32_t bccc = cccList[i + 1];
                if(bccc > 0 && cccList[i] > bccc){
                    NormCPElem tmp;
                    tmp = ret[i + 1];
                    ret[i + 1] = ret[i];
                    ret[i] = tmp;
                    char32_t tmp_c;
                    tmp_c = cccList[i + 1];
                    cccList[i + 1] = cccList[i];
                    cccList[i] = tmp_c;
                    reordered = true;
                }
            }
        }while(reordered);
    }else{
        bool retPrepared = false;
        if(ed - bg < 2)
            return ret;
        for(auto it = bg ; it != ed - 1 ; ++it)
            cccList.push_back(getCanonicalCombiningClass(it->codePoint));
        do{
            reordered = false;
            for(int i = 0 ; i < ed - bg - 1 ; ++i){
                char32_t bccc = cccList[i + 1];
                if(bccc > 0 && cccList[i] > bccc){
                    if(!retPrepared){
                        size_t i = 0;
                        for(auto jt = bg ; jt != ed ; ++jt){
                            ret.push_back(NormCPElem{jt->codePoint, i});
                            ++i;
                        }
                        retPrepared = true;
                    }
                    NormCPElem tmp(ret[i + 1]);
                    ret[i + 1] = ret[i];
                    ret[i] = tmp;
                    char32_t tmp_c;
                    tmp_c = cccList[i + 1];
                    cccList[i + 1] = cccList[i];
                    cccList[i] = tmp_c;
                    reordered = true;
                }
            }
        }while(reordered);
    }
    return std::move(ret);
}


struct TmpParams{
    std::vector<UnicodeStr::CPElem>& cpList;
    bool lastIsExtPictExtend, lastIsFormatOrControl, prevCompatNormalizable, prevCannNormalizable, prevIsStartar, noLbpCheck;
    size_t graphemeLength, lineBreakLength, cpCount, ccSeqLength, prevCCC; 
    GraphemeBreakProperty lastGbp;
    LineBreakProperty lastLbp, lastLbpX, specialSP;
    TmpParams(UnicodeStr* u) : cpList(u->cpList), lastIsExtPictExtend(false), lastIsFormatOrControl(true),
        prevCompatNormalizable(false), prevCannNormalizable(false), prevIsStartar(true), noLbpCheck(false),
        graphemeLength(0), lineBreakLength(0), cpCount(0), ccSeqLength(0),
        lastGbp(gbNil), lastLbp(lbNil), lastLbpX(lbNil), specialSP(lbNil) {}
    void add(char32_t cp, size_t cp_pos, size_t start, size_t bsz, const TTYAttr& attr, std::string alt = "", size_t altTTYSize = 0){
        GraphemeBreakProperty gbp = getGraphemeBreakProperty(cp);
        LineBreakProperty lbp = getLineBreakProperty(cp);
        size_t ccc = getCanonicalCombiningClass(cp);
        bool isStarter = ccc == 0 || lastIsFormatOrControl/* initial : true */;

        if((cpList.size() == 0 || lastGbp != gbRegional_Indicator_First) && gbp == gbRegional_Indicator){
            gbp = gbRegional_Indicator_First;
            lbp = lbRI_first;
        }
        if(lbp == lbSP){
            if(specialSP == lbNil){
                switch(lastLbp){
                case lbOP_FWH:
                case lbOP_NonFWH:
                    specialSP = lbSPm_AFTER_OP;
                    break;
                case lbB2:
                    specialSP = lbSPm_AFTER_B2;
                    break;
                case lbQU:
                    specialSP = lbSPm_AFTER_QU;
                    break;
                case lbZW:
                    specialSP = lbSPm_AFTER_ZW;
                    break;
                case lbCL_NonFWH:
                case lbCL_FWH:
                case lbCP_NonFWH:
                    specialSP = lbSPm_AFTER_CLCP;
                    break;
                default:
                    noLbpCheck = false;
                    goto non_special_sp;
                }
            }
            noLbpCheck = true;
            lbp = specialSP;
    non_special_sp:
            ;
        }else{
            specialSP = lbNil;
            if(lbp == lbCM || lbp == lbZWJ){
                if(lastLbpX != lbNil){
                    lbp = lastLbpX;
                    noLbpCheck = true;
                }else{
                    lbp = lbAL;
                    noLbpCheck = false;
                }
            }else if(lastLbp == lbHL && (lbp == lbHY || lbp == lbBA)){
                noLbpCheck = true;
                lbp = lbHYBA_AFTER_HL;
            }else{
                noLbpCheck = false;
            }
        }
        if(cpList.size() > 0){
            if(lastIsExtPictExtend){
                if(gbp == gbZWJ){
                    gbp = gbZWJ_Extended_Pictographic;
                    lastIsExtPictExtend = false;
                }else if(gbp != gbExtend){
                    lastIsExtPictExtend = false;
                }
            }
            if(!lastIsExtPictExtend && graphemeBreakPropertyCompList[lastGbp][gbp]){
                cpList.back().isGraphemeBreakClusterEnd = true;
                std::vector<UnicodeStr::CPElem>::iterator st = cpList.end() - graphemeLength, it;
                size_t w = 0;
                for(it = st ; it != cpList.end() ; ++it){
                    it->graphemeClusterLeft = --graphemeLength;
                    w += it->ttyWidth;
                }
                for(it = st ; it != cpList.end() ; ++it){
                    w -= it->ttyWidth;
                    it->graphemeClusterTTyWidthLeft = w;
                }
            }

            if(!noLbpCheck && (cpList.back().lineBreakMode = lineBreakPropertyCompList[lastLbp][lbp]) != lbFalse){
                std::vector<UnicodeStr::CPElem>::iterator st = cpList.end() - lineBreakLength, it;
                size_t w = 0;
                for(it = st ; it != cpList.end() ; ++it){
                    it->lineBreakClusterLeft = --lineBreakLength;
                    w += it->ttyWidth;
                }
                for(it = st ; it != cpList.end() ; ++it){
                    w -= it->ttyWidth;
                    it->lineBreakClusterTTyWidthLeft = w;
                }
            }

            if(isStarter){
                std::vector<UnicodeStr::CPElem>::iterator st = cpList.end() - ccSeqLength, it;
                for(it = st ; it != cpList.end() ; ++it)
                    it->ccSeqLeft = --ccSeqLength;
                if(prevCannNormalizable){
                    st->cannNormalized = UnicodeStr::getNormalized(st, cpList.end(), false);
                    prevCannNormalizable = false;
                }
                if(prevCompatNormalizable){
                    st->compatNormalized = UnicodeStr::getNormalized(st, cpList.end(), true);
                    prevCompatNormalizable = false;
                }
            }
        }
        cpList.push_back(UnicodeStr::CPElem(cp, cp_pos, start, bsz, attr, alt, altTTYSize, graphemeLength));
        if((lastIsExtPictExtend && gbp == gbExtend) || gbp == gbExtended_Pictographic)
            lastIsExtPictExtend = true;
        else
            lastIsExtPictExtend = false;
        lastGbp = gbp;
        lastLbp = lbp;
        if(lbp != lbBK && lbp != lbCR && lbp != lbLF && lbp != lbNL && lbp != lbZW)
            lastLbpX = lbp;
        else
            lastLbpX = lbNil;
        auto gc = getGeneralCategoryProperty(cp);
        auto dd = getDecompData(cp);
        lastIsFormatOrControl = gc == gcCc || gc == gcCf || gc == gcCn || gc == gcCo || gc == gcCs;
        if(!prevCannNormalizable && (dd.mode == dmCanonical || (!isStarter && !prevIsStartar && prevCCC > ccc)))
            prevCannNormalizable = true;
        if(!prevCompatNormalizable && (dd.mode != dmNone || (!isStarter && !prevIsStartar && prevCCC > ccc)))
            prevCompatNormalizable = true;
        prevCCC = ccc;
        prevIsStartar = isStarter;
        ++graphemeLength;
        ++lineBreakLength;
        ++ccSeqLength;
    }
    void setLastParam(){
        std::vector<UnicodeStr::CPElem>::iterator it, st;
        st = cpList.end() - graphemeLength;
        size_t w = 0;
        for(it = st; it != cpList.end() ; ++it){
            it->graphemeClusterLeft = --graphemeLength;
            w += it->ttyWidth;
        }
        for(it = st; it != cpList.end() ; ++it){
            w -= it->ttyWidth;
            it->graphemeClusterTTyWidthLeft = w;
        }
        w = 0;
        st = cpList.end() - lineBreakLength;
        for(it = st; it != cpList.end() ; ++it){
            it->lineBreakClusterLeft = --lineBreakLength;
            w += it->ttyWidth;
        }
        for(it = st; it != cpList.end() ; ++it){
            w -= it->ttyWidth;
            it->lineBreakClusterTTyWidthLeft = w;
        }
        st = cpList.end() - ccSeqLength;
        for(it = st; it != cpList.end() ; ++it)
            it->ccSeqLeft = --ccSeqLength;
        if(prevCannNormalizable){
            st->cannNormalized = UnicodeStr::getNormalized(st, cpList.end(), false);
            prevCannNormalizable = false;
        }
        if(prevCompatNormalizable){
            st->compatNormalized = UnicodeStr::getNormalized(st, cpList.end(), true);
            prevCompatNormalizable = false;
        }
    }
};


UnicodeStr::UnicodeStr(std::string s) : 
    orgStr(s)
{
    TmpParams t(this);
    TTYAttr attr;
    size_t i = 0, ei;
    size_t prev_i;
	size_t cp_pos_next = 0;
    while(true){
        if(i >=  orgStr.size())
            break;
        prev_i = i;
        char32_t cp = nextCodePoint(orgStr, &i);
		++cp_pos_next;
        switch(cp){
        case 0x0a: //LF
        case 0x0d: //CR
        case 0x09: //TAB
        case 0x85: //NL
            goto else_label;
        case 0x1b: //ESC
            if(i >=  orgStr.size())
                goto control_label;
            ei = i;
            cp = nextCodePoint(orgStr, &i);
			++cp_pos_next;
            if(cp == '['){
                if(i >=  orgStr.size()){
                    i = ei;
                    cp = 0x1b;
                    goto control_label;
                }
                std::vector<int> nums;
                while(true){
                    int num = -1;
                    while(true){
                        cp = nextCodePoint(orgStr, &i);
						++cp_pos_next;
                        if(cp == ';'){
                            if(num != -1){
                                nums.push_back(num);
                                break;
                            }                                
                        }else if(('a' <= cp && cp <= 'z') || ('A' <= cp && cp <= 'Z')){
                            if(num == -1 && nums.size() == 0){
                                i = ei;
                                cp = 0x1b;
                                goto control_label;
                            }
                            if(cp == 'm' && num != -1){
								nums.push_back(num);
                                attr.setArg(nums);
							}
                            goto finish_esc;
                            break;
                        }else if(cp < '0' || '9' < cp){
                            i = ei;
                            cp = 0x1b;
                            goto control_label;
                        }else{
                            if(num == -1)
                                num = cp - '0';
                            else
                                num = num * 10 + cp - '0';
                        }
                        if(i >=  orgStr.size()){
                            i = ei;
                            cp = 0x1b;
                            goto control_label;
                        }
                    }
                }
            }else{
                i = ei;
                cp = 0x1b;
                goto control_label;
            }
finish_esc:
            break;
        default:
            if((0 <= cp && cp <= 0x1f) || (0x7f <= cp && cp <= 0x9f)){
control_label:
                char altStr[5];
                altStr[0] = '<';
                altStr[1] = '0' + (cp / 16);
                altStr[2] = '0' + (cp % 16);
                altStr[3] = '>';
                altStr[4] = '\0';
                TTYAttr a(attr);
                a._reverse = ~a._reverse;
                t.add(cp, cp_pos_next - 1, i, i - prev_i, a, altStr, 4);
            }else if(cp == 0xfffd){
                char altStr[8];
                altStr[0] = '<';
                altStr[1] = 'E';
                altStr[2] = 'R';
                altStr[3] = 'R';
                altStr[4] = 'O';
                altStr[5] = 'R';
                altStr[6] = '>';
                altStr[7] = '\0';
                TTYAttr a(attr);
                a._reverse = ~a._reverse;
                t.add(cp, cp_pos_next - 1, i, i - prev_i, a, altStr, 7);
            }else{
else_label:
                t.add(cp, cp_pos_next - 1, i, i - prev_i, attr);
            }
        }
    }
    t.setLastParam();
    //createNormalized();
}

/*
size_t UnicodeStr::lineCount(size_t width, size_t tabSize)const{// f(const std::vector<terminal_str>& s)
		if(width == 0 || tabSize == 0)
				throw UnicodeStr::Error("width = 0 or tab size = 0");
		size_t curPos = 0, lc = 0;
		bool isEmpty = true;
		auto it = cpList.begin();
		while(it != cpList.end()){
				bool useGraphBreak = false; //line break or grapheme break
		retry:
				size_t posMaybe = curPos;
				auto org = it;
				while(true){
						if(it->codePoint == U'\t'){
								posMaybe = ((posMaybe + 1) / tabSize + 1) * tabSize;
						}else if(it->altTTYSize == 0){
								posMaybe += it->ttyWidth;
						}else{
								posMaybe += it->altTTYSize;
						}
						if(it->clusterLeft(useGraphBreak) == 0)
								break;
						++it;
				}
				++it;
				if(posMaybe > width){
						if(!isEmpty){
								++lc;
								curPos = 0;
								isEmpty = true;
								it = org;
								continue;
						}else{
								if(!useGraphBreak){
										useGraphBreak = true;
										it = org;
										goto retry;
								}else{
										++lc;
										curPos = 0;
										isEmpty = true;
										continue;
								}
						}
				}else{
						auto jt = org;
						posMaybe = curPos;
						while(jt != it){
								size_t pos = jt - cpList.begin();
								if(jt->codePoint == U'\t'){
										size_t prevPosMaybe = posMaybe;
										posMaybe = ((posMaybe + 1) / tabSize + 1) * tabSize;
								}else if(jt->codePoint == U'\r' || jt->codePoint == U'\n' || jt->codePoint == U'\x85'){
										;
								}else{
										if(jt->altTTYSize == 0)
												posMaybe += jt->ttyWidth;
										else
												posMaybe += jt->altTTYSize;
								}
								++jt;
						}
						if(it != cpList.begin() && (it - 1)->lineBreakMode == lbForce){
								++lc;
								curPos = 0;
								isEmpty = true;
								continue;
						}else{
								isEmpty = false;
								curPos = posMaybe;
						}
				}
		}
		if(!isEmpty)
				++lc;
		return lc;
}
*/

}
}
