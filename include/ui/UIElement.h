#pragma once
#include "../Type.h"
#include "../DependencyObject.h"
#include "Visibility.h"
#include "../visual/RenderCoreProvider.h"

NS_MPF
NS_UI

class UIElement : public DependencyObject
{
public:
	MPF_API UIElement();
	MPF_API virtual ~UIElement();

	//加载
	MPF_API virtual void Initialize();

	//获取宽度
	MPF_API float GetWidth() const;
	//设置宽度
	MPF_API void SetWidth(float value);
	//获取或设置宽度
	mproperty(float, Width);

	//获取高度
	MPF_API float GetHeight() const;
	//设置高度
	MPF_API void SetHeight(float value);
	//获取或设置高度
	mproperty(float, Height);

	//获取可见性
	MPF_API Visibility GetVisibility() const;
	//设置可见性
	MPF_API void SetVisibility(Visibility value);
	//获取或设置可见性
	mproperty(Visibility, Visibility);

	MPF_API void Render(MPF::Visual::RenderCoreProvider& renderer);
	MPF_API void Update(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime);

	//获取类型
	MPF_API DECLARE_GETTYPE(UIElement)
	MPF_API DECLARE_GETINSTANTTYPE(UIElement)
public:
	//宽度
	MPF_API static DependencyProperty<float> WidthPropery;
	//高度
	MPF_API static DependencyProperty<float> HeightPropery;
	//可见性
	MPF_API static DependencyProperty<MPF::UI::Visibility> VisibilityPropery;
protected:
	MPF_API virtual void RenderCore(MPF::Visual::RenderCoreProvider& renderer);
	MPF_API virtual void UpdateCore(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime);
protected:
	DECLARE_UI_FUNCS
private:
	DECLARE_UI_VALUES
	DECLARE_TYPE(UIElement)
};

NS_ED
NS_ED