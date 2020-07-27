#ifndef __GENERAL_CATEGORY_PROPERTY_HPP
#define __GENERAL_CATEGORY_PROPERTY_HPP

namespace Yk{
namespace UTF{            

	enum GeneralCategoryProperty {
		gcCc,
		gcCf,
		gcCn,
		gcCo,
		gcCs,
		gcLl,
		gcLm,
		gcLo,
		gcLt,
		gcLu,
		gcMc,
		gcMe,
		gcMn,
		gcNd,
		gcNl,
		gcNo,
		gcPc,
		gcPd,
		gcPe,
		gcPf,
		gcPi,
		gcPo,
		gcPs,
		gcSc,
		gcSk,
		gcSm,
		gcSo,
		gcZl,
		gcZp,
		gcZs
	};


	GeneralCategoryProperty getGeneralCategoryProperty(char32_t codePoint);


}
}


#endif