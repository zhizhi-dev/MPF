#pragma once
#include "UIElement.h"
#include "../visual/BitmapData.h"
#include "../visual/Font.h"
#include "../visual/Brush.h"

NS_MPF
NS_UI

//文本块
class TextBlock : public UIElement
{
public:
	MPF_API TextBlock();
	MPF_API TextBlock(const MPF::String& text);
	MPF_API TextBlock(MPF::String&& text);
	MPF_API virtual ~TextBlock();

	//获取文字
	MPF_API const MPF::String& GetText() const;
	//设置文字
	MPF_API void SetText(const MPF::String& value);
	//设置文字
	MPF_API void SetText(MPF::String&& value);
	//获取或设置文字
	mproperty(MPF::String, Text);

	//获取字体
	MPF_API const MPF::Visual::Font& GetFont() const;
	//设置字体
	MPF_API void SetFont(const MPF::Visual::Font& value);
	//设置字体
	MPF_API void SetFont(MPF::Visual::Font&& value);
	//获取或设置字体
	mproperty(MPF::Visual::Font, Font);

	//获取前景画刷
	MPF_API const MPF::Visual::Brush* GetForeground() const;
	//设置前景画刷
	MPF_API void SetForeground(const MPF::Visual::Brush* value);
	//获取或设置前景画刷
	mproperty(const MPF::Visual::Brush*, Foreground);

	//获取类型
	MPF_API DECLARE_GETTYPE(TextBlock);
	MPF_API DECLARE_GETINSTANTTYPE(TextBlock);
public:
	//文字
	MPF_API static DependencyProperty<MPF::String> TextProperty;
	//字体
	MPF_API static DependencyProperty<MPF::Visual::Font> FontProperty;
	//前景画刷
	MPF_API static DependencyProperty<const MPF::Visual::Brush*> ForegroundProperty;
protected:
	MPF_API virtual void UpdateCore(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args);
	MPF_API virtual void RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args);
	//自动计算大小
	MPF_API virtual MPF::Visual::Size AutoMeasureSize() mnoexcept;

	DECLARE_UI_FUNCS
private:
	void AddPropertyHandlers();
	void OnTextChanged();
	void UpdateTextGlyphs();
	void EnsureTextGlyphs();
private:
	//字形数据
	std::unique_ptr<MPF::Visual::BitmapData<byte>> textGlyphs;

	DECLARE_UI_VALUES
	DECLARE_TYPE(TextBlock)
};

NS_ED
NS_ED