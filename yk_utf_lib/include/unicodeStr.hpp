#ifndef __YK_UNICODE_STR_HPP__
#define __YK_UNICODE_STR_HPP__

#include "graphemeProperty.hpp"
#include "regex_utf.hpp"
#include "ttyWidth.hpp"

namespace Yk{
namespace UTF{
//デフォルトの見直し。

struct TTYAttr{
    int fgColor, bgColor;
    static constexpr int fgColorArg = 30;
    static constexpr int bgColorArg = 40;
    static constexpr int cancelArg = 20;
    static constexpr int blinkArg = 5;
    static constexpr int underlineArg = 4;
    static constexpr int italicArg = 3;
    static constexpr int boldArg = 1;
    static constexpr int shallowArg = 2;
    static constexpr int fastBlinkArg = 6;
    static constexpr int hideArg = 8;
    static constexpr int strikeArg = 9;
    static constexpr int reverseArg = 7;
    static constexpr int colBlack = 0;
    static constexpr int colRed = 1;
    static constexpr int colGreen = 2;
    static constexpr int colYellow = 3;
    static constexpr int colBlue = 4;
    static constexpr int colPurple = 5;
    static constexpr int colCyan= 6;
    static constexpr int colWhite= 7;
    static constexpr int colDefault = 9;
    bool bold : 1;//1
    bool shallow : 1;//2
    bool italic : 1;//3
    bool underline : 1;//4
    bool blink : 1;//5
    bool fastBlink : 1; //6
    bool reverse : 1;//7
    bool hide : 1;//8
    bool strike : 1;//9
    std::string operator-(const TTYAttr& arg)const;
    void clear();
    void setArg(const std::vector<int>& args);
    TTYAttr(const std::vector<int>&& args);
    TTYAttr();
    TTYAttr(int, int);
    TTYAttr(const TTYAttr& arg);
    TTYAttr& operator=(const TTYAttr& arg);
    bool operator!=(const TTYAttr& arg)const;
    bool operator==(const TTYAttr& arg)const;
    TTYAttr operator|(const TTYAttr& arg)const;
    static const TTYAttr fgBlack;
    static const TTYAttr fgRed;
    static const TTYAttr fgGreen;
    static const TTYAttr fgYellow;
    static const TTYAttr fgBlue;
    static const TTYAttr fgPurple;
    static const TTYAttr fgCyan;
    static const TTYAttr fgWhite;
    static const TTYAttr fgDefault;
    static const TTYAttr bgBlack;
    static const TTYAttr bgRed;
    static const TTYAttr bgGreen;
    static const TTYAttr bgYellow;
    static const TTYAttr bgBlue;
    static const TTYAttr bgPurple;
    static const TTYAttr bgCyan;
    static const TTYAttr bgWhite;
    static const TTYAttr bgDefault;
};

struct TTYStr{
    struct Elem{
        char32_t cp;
        TTYAttr attr;
        Elem(char32_t c, TTYAttr a) : cp(c), attr(a) {}
    };
    std::vector<Elem>elems;
    void push(char32_t cp, TTYAttr a){
        elems.emplace_back(Elem(cp, a));
    }
    void push(std::string s, TTYAttr a);
    static void put_utf8(std::string& s, char32_t codepoint);
    std::string getStdStr(size_t paddingNum = 0);
    bool empty(){
        return elems.empty();
    }
    void clear(){
        elems.clear();
    }
};

struct UnicodeStr{
    static TTYAttr matchColor;
    std::string orgStr;//UTF-8
    typedef std::basic_string<char32_t> string_type;
    template <class F>
    void eachLineWithMatch(size_t width, size_t tabSize, string_type regex, TTYAttr matchColor, F f); // f(const std::vector<terminal_str>& s)
    template <class F>
    void eachLine(size_t width, size_t tabSize, F f){
        eachLineWithMatch(width, tabSize, U"", matchColor, f);
    };// f(const std::vector<terminal_str>& s)
    struct NormCPElem{
        char32_t codePoint;
        size_t orgPos;
    };
    struct CPElem{
        char32_t codePoint;
        size_t bytePos, byteSize;
        TTYAttr attr;
        std::string alt;
        size_t altTTYSize, ttyWidth;
        size_t ccSeqLeft, graphemeClusterLeft, graphemeClusterTTyWidthLeft, lineBreakClusterLeft, lineBreakClusterTTyWidthLeft;
        bool isGraphemeBreakClusterEnd;
        LBMode lineBreakMode;
        std::vector<NormCPElem> cannNormalized, compatNormalized;
        void utf8_push_tty(TTYStr& ts, TTYAttr eAttr = TTYAttr())const{
            std::cout << __LINE__ << std::endl << std::flush;
            if(altTTYSize > 0)
                ts.push(alt, attr|eAttr);
            else
                ts.push(codePoint, attr|eAttr);
            std::cout << __LINE__ << std::endl << std::flush;
        }
        CPElem(char32_t cp, size_t start, size_t bsz, TTYAttr a, std::string as, size_t asz) :
            codePoint(cp), bytePos(start), byteSize(bsz), attr(a), alt(as), altTTYSize(asz), ttyWidth(getTTYWidth(cp)),
            ccSeqLeft(0), graphemeClusterLeft(0), graphemeClusterTTyWidthLeft(0), lineBreakClusterLeft(0), lineBreakClusterTTyWidthLeft(0),
            isGraphemeBreakClusterEnd(false), lineBreakMode(lbFalse)
        { }
        CPElem(const CPElem& arg) = default;/* : 
            codePoint(arg.codePoint), bytePos(arg.bytePos), byteSize(arg.byteSize), attr(arg.attr), alt(arg.alt), altTTYSize(arg.altTTYSize), ttyWidth(arg.ttyWidth)
        { }*/
        CPElem() = delete;
    };
    std::vector<CPElem> cpList;
    struct {
        std::basic_string<char32_t> forRegexSearch;
        std::vector<size_t> forRegexSearchPos;
    } canon, compat;
    struct MatchResult{
        bool matched;
        size_t pos, length;
        size_t start(){ return pos; }
        size_t end(){ return pos + length; }
    };
    bool regexMatch(const std::basic_string<char32_t>& regexpr, std::vector<MatchResult>* mrList, boost::match_flag_type flg = boost::match_default, bool isCompat = false)const;
    static void pushDecomped(char32_t codePoint, std::vector<NormCPElem>& list, size_t pos, bool isCompat);
    static std::vector<NormCPElem> getDecomped(std::vector<CPElem>::iterator bg, std::vector<CPElem>::iterator ed, bool isCompat);
    static std::vector<NormCPElem> getNormalized(std::vector<CPElem>::iterator bg, std::vector<CPElem>::iterator ed, bool isCompat);
    UnicodeStr(std::string s);
};


template <class F>
void UnicodeStr::eachLineWithMatch(size_t width, size_t tabSize, string_type regex, TTYAttr matchColor, F f){// f(const std::vector<terminal_str>& s)
    if(width == 0 || tabSize == 0)
        throw UnicodeStr::Error("width = 0 or tab size = 0");
    using namespace Yk::UTF;
    TTYStr out;
    size_t curPos = 0;
    auto it = cpList.begin();
    std::vector<MatchResult> matchList;
    if(!regex.empty())
        regexMatch(regex, &matchList);
    std::vector<MatchResult>::iterator curMatch = matchList.begin();
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
        std::cout << "posMaybe = " << posMaybe << std::endl;
        if(posMaybe >= width){
retry:
            if(!out.empty()){
                f(out.getStdStr(width - curPos));
                out.clear();
                curPos = 0;
                it = org;
                continue;
            }else{
                if(!useGraphBreak){
                    useGraphBreak = true;
                    it = org;
                    goto retry;
                }else{
                    out.setStdStr(".", TTYAttr::reverse)
                    f(out.getStdStr(width - curPos));
                    out.clear();
                    curPos = 0;
                    it = org;
                    continue;
                }
            }
        }else{
            auto jt = org;
            posMaybe = curPos;
            while(jt != it){
                size_t pos = jt - cpList.begin();
                TTYAttr tattr = (curMatch != matchList.end() && curMatch->start() <= pos && pos < curMatch->end()) ? matchColor : TTYAttr();
                if(jt->codePoint == U'\t'){
                    size_t prevPosMaybe = posMaybe;
                    posMaybe = ((posMaybe + 1) / tabSize + 1) * tabSize;
                    for(size_t i = prevPosMaybe ; i < posMaybe ;　++i)
                        out.push(" ", tattr); //consider altTTY
                }else if(jt->codePoint == U'\r' || jt->codePoint == U'\n'){
                    ;
                }else{
                    jt->utf8_push_tty(out, tattr);
                    if(jt->altTTYSize == 0)
                        posMaybe += jt->ttyWidth;
                    else
                        posMaybe += jt->altTTYSize;
                }
                if(curMatch != matchList.end())
                    while(curMatch->end() + 1 <= pos)
                        ++curMatch;
                ++jt;
            }
            if(it != cpList.begin() && (it - 1)->lineBreakMode == lbForce){
                f(out.getStdStr(width - curPos)); // remove CR and LF, so empty string is allowed
                out.clear();
                curPos = 0;
                it = org;
                continue;
            }else
                curPos = posMaybe;
        }
    }
    if(!out.empty())
        f(out.getStdStr(width - curPos));    
}

} 
}

#endif