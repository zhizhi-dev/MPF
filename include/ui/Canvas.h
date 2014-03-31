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

	//获取类型
	MPF_API DECLARE_GETTYPE(Canvas);
	MPF_API DECLARE_GETINSTANTTYPE(Canvas);
public:
	//横坐标
	MPF_API static DependencyProperty<float> LeftProperty;
	//纵坐标
	MPF_API static DependencyProperty<float> TopProperty;
protected:
	MPF_API virtual void RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args);
protected:
	DECLARE_UI_FUNCS
private:
	DECLARE_UI_VALUES
	DECLARE_TYPE(Canvas)
};

NS_ED
NS_ED