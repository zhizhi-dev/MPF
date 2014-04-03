#pragma once
#include "ContentElement.h"

NS_MPF
NS_UI

//所有 Button 的基类
class ButtonBase : public ContentElement
{
public:
	MPF_API ButtonBase();
	MPF_API virtual ~ButtonBase();

	//获取类型
	MPF_API DECLARE_GETTYPE(ButtonBase);
	MPF_API DECLARE_GETINSTANTTYPE(ButtonBase);
protected:

	DECLARE_UI_FUNCS
private:
	DECLARE_UI_VALUES
	DECLARE_TYPE(ButtonBase);
};

NS_ED
NS_ED