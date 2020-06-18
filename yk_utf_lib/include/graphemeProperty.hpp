#ifndef __GRAPHEME_PROPERTY_HPP__
#define __GRAPHEME_PROPERTY_HPP__

namespace Yk{
namespace UTF{

	enum GraphemeBreakProperty {
		gbCR,
		gbControl,
		gbExtend,
		gbExtended_Pictographic,
		gbL,
		gbLF,
		gbLV,
		gbLVT,
		gbOther,
		gbPrepend,
		gbRegional_Indicator,
		gbRegional_Indicator_First,
		gbSpacingMark,
		gbT,
		gbV,
		gbZWJ,
		gbZWJ_Extended_Pictographic,
		gbNil
	};


	extern bool graphemeBreakPropertyCompList[gbNil][gbNil];
    GraphemeBreakProperty getGraphemeBreakProperty(char32_t cp);

}
}

#endif
