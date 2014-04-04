#pragma once
#include "Panel.h"

NS_MPF
NS_UI

//画板
class Canvas : public Panel
{
public:
	MPF_API Canvas();
	MPF_API virtual ~Canvas();

	//获取横坐标
	MPF_API static float GetLeft(const UIElement& elem);
	//设置横坐标
	MPF_API static void SetLeft(UIElement& elem, float value);
	//获取纵坐标
	MPF_API static float GetTop(const UIElement& elem);
	//设置纵坐标
	MPF_API static void SetTop(UIElement& elem, float value);
	//获取坐标
	MPF_API static std::pair<float, float> GetPosition(const UIElement& elem);
	//设置坐标
	MPF_API static void SetPosition(UIElement& elem, const std::pair<float, float>& position);

	//获取类型
	MPF_API DECLARE_GETTYPE(Canvas);
	MPF_API DECLARE_GETINSTANTTYPE(Canvas);
public:
	//横坐标
	MPF_API static DependencyProperty<float> LeftProperty;
	//纵坐标
	MPF_API static DependencyProperty<float> TopProperty;
protected:
	MPF_API virtual MPF::Visual::Point MakeChildOffset(UIElement& elem);
protected:
	DECLARE_UI_FUNCS
private:
	DECLARE_UI_VALUES
	DECLARE_TYPE(Canvas)
};

NS_ED
NS_ED