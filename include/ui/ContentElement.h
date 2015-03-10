#pragma once
#include "TextBlock.h"

NS_MPF
NS_UI

//内容UI元素
class ContentElement : public TextBlock
{
public:
	MPF_API ContentElement();
	MPF_API virtual ~ContentElement();

	//获取内容
	MPF_API UIElement* GetContent() const;
	//设置内容
	MPF_API void SetContent(UIElement* value);
	//获取或设置内容
	mproperty(UIElement*, Content);

	//获取背景画刷
	MPF_API const MPF::Visual::Brush* GetBackground() const;
	//设置背景画刷
	MPF_API void SetBackground(const MPF::Visual::Brush* value);
	//获取或设置背景画刷
	mproperty(const MPF::Visual::Brush*, Background);

	using TextBlock::HitTest;
	MPF_API virtual bool HitTest(MPF::Visual::Point point, std::vector<UIElement*>& elements) noexcept;

	//获取类型
	MPF_API DECLARE_GETTYPE(ContentElement);
	MPF_API DECLARE_GETINSTANTTYPE(ContentElement);
	DECLARE_PUB_UI_FUNCS;
public:
	//内容
	MPF_API static DependencyProperty<UIElement*> ContentProperty;
	//背景
	MPF_API static DependencyProperty<const MPF::Visual::Brush*> BackgroundProperty;
protected:
	MPF_API virtual void RenderCore(MPF::Visual::RenderCoreProvider& renderer, const RenderArgs& args);
	MPF_API virtual void UpdateCore(MPF::Visual::RenderCoreProvider& renderer, const UpdateArgs& args);
	MPF_API virtual MPF::Visual::Point MakeContentOffset(UIElement& elem);
	//自动计算大小
	MPF_API virtual MPF::Visual::Size AutoMeasureSize() noexcept;
protected:
	DECLARE_UI_FUNCS
private:
	DECLARE_UI_VALUES
	DECLARE_TYPE(ContentElement)
};

NS_ED
NS_ED