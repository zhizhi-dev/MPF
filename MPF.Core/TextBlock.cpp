#include "stdafx.h"
#include "../include/ui/TextBlock.h"
#include "../include/visual/SolidColorBrush.h"
#include "../include/visual/AlphaBlendBrush.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;

DEFINE_TYPE(TextBlock, MPF::UI::TextBlock)
DEFINE_UI_VALUES(TextBlock)
DEFINE_UI_FUNCS(TextBlock, UIElement)

static SolidColorBrush defaultForegroundBrush(0xFF000000);
DependencyProperty<MPF::String> TextBlock::TextProperty(L"Text", String::GetEmpty());
DependencyProperty<MPF::Visual::Font> TextBlock::FontProperty(L"Font", MPF::Visual::Font(L"Microsoft YaHei", 15.f));
DependencyProperty<const MPF::Visual::Brush*> TextBlock::ForegroundProperty(L"Foreground", &defaultForegroundBrush);

TextBlock::TextBlock()
{
	AddPropertyHandlers();
}

TextBlock::TextBlock(const MPF::String& text)
:TextBlock()
{
	SetText(text);
}

TextBlock::TextBlock(MPF::String&& text)
: TextBlock()
{
	SetText(std::move(text));
}

TextBlock::~TextBlock()
{

}

const MPF::String& TextBlock::GetText() const
{
	return GetValue(TextProperty);
}

void TextBlock::SetText(const MPF::String& value)
{
	SetValue(TextProperty, value);
}

void TextBlock::SetText(MPF::String&& value)
{
	SetValue(TextProperty, std::move(value));
}

void TextBlock::OnTextChanged()
{
	//×ÖÐÎ»º³åÊ§Ð§
	textGlyphs = nullptr;
}

void TextBlock::AddPropertyHandlers()
{
	SetPropertyChangedHandler(TextProperty, [&]
	{
		OnTextChanged(); 
	});
}

void TextBlock::UpdateCore(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args)
{
	UIElement::UpdateCore(renderer, std::move(args));
}

void TextBlock::UpdateTextGlyphs()
{
	auto font(Font);
	auto& text(Text);

	auto size(font.MeasureText(text));
	textGlyphs = std::make_unique<BitmapData<byte>>(size.first, size.second);
	font.DrawText(*textGlyphs, 0, 0, text);
}

const MPF::Visual::Font& TextBlock::GetFont() const
{
	return GetValue(FontProperty);
}

void TextBlock::SetFont(const MPF::Visual::Font& value)
{
	SetValue(FontProperty, value);
}

void TextBlock::RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{
	auto foreground = Foreground;
	if (foreground)
	{
		auto textQuad = renderBound.second - Padding;
		AlphaBlendBrush blendBrush(*textGlyphs, *foreground);

		renderer.FillQuad(textQuad, blendBrush);
		UIElement::RenderCore(renderer, std::move(args));
	}
}

void TextBlock::UpdateSize() mnoexcept
{
	UIElement::UpdateSize();

	if (textGlyphs == nullptr)
	{
		UpdateTextGlyphs();
	}

	auto& size = this->size.second;
	size.Width += textGlyphs->GetWidth();
	size.Height += textGlyphs->GetHeight();
}

const MPF::Visual::Brush* TextBlock::GetForeground() const
{
	return GetValue(ForegroundProperty);
}

void TextBlock::SetForeground(const MPF::Visual::Brush* value)
{
	SetValue(ForegroundProperty, value);
}