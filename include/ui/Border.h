#pragma once
#include "ContentElement.h"
#include "../visual/Brush.h"

NS_MPF
NS_UI

//边框
class Border : public ContentElement
{
public:
	MPF_API Border();
	MPF_API virtual ~Border();

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
	DECLARE_GETTYPE(Border);
	DECLARE_GETINSTANTTYPE(Border);
	DECLARE_PUB_UI_FUNCS;
public:
	//边框画刷
	MPF_API static DependencyProperty<const MPF::Visual::Brush*> BorderBrushProperty;
	//边框厚度
	MPF_API static DependencyProperty<MPF::Visual::Thickness> BorderThicknessProperty;
protected:
	MPF_API virtual void RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args);
	MPF_API virtual MPF::Visual::Point MakeContentOffset(UIElement& elem);
	//自动计算大小
	MPF_API virtual MPF::Visual::Size AutoMeasureSize() mnoexcept;

	DECLARE_UI_FUNCS
private:
	DECLARE_UI_VALUES
	DECLARE_TYPE(Border);
};

NS_ED
NS_ED