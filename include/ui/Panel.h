#pragma once
#include "UIElement.h"

NS_MPF
NS_UI

//具有多个子元素的 UI 对象
class Panel : public UIElement
{
public:
	MPF_API Panel();
	MPF_API virtual ~Panel();

	//获取子元素
	MPF_API const std::vector<UIElement*>& GetChildren() const;
	//获取子元素
	MPF_API std::vector<UIElement*>& GetChildren();
	//添加子元素
	MPF_API void AddChild(UIElement& elem);

	//添加子元素
	template<typename TElem, typename ...TElems>
	void AddChildren(TElem& elem, TElems&... others)
	{
		AddChild(elem);
		AddChildren(others...);
	}

	//添加子元素
	template<typename TElem>
	void AddChildren(TElem& elem)
	{
		AddChild(elem);
	}

	using UIElement::HitTest;
	MPF_API virtual bool HitTest(MPF::Visual::Point point, std::vector<UIElement*>& elements) noexcept;

	//获取类型
	MPF_API DECLARE_GETTYPE(Panel);
	MPF_API DECLARE_GETINSTANTTYPE(Panel);
	DECLARE_PUB_UI_FUNCS;
public:
protected:
	MPF_API virtual void RenderCore(MPF::Visual::RenderCoreProvider& renderer, const RenderArgs& args);
	MPF_API virtual void UpdateCore(MPF::Visual::RenderCoreProvider& renderer, const UpdateArgs& args);
	MPF_API virtual MPF::Visual::Point MakeChildOffset(UIElement& elem);
	//自动计算大小
	MPF_API virtual MPF::Visual::Size AutoMeasureSize() noexcept;
protected:
	std::vector<UIElement*> children;

	DECLARE_UI_FUNCS
private:
	DECLARE_UI_VALUES
	DECLARE_TYPE(Panel)
};

NS_ED
NS_ED