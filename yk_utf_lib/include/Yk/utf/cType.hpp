#include <boost/integer.hpp>

namespace Yk{
namespace UTF{            

	typedef int CType;

	/*class CTypeBase {
		int data;
		CTypeBase(){ data = 0; };
		constexpr CTypeBase(const CTypeBase& arg) : data(arg.data){ };
		constexpr explicit CTypeBase(const int arg) : data(arg){ }
		friend CType;
	public:
		constexpr operator int() const { return data; }
	};

	class CType : public CTypeBase{
	public:
		CType() = default;
		constexpr CType(const int data) : CTypeBase(data) {}
		constexpr CType(const CTypeBase& base) : CTypeBase(base) {}
		CType operator|=(const CTypeBase& arg){ 
			return CType(*this | arg);
		}
		static constexpr CTypeBase ctAlnum{1 << 0};
		static constexpr CTypeBase ctAlpha{1 << 1};
		static constexpr CTypeBase ctAscii{1 << 2};
		static constexpr CTypeBase ctBlank{1 << 3};
		static constexpr CTypeBase ctCntrl{1 << 4};
		static constexpr CTypeBase ctDigit{1 << 5};
		static constexpr CTypeBase ctGraph{1 << 6};
		static constexpr CTypeBase ctHorizontalSpace{1 << 7};
		static constexpr CTypeBase ctLower{1 << 8};
		static constexpr CTypeBase ctPrint{1 << 9};
		static constexpr CTypeBase ctPunct{1 << 10};
		static constexpr CTypeBase ctSpace{1 << 11};
		static constexpr CTypeBase ctUpper{1 << 12};
		static constexpr CTypeBase ctVerticalSpace{1 << 13};
		static constexpr CTypeBase ctWord{1 << 14};
		static constexpr CTypeBase ctXdigit{1 << 15};
		static constexpr CTypeBase ctOther{0};

	};
		static constexpr CType ctAlnum{1 << 0};
		static constexpr CType ctAlpha{1 << 1};
		static constexpr CType ctAscii{1 << 2};
		static constexpr CType ctBlank{1 << 3};
		static constexpr CType ctCntrl{1 << 4};
		static constexpr CType ctDigit{1 << 5};
		static constexpr CType ctGraph{1 << 6};
		static constexpr CType ctHorizontalSpace{1 << 7};
		static constexpr CType ctLower{1 << 8};
		static constexpr CType ctPrint{1 << 9};
		static constexpr CType ctPunct{1 << 10};
		static constexpr CType ctSpace{1 << 11};
		static constexpr CType ctUpper{1 << 12};
		static constexpr CType ctVerticalSpace{1 << 13};
		static constexpr CType ctWord{1 << 14};
		static constexpr CType ctXdigit{1 << 15};
		static constexpr CType ctOther{0};


	/*enum CType : boost::int_t<16> {
		ctAlnum = 1 << 0,
		ctAlpha = 1 << 1,
		ctAscii = 1 << 2,
		ctBlank = 1 << 3,
		ctCntrl = 1 << 4,
		ctDigit = 1 << 5,
		ctGraph = 1 << 6,
		ctHorizontalSpace = 1 << 7,
		ctLower = 1 << 8,
		ctPrint = 1 << 9,
		ctPunct = 1 << 10,
		ctSpace = 1 << 11,
		ctUpper = 1 << 12,
		ctVerticalSpace = 1 << 13,
		ctWord = 1 << 14,
		ctXdigit = 1 << 15,
		ctOther = 0
	};*/

	const int ctAlnum = 1 << 0;
	const int ctAlpha = 1 << 1;
	const int ctAscii = 1 << 2;
	const int ctBlank = 1 << 3;
	const int ctCntrl = 1 << 4;
	const int ctDigit = 1 << 5;
	const int ctGraph = 1 << 6;
	const int ctHorizontalSpace = 1 << 7;
	const int ctLower = 1 << 8;
	const int ctPrint = 1 << 9;
	const int ctPunct = 1 << 10;
	const int ctSpace = 1 << 11;
	const int ctUpper = 1 << 12;
	const int ctVerticalSpace = 1 << 13;
	const int ctWord = 1 << 14;
	const int ctXdigit = 1 << 15;
	const int ctOther = 0;

	CType getCType(char32_t codePoint);


}
}
