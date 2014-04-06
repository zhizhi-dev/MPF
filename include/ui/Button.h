#pragma once
#include "ButtonBase.h"
#include "Border.h"

NS_MPF
NS_UI

//按钮
class Button : public ButtonBase
{
public:
	MPF_API Button();
	MPF_API virtual ~Button();

	//获取边框画刷
	MPF_API const MPF::Visual::Brush* GetBorderBrush() const;
	//设置边框画刷
	MPF_API void SetBorderBrush(const MPF::Visual::Brush* value);
	//获取或设置边框画刷
	mproperty(const MPF::Visual::Brush*, BorderBrush);

	//获取边框厚度
	MPF_API MPF::Visual::Thickness GetBorderThickness() const;
	//设置边框厚度
	MPF_API void SetBorderThickness(const MPF::Visual::Thickness& value);
	//获取或设置边框厚度
	mproperty(MPF::Visual::Thickness, BorderThickness);

	//获取类型
	MPF_API DECLARE_GETTYPE(Button);
	MPF_API DECLARE_GETINSTANTTYPE(Button);
	DECLARE_PUB_UI_FUNCS;
protected:

	DECLARE_UI_FUNCS
private:


	DECLARE_UI_VALUES
	DECLARE_TYPE(Button);
};

NS_ED
NS_ED