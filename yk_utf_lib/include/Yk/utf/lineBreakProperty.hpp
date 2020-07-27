#ifndef __LINE_BREAK_PROPERTY_HPP__
#define __LINE_BREAK_PROPERTY_HPP__


namespace Yk{
namespace UTF{

	enum LineBreakProperty {
		lbAL,
		lbB2,
		lbBA,
		lbBB,
		lbBK,
		lbCB,
		lbCL_FWH,
		lbCL_NonFWH,
		lbCM,
		lbCP_NonFWH,
		lbCR,
		lbEB,
		lbEM,
		lbEX,
		lbGL,
		lbH2,
		lbH3,
		lbHL,
		lbHY,
		lbHYBA_AFTER_HL,
		lbID,
		lbIN,
		lbIS,
		lbJL,
		lbJT,
		lbJV,
		lbLF,
		lbNL,
		lbNS,
		lbNU,
		lbOP_FWH,
		lbOP_NonFWH,
		lbPO,
		lbPR,
		lbQU,
		lbRI,
		lbRI_first,
		lbSP,
		lbSPm_AFTER_B2,
		lbSPm_AFTER_CLCP,
		lbSPm_AFTER_OP,
		lbSPm_AFTER_QU,
		lbSPm_AFTER_ZW,
		lbSY,
		lbWJ,
		lbZW,
		lbZWJ,
		lbNil
	};


	enum LBMode {
	    lbTrue,
	    lbFalse,
	    lbForce
	};



	extern LBMode lineBreakPropertyCompList[lbNil][lbNil];

    LineBreakProperty getLineBreakProperty(char32_t cp);



}
}

#endif