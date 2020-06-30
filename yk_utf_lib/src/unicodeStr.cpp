#include "../include/unicodeStr.hpp"
#include "../include/canonicalCombiningClass.hpp"
#include "../include/decompData.hpp"
#include "../include/lineBreakProperty.hpp"
#include "../include/generalCategoryProperty.hpp"

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
    if(fgColor != arg.fgColor && fgColor != -1)
        args.push_back(fgColorArg + fgColor);
    if(bgColor != arg.bgColor && bgColor != -1)
        args.push_back(bgColorArg + bgColor);
    if(blink != arg.blink)
        args.push_back((!blink ? cancelArg : 0) +  blinkArg);
    if(underline != arg.underline)
        args.push_back((!underline ? cancelArg : 0) +  underlineArg);
    if(italic != arg.italic)
        args.push_back((!italic ? cancelArg : 0) +  italicArg);
    if(bold != arg.bold)
        args.push_back((!bold ? cancelArg : 0) +  boldArg);
    if(shallow != arg.shallow)
        args.push_back((!shallow ? cancelArg : 0) +  shallowArg);
    if(fastBlink != arg.fastBlink)
        args.push_back((!fastBlink ? cancelArg : 0) +  fastBlinkArg);
    if(hide != arg.hide)
        args.push_back((!hide ? cancelArg : 0) +  hideArg);
    if(strike != arg.strike)
        args.push_back((!strike ? cancelArg : 0) +  strikeArg);
    if(reverse != arg.reverse)
        args.push_back((!reverse ? cancelArg : 0) +  reverseArg);
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
    bold = false;
    shallow = false;
    italic = false;
    underline = false;
    blink = false;
    fastBlink = false;
    reverse = false;
    hide = false;
    strike = false;
}


void TTYAttr::setArg(const std::vector<int>& args){
    for(auto i : args){
        switch(i){
        case 0:
            clear();
            break;
        case 1:
            bold = true;
            break;
        case 2:
            shallow = true;
            break;
        case 3:
            italic = true;
            break;
        case 4:
            underline = true;
            break;
        case 5:
            blink = true;
            break;
        case 6:
            fastBlink = true;
            break;
        case 7:
            reverse = true;
            break;
        case 8:
            hide = true;
            break;
        case 9:
            strike = true;
            break;
        case 21:
            bold = false;
            break;
        case 22:
            shallow = false;
            break;
        case 23:
            italic = false;
            break;
        case 24:
            underline = false;
            break;
        case 25:
            blink = false;
            break;
        case 26:
            fastBlink = false;
            break;
        case 27:
            reverse = false;
            break;
        case 28:
            hide = false;
            break;
        case 29:
            strike = false;
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
    blink(false), underline(false), italic(false),
    bold(false), shallow(false), fastBlink(false), 
    hide(false), strike(false), reverse(false)

{
    setArg(args);
}


TTYAttr::TTYAttr() : 
    fgColor(-1), bgColor(-1),
    blink(false), underline(false), italic(false),
    bold(false), shallow(false), fastBlink(false), 
    hide(false), strike(false), reverse(false)
{
}


TTYAttr::TTYAttr(int f, int b) : 
    fgColor(f), bgColor(b),
    blink(false), underline(false), italic(false),
    bold(false), shallow(false), fastBlink(false), 
    hide(false), strike(false), reverse(false)
{
}


TTYAttr::TTYAttr(const TTYAttr& arg) : 
    fgColor(arg.fgColor), bgColor(arg.bgColor),
    blink(arg.blink), underline(arg.underline), italic(arg.italic),
    bold(arg.bold), shallow(arg.shallow), fastBlink(arg.fastBlink), 
    hide(arg.hide), strike(arg.strike), reverse(arg.reverse)
{
}


TTYAttr& TTYAttr::operator=(const TTYAttr& arg){
    fgColor = arg.fgColor; bgColor = arg.bgColor;
    blink = arg.blink; underline = arg.underline; italic = arg.italic;
    bold = arg.bold; shallow = arg.shallow; fastBlink = arg.fastBlink; 
    hide = arg.hide; strike = arg.strike; reverse = arg.reverse;
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

bool TTYAttr::operator!=(const TTYAttr& arg)const{
    return fgColor != arg.fgColor || bgColor != arg.bgColor ||
        blink != arg.blink || underline != arg.underline || italic != arg.italic ||
        bold != arg.bold || shallow != arg.shallow || fastBlink != arg.fastBlink ||
        hide != arg.hide || strike != arg.strike || reverse != arg.reverse;
}


bool TTYAttr::operator==(const TTYAttr& arg)const{
    return fgColor == arg.fgColor && bgColor == arg.bgColor &&
        blink == arg.blink && underline == arg.underline && italic == arg.italic &&
        bold == arg.bold && shallow == arg.shallow && fastBlink == arg.fastBlink &&
        hide == arg.hide && strike == arg.strike && reverse == arg.reverse;
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
    ret.blink = blink | arg.blink;
    ret.underline = underline | arg.underline;
    ret.italic = italic | arg.italic;
    ret.blink = blink | arg.blink;
    ret.bold = bold| arg.bold;
    ret.shallow = shallow | arg.shallow;
    ret.fastBlink = fastBlink | arg.fastBlink;
    ret.hide = hide | arg.hide;
    ret.strike = strike | arg.strike;
    ret.reverse = reverse | arg.reverse;
    return ret;
}


void TTYStr::push(std::string s, TTYAttr a){
    size_t cursor = 0;
    while(s.size() > cursor)
        elems.emplace_back(Elem(nextCodePoint(s, &cursor), a));
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


std::string TTYStr::getStdStr(size_t paddingNum){
    TTYAttr bAttr;
    std::string out;
    for(auto e : elems){
        if(e.attr != bAttr){
            out += e.attr - bAttr;
            put_utf8(out, e.cp);
            bAttr = e.attr;
        }else{
            put_utf8(out, e.cp);
        }
    }
    if(TTYAttr() != bAttr)
        out += TTYAttr() - bAttr;
    for(size_t i = 0 ; i < paddingNum ; ++i)
        out += " ";
    return out;
}


bool UnicodeStr::regexMatch(const std::basic_string<char32_t>& regexpr, std::vector<MatchResult>* mrList, boost::match_flag_type flg, bool isCompat)const{
    auto* toMatch = !isCompat ? &const_cast<UnicodeStr*>(this)->canon : &const_cast<UnicodeStr*>(this)->compat;
    int curPos = 0;
    if(toMatch->forRegexSearch.empty())
        for(auto it = cpList.begin() ; it != cpList.end() ; ++it, ++curPos){
            auto& normalized = !isCompat ? it->cannNormalized : it->compatNormalized;
            if(!normalized.empty()){
                for(auto& e : normalized){
                    toMatch->forRegexSearch.push_back(e.codePoint);
                    toMatch->forRegexSearchPos.push_back(curPos + e.orgPos);
                }
                it += it->ccSeqLeft;
            }else{
                toMatch->forRegexSearch.push_back(it->codePoint);
                toMatch->forRegexSearchPos.push_back(curPos);
            }
        }
    Regex regex(regexpr); // 正規表現

    boost::match_results<std::basic_string<char32_t>::iterator> what;
    size_t npos = 0;
    std::basic_string<char32_t>::iterator spos(toMatch->forRegexSearch.begin());
    while(boost::regex_search(spos, toMatch->forRegexSearch.end(), what, regex, flg) != 0){
        size_t f = toMatch->forRegexSearchPos[what[0].first - toMatch->forRegexSearch.begin()],
               s = toMatch->forRegexSearchPos[what[0].second - toMatch->forRegexSearch.begin()];
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
    void add(char32_t cp, size_t start, size_t bsz, const TTYAttr& attr, std::string alt = "", size_t altTTYSize = 0){
    std::cout << ccSeqLength << std::endl;
        GraphemeBreakProperty gbp = getGraphemeBreakProperty(cp);
    std::cout << __LINE__ << std::endl;
        LineBreakProperty lbp = getLineBreakProperty(cp);
    std::cout << __LINE__ << std::endl;
        size_t ccc = getCanonicalCombiningClass(cp);
    std::cout << __LINE__ << std::endl;
        bool isStarter = ccc == 0 || lastIsFormatOrControl/* initial : true */;

        if((cpList.size() == 0 || lastGbp != gbRegional_Indicator_First) && gbp == gbRegional_Indicator){
            gbp = gbRegional_Indicator_First;
            lbp = lbRI_first;
        }
    std::cout << __LINE__ << std::endl;
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
        cpList.push_back(UnicodeStr::CPElem(cp, start, bsz, attr, alt, altTTYSize));
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
        for(st = it; it != cpList.end() ; ++it){
            it->lineBreakClusterLeft = --lineBreakLength;
            w += it->ttyWidth;
        }
        for(st = it; it != cpList.end() ; ++it){
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
    std::cout << __LINE__ << std::endl;
    TmpParams t(this);
    std::cout << __LINE__ << std::endl;
    TTYAttr attr;
    std::cout << __LINE__ << std::endl;
    size_t i = 0, ei;
    size_t prev_i;
    while(true){
        if(i >=  orgStr.size())
            break;
        prev_i = i;
    std::cout << __LINE__ << std::endl;
        char32_t cp = nextCodePoint(orgStr, &i);
    std::cout << __LINE__ << std::endl;
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
    std::cout << __LINE__ << std::endl;
            cp = nextCodePoint(orgStr, &i);
    std::cout << __LINE__ << std::endl;
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
                            if(cp == 'm')
                                attr.setArg(nums);
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
                a.reverse = ~a.reverse;
                t.add(cp, i, i - prev_i, a, altStr, 4);
            }else{
else_label:
    std::cout << __LINE__ << std::endl;
                t.add(cp, i, i - prev_i, attr);
            }
        }
    }
    t.setLastParam();
    //createNormalized();
}

void UnicodeStr::CPElem::utf8_push_tty2(TTYStr& ts, TTYAttr eAttr){
    std::cout << __LINE__ << std::endl << std::flush;
}


}
}
