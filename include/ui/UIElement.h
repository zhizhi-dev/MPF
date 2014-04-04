#pragma once
#include "../Type.h"
#include "../DependencyObject.h"
#include "Visibility.h"
#include "../visual/RenderCoreProvider.h"
#include "RenderArgs.h"
#include "../visual/Thickness.h"
#include "../visual/Size.h"

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

	//获取边距
	MPF_API const MPF::Visual::Thickness& GetMargin() const;
	//设置边距
	MPF_API void SetMargin(const MPF::Visual::Thickness& value);
	//获取或设置边距
	mproperty(MPF::Visual::Thickness, Margin);

	//获取留白
	MPF_API const MPF::Visual::Thickness& GetPadding() const;
	//设置留白
	MPF_API void SetPadding(const MPF::Visual::Thickness& value);
	//获取或设置留白
	mproperty(MPF::Visual::Thickness, Padding);

	MPF_API void Render(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args);
	MPF_API void Update(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args);

	MPF_API MPF::Visual::Size MeasureSize() mnoexcept;

	//获取类型
	MPF_API DECLARE_GETTYPE(UIElement)
	MPF_API DECLARE_GETINSTANTTYPE(UIElement)
public:
	//宽度
	MPF_API static DependencyProperty<float> WidthProperty;
	//高度
	MPF_API static DependencyProperty<float> HeightProperty;
	//可见性
	MPF_API static DependencyProperty<MPF::UI::Visibility> VisibilityProperty;
	//边距
	MPF_API static DependencyProperty<MPF::Visual::Thickness> MarginProperty;
	//留白
	MPF_API static DependencyProperty<MPF::Visual::Thickness> PaddingProperty;
protected:
	MPF_API virtual void RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args);
	MPF_API virtual void UpdateCore(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args);
protected:
	//更新相对父节点的偏移
	MPF_API virtual void UpdateRelativeOffset() mnoexcept;
	///<summary>更新渲染区域</summary>
	///<param name="parentOffset">父节点的绝对偏移</param>
	MPF_API virtual void UpdateRenderBound(MPF::Visual::Point parentOffset) mnoexcept;
	//更新大小
	MPF_API virtual void UpdateSize() mnoexcept;
	MPF_API virtual UIElement* HitTest(MPF::Visual::Point point);
	DECLARE_UI_FUNCS
protected:
	//渲染区域
	std::pair<bool, MPF::Visual::Quad> renderBound = { true, MPF::Visual::Quad()};
	//相对父节点的偏移
	std::pair<bool, MPF::Visual::Point> relativeOffset = { true, MPF::Visual::Point() };
	//大小
	std::pair<bool, MPF::Visual::Size> size = { true, MPF::Visual::Size() };
private:
	DECLARE_UI_VALUES
	DECLARE_TYPE(UIElement)
};

NS_ED
NS_ED