#ifndef __DECOMP_DATA_HPP__
#define __DECOMP_DATA_HPP__
#include <vector>

namespace Yk{
namespace UTF{            

	enum DecompMode {
		dmCanonical,
		dmCircle,
		dmCompat,
		dmFinal,
		dmFont,
		dmFraction,
		dmInitial,
		dmIsolated,
		dmMedial,
		dmNarrow,
		dmNoBreak,
		dmNone,
		dmSmall,
		dmSquare,
		dmSub,
		dmSuper,
		dmVertical,
		dmWide
	};

    struct DecompData{
        DecompMode mode;
        std::vector<char32_t> data;
    };

	DecompData getDecompData(char32_t codePoint);


}
}

#endif