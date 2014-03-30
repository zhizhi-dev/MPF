#pragma once
#include "UIElement.h"

NS_MPF
NS_UI

//内容UI元素
class ContentElement : public UIElement
{
public:
	MPF_API ContentElement();
	MPF_API virtual ~ContentElement();

	//获取内容
	MPF_API std::weak_ptr<UIElement> GetContent() const;
	//设置内容
	MPF_API void SetContent(std::weak_ptr<UIElement> value);
	//获取或设置内容
	mproperty(std::weak_ptr<UIElement>, Content);

	//获取类型
	MPF_API DECLARE_GETTYPE(ContentElement)
	MPF_API DECLARE_GETINSTANTTYPE(ContentElement)
public:
	//内容
	MPF_API static DependencyProperty<std::weak_ptr<UIElement>> ContentPropery;
protected:
	MPF_API virtual void RenderCore(MPF::Visual::RenderCoreProvider& renderer);
	MPF_API virtual void UpdateCore(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime);
protected:
	DECLARE_UI_FUNCS
private:
	DECLARE_UI_VALUES
	DECLARE_TYPE(ContentElement)
};

NS_ED
NS_ED