#ifndef __YK_UNICODE_STR_HPP__
#define __YK_UNICODE_STR_HPP__

#include "graphemeProperty.hpp"
#include "regex_utf.hpp"
#include "ttyWidth.hpp"
#include "lineBreakProperty.hpp"

namespace Yk{
namespace UTF{
//デフォルトの見直し。

struct TTYAttr{
		int fgColor, bgColor;
		static constexpr int fgColorArg = 30;
		static constexpr int bgColorArg = 40;
		static constexpr int cancelArg = 20;
		static constexpr int doubleUnderlineArg = 20;
		static constexpr int blinkArg = 5;
		static constexpr int boldArg = 1;
		static constexpr int underlineArg = 4;
		static constexpr int italicArg = 3;
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
		bool _bold : 1;//1
		bool _shallow : 1;//2
		bool _italic : 1;//3
		bool _underline : 1;//4
		bool _blink : 1;//5
		bool _fastBlink : 1; //6
		bool _reverse : 1;//7
		bool _hide : 1;//8
		bool _strike : 1;//9
		bool _doubleUnderline : 1;//9
		std::string operator-(const TTYAttr& arg)const;
		std::string operator-()const;
		void clear();
		void setArg(const std::vector<int>& args);
		TTYAttr(const std::vector<int>&& args);
		TTYAttr();
		TTYAttr(int, int);
		TTYAttr(int, int, bool, bool, bool, bool, bool, bool, bool, bool, bool, bool);
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
		static const TTYAttr bold;
		static const TTYAttr shallow;
		static const TTYAttr italic;
		static const TTYAttr underline;
		static const TTYAttr blink;
		static const TTYAttr fastBlink;
		static const TTYAttr reverse;
		static const TTYAttr hide;
		static const TTYAttr strike;
		static const TTYAttr doubleUnderline;
		static constexpr unsigned int i_fgBlack = 1;
		static constexpr unsigned int i_fgRed = 2;
		static constexpr unsigned int i_fgGreen = 3;
		static constexpr unsigned int i_fgYellow = 4;
		static constexpr unsigned int i_fgBlue = 5;
		static constexpr unsigned int i_fgPurple = 6;
		static constexpr unsigned int i_fgCyan = 7;
		static constexpr unsigned int i_fgWhite = 8;
		static constexpr unsigned int i_fgDefault = 9;
		static constexpr unsigned int i_bgBlack = 1 << 5;
		static constexpr unsigned int i_bgRed = 2 << 5;
		static constexpr unsigned int i_bgGreen = 3 << 5;
		static constexpr unsigned int i_bgYellow = 4 << 5;
		static constexpr unsigned int i_bgBlue = 5 << 5;
		static constexpr unsigned int i_bgPurple = 6 << 5;
		static constexpr unsigned int i_bgCyan = 7 << 5;
		static constexpr unsigned int i_bgWhite = 8 << 5;
		static constexpr unsigned int i_bgDefault = 9 << 5;
		static constexpr unsigned int i_bold = 1 << 10;
		static constexpr unsigned int i_shallow = 1 << 11;
		static constexpr unsigned int i_italic = 1 << 12;
		static constexpr unsigned int i_underline = 1 << 13;
		static constexpr unsigned int i_blink = 1 << 14;
		static constexpr unsigned int i_fastBlink = 1 << 15;
		static constexpr unsigned int i_reverse = 1 << 16;
		static constexpr unsigned int i_hide = 1 << 17;
		static constexpr unsigned int i_strike = 1 << 18;
		static constexpr unsigned int i_doubleUnderline = 1 << 19;
		TTYAttr(unsigned int arg);
};

struct TTYStr{
		struct Elem{
			char32_t cp;
			size_t cpPos;
			TTYAttr attr;
			Elem(char32_t c, TTYAttr a, size_t cpos) : cp(c), attr(a), cpPos(cpos) {}
		};
		TTYStr() : notEmpty(false){ }
		std::vector<Elem> elems;
		bool notEmpty;
		void push(char32_t cp, TTYAttr a, size_t cpos){
			elems.emplace_back(Elem(cp, a, cpos));
		}
		void pushEmpty(){
			notEmpty = true;
		}
		void push(std::string s, TTYAttr a, size_t cpos);
		static void put_utf8(std::string& s, char32_t codepoint);
		void flush(std::string* outString, size_t paddingNum, std::vector<size_t>* cpPosList);
		bool empty()const{
			return elems.empty() && !notEmpty;
		}
		void clear(){
			notEmpty = false;
			elems.clear();
		}
		static std::string utf8(char32_t codepoint){
			std::string s;
			put_utf8(s, codepoint);
			return s;
		}
};



struct UnicodeStr{
	static std::basic_string<char32_t> to_U(std::string s);
	struct Error{
			std::string msg;
			Error(std::string err) : msg(err){ }
	};
	static TTYAttr matchColor;
	std::string orgStr;//UTF-8
	typedef std::basic_string<char32_t> string_type;
	template <class F>
	void eachLineWithMatch(size_t width, size_t tabSize, std::string regex, TTYAttr matchColor, F f)const; // f(const std::vector<terminal_str>& s)
	template <class F>
	void eachLine(size_t width, size_t tabSize, F f)const{
			eachLineWithMatch(width, tabSize, U"", matchColor, f);
	};// f(const std::vector<terminal_str>& s)
//	size_t lineCount(size_t width, size_t tabSize)const;
	struct NormCPElem{
			char32_t codePoint;
			size_t orgPos;
	};
	struct CPElem{
			char32_t codePoint;
			size_t codePointPos, bytePos, byteSize;
			TTYAttr attr;
			std::string alt;
			size_t altTTYSize, ttyWidth;
			size_t ccSeqLeft, graphemeClusterLeft, graphemeClusterIndex, graphemeClusterTTyWidthLeft, lineBreakClusterLeft, lineBreakClusterTTyWidthLeft;
			bool isGraphemeBreakClusterEnd;
			LBMode lineBreakMode;
			std::vector<NormCPElem> cannNormalized, compatNormalized;
			void utf8_push_tty(TTYStr& ts, TTYAttr eAttr = TTYAttr())const{
					if(altTTYSize > 0)
							ts.push(alt, attr|eAttr, codePointPos);
					else
							ts.push(codePoint, attr|eAttr, codePointPos);
			}
			CPElem(char32_t cp, size_t cp_pos, size_t start, size_t bsz, TTYAttr a, std::string as, size_t asz, size_t gi) :
					codePoint(cp), codePointPos(cp_pos), bytePos(start), byteSize(bsz), attr(a), alt(as), altTTYSize(asz), ttyWidth(getTTYWidth(cp)),
					ccSeqLeft(0), graphemeClusterLeft(0), graphemeClusterIndex(gi), graphemeClusterTTyWidthLeft(0), lineBreakClusterLeft(0), lineBreakClusterTTyWidthLeft(0),
					isGraphemeBreakClusterEnd(false), lineBreakMode(lbFalse)
			{ }
			CPElem(const CPElem& arg) = default;/* : 
					codePoint(arg.codePoint), bytePos(arg.bytePos), byteSize(arg.byteSize), attr(arg.attr), alt(arg.alt), altTTYSize(arg.altTTYSize), ttyWidth(arg.ttyWidth)
			{ }*/
			CPElem() = delete;
			size_t clusterLeft(bool useGrapheme)const{
					if(useGrapheme)
							return graphemeClusterLeft;
					else
							return lineBreakClusterLeft;
			}
	};
	std::vector<CPElem> cpList;
	struct ToMatch{
			std::basic_string<char32_t> forRegexSearch;
			std::vector<size_t> forRegexSearchPosBegin;
			std::vector<size_t> forRegexSearchPosEnd;
	} canon, compat;
	struct MatchResult{
			bool matched;
			size_t pos, length;
			size_t start(){ return pos; }
			size_t end(){ return pos + length; }
	};
	bool regexMatch(const std::basic_string<char32_t>& regexpr, std::vector<MatchResult>* mrList, boost::match_flag_type flg = boost::match_default, bool isCompat = false)const;
	bool hasRegexMatch(const std::basic_string<char32_t>& regexpr, boost::match_flag_type flg = boost::match_default, bool isCompat = false)const;
	ToMatch* getToMatch(bool isCompat = false)const;
	static void pushDecomped(char32_t codePoint, std::vector<NormCPElem>& list, size_t pos, bool isCompat);
	static std::vector<NormCPElem> getDecomped(std::vector<CPElem>::iterator bg, std::vector<CPElem>::iterator ed, bool isCompat);
	static std::vector<NormCPElem> getNormalized(std::vector<CPElem>::iterator bg, std::vector<CPElem>::iterator ed, bool isCompat);
	UnicodeStr(std::string s);
	UnicodeStr(){}
	std::basic_string<char32_t> getCanUTF32()const{
			std::basic_string<char32_t> ret;
			auto it = cpList.begin();
			while(it != cpList.end()){
					if(!it->cannNormalized.empty()){
							for(auto e : it->cannNormalized)
									ret.push_back(e.codePoint);
							it += it->ccSeqLeft;
							++it;
							continue;
					}else
							ret.push_back(it->codePoint);
					++it;
			}
			return std::move(ret);
	}
};


template <class F>
void UnicodeStr::eachLineWithMatch(size_t width, size_t tabSize, std::string regex_s, TTYAttr matchColor, F f)const{// f(const std::vector<terminal_str>& s)
	UnicodeStr regex(regex_s);
	if(width == 0 || tabSize == 0)
		throw UnicodeStr::Error("width = 0 or tab size = 0");
	using namespace Yk::UTF;
	TTYStr out;
	size_t curPos = 0;
	auto it = cpList.begin();
	auto prevIt = it;
	std::string outString;
	std::vector<size_t> outTTYPosList;
	std::vector<MatchResult> matchList;
	if(!regex_s.empty()){
		regexMatch(regex.getCanUTF32(), &matchList);
	}
	std::vector<MatchResult>::iterator curMatch = matchList.begin();
	while(it != cpList.end()){
		bool useGraphBreak = false; //line break or grapheme break
retry:
		size_t posMaybe = curPos, prevPosMaybe = curPos;
		auto org = it;
		while(true){
			if(it->codePoint == U'\t'){
				posMaybe = ((posMaybe + 1) / tabSize + 1) * tabSize;
			}else if(it->altTTYSize == 0){
				posMaybe += it->ttyWidth;
			}else{
				posMaybe += it->altTTYSize;
			}
			if(!useGraphBreak){
				if(it->clusterLeft(false) == 0)
					break;
			}else if(it->clusterLeft(true) == 0){
				if(posMaybe > width){
					it = prevIt;
					posMaybe = prevPosMaybe;
					break;
				}else{
					prevIt = it;
					prevPosMaybe = posMaybe;
				}
			}
			++it;
		}
		++it;
		if(posMaybe > width){
			if(!out.empty()){
				out.flush(&outString, width - curPos, &outTTYPosList);
				f(outString, width - curPos, outTTYPosList);
				curPos = 0;
				it = org;
				continue;
			}else{
				if(!useGraphBreak){
					useGraphBreak = true;
					it = org;
					goto retry;
				}else{
					out.push(".", TTYAttr::reverse, it->codePointPos);
					out.flush(&outString, width - curPos, &outTTYPosList);
					f(outString, width - curPos, outTTYPosList);
					curPos = 0;
					continue;
				}
			}
		}else{
			auto jt = org;
			posMaybe = curPos;
			while(jt != it){
				size_t pos = jt - cpList.begin();
				bool mc = false;
				TTYAttr tattr = (mc = curMatch != matchList.end() && curMatch->start() <= pos && pos < curMatch->end()) ? matchColor : TTYAttr();
				if(jt->codePoint == U'\t'){
					size_t prevPosMaybe = posMaybe;
					posMaybe = ((posMaybe + 1) / tabSize + 1) * tabSize;
					for(size_t i = prevPosMaybe ; i < posMaybe ; ++i)
						out.push(" ", tattr, jt->codePointPos); //consider altTTY
				}else if(jt->codePoint == U'\r' || jt->codePoint == U'\n' || jt->codePoint == U'\x85' || jt->codePoint == U'\x2028' || jt->codePoint == U'\x2029' || jt->codePoint == U'\x0b' || jt->codePoint == U'\x0c'){
					out.pushEmpty();
				}else{
					jt->utf8_push_tty(out, tattr);
					if(jt->altTTYSize == 0)
						posMaybe += jt->ttyWidth;
					else
						posMaybe += jt->altTTYSize;
				}
				while(curMatch != matchList.end() && curMatch->end() + 1 <= pos)
					++curMatch;
				++jt;
			}
			if(it != cpList.begin() && (it - 1)->lineBreakMode == lbForce){
				out.flush(&outString, width - posMaybe, &outTTYPosList);
				f(outString, width - posMaybe, outTTYPosList);
				// remove CR and LF, so empty string is allowed
				curPos = 0;
				continue;
			}else
				curPos = posMaybe;
		}
cont:
		;
	}
	if(!out.empty()){
		out.flush(&outString, width - curPos, &outTTYPosList);
		f(outString, width - curPos, outTTYPosList);
	}
}

} //namespace UTF
} //namespace Yk

#endif
