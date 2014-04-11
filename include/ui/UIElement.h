#pragma once
#include "../Type.h"
#include "../DependencyObject.h"
#include "Visibility.h"
#include "../visual/RenderCoreProvider.h"
#include "RenderArgs.h"
#include "../visual/Thickness.h"
#include "../visual/Size.h"
#include "../RoutedEvent.h"
#include "../RoutedEventArgs.h"
#include "../EventWrapper.h"
#include "../input/InputEventHandlers.h"
#include "ControlTemplate.h"

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

	//获取模板
	MPF_API ControlTemplate GetTemplate() const;
	//设置模板
	MPF_API void SetTemplate(ControlTemplate&& value);
	//获取或设置模板
	mproperty(ControlTemplate, Template);

	MPF_API UIElement* GetParent() const mnoexcept{ return parent; }

	//鼠标左键释放时触发事件
	EventWrapper<UIElement, MPF::Input::MouseEventHandler, MPF::Input::MouseEventArgs> MouseLeftButtonUp;

	MPF_API void Render(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args);
	MPF_API void Update(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args);

	MPF_API MPF::Visual::Size MeasureSize() mnoexcept;
	MPF_API MPF::Visual::Quad GetRenderBound() const mnoexcept;
	///<summary>点击测试</summary>
	///<return>测试成功的UI元素，并按逻辑树上从顶端到底端排列</return>
	MPF_API std::vector<UIElement*> HitTest(MPF::Visual::Point point) mnoexcept;
	MPF_API virtual bool HitTest(MPF::Visual::Point point, std::vector<UIElement*>& elements) mnoexcept;

	//引发事件
	template<typename THandler, typename TArgs>
	static void RaiseEvent(const RoutedEvent<THandler>& ent, TArgs& args)
	{
		RaiseEventInternal(ent, args);
	}

	//获取类型
	MPF_API DECLARE_GETTYPE(UIElement);
	MPF_API DECLARE_GETINSTANTTYPE(UIElement);
	DECLARE_PUB_UI_FUNCS;
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
	//模板
	MPF_API static DependencyProperty<ControlTemplate> TemplateProperty;
	//鼠标左键释放时触发事件
	MPF_API static RoutedEvent<MPF::Input::MouseEventHandler> MouseLeftButtonUpEvent;
protected:
	MPF_API virtual void RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args);
	MPF_API virtual void UpdateCore(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args);
	MPF_API virtual void OnMouseLeftButtonUp(MPF::Input::MouseEventArgs& args);
protected:
	//更新相对父节点的偏移
	MPF_API virtual void UpdateRelativeOffset() mnoexcept;
	///<summary>更新渲染区域</summary>
	///<param name="parentOffset">父节点的绝对偏移</param>
	MPF_API virtual void UpdateRenderBound(MPF::Visual::Point parentOffset) mnoexcept;
	//更新大小
	MPF_API virtual void UpdateSize() mnoexcept;
	//自动计算大小
	MPF_API virtual MPF::Visual::Size AutoMeasureSize() mnoexcept;

	DECLARE_UI_FUNCS
protected:
	//渲染区域
	std::pair<bool, MPF::Visual::Quad> renderBound = { true, MPF::Visual::Quad()};
	//相对父节点的偏移
	std::pair<bool, MPF::Visual::Point> relativeOffset = { true, MPF::Visual::Point() };
	//大小
	std::pair<bool, MPF::Visual::Size> size = { true, MPF::Visual::Size() };
protected:
	MPF_API static void RaiseEventInternal(const IRoutedEvent& ent, RoutedEventArgs& args);
	MPF_API static void SetParent(UIElement& element, UIElement* parent) mnoexcept;
private:
	void InitializeEventHandlers();
private:
	UIElement* parent = nullptr;
	std::unique_ptr<TemplateInstance> templateInst;
	UIElement* templateRoot = nullptr;
	DECLARE_UI_VALUES
	DECLARE_TYPE(UIElement)
};

NS_ED
NS_ED