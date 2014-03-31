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
	MPF_API const std::vector<std::weak_ptr<UIElement>>& GetChildren() const;
	//获取子元素
	MPF_API std::vector<std::weak_ptr<UIElement>>& GetChildren();

	//获取类型
	MPF_API DECLARE_GETTYPE(Panel);
	MPF_API DECLARE_GETINSTANTTYPE(Panel);
public:
	//内容
	MPF_API static DependencyProperty<std::vector<std::weak_ptr<UIElement>>> ChildrenProperty;
protected:
	MPF_API virtual void RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args);
	MPF_API virtual void UpdateCore(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime);
protected:
	DECLARE_UI_FUNCS
private:
	DECLARE_UI_VALUES
	DECLARE_TYPE(Panel)
};

NS_ED
NS_ED