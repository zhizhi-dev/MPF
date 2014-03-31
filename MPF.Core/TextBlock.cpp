#include "stdafx.h"
#include "../include/ui/TextBlock.h"
#include "../include/visual/LinearGradientBrush.h"
#include "../include/visual/AlphaBlendBrush.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;

DEFINE_TYPE(TextBlock, MPF::UI::TextBlock)
DEFINE_UI_VALUES(TextBlock)
DEFINE_UI_FUNCS(TextBlock, UIElement)

DependencyProperty<MPF::String> TextBlock::TextProperty(L"Text", String::GetEmpty());
DependencyProperty<MPF::Visual::Font> TextBlock::FontProperty(L"Font", MPF::Visual::Font(L"Microsoft YaHei", 15.f));

TextBlock::TextBlock()
{
	AddPropertyHandlers();
}

TextBlock::TextBlock(const MPF::String& text)
:TextBlock()
{
	Text = text;
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

void TextBlock::UpdateCore(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime)
{
	if (Visibility == Visibility::Visible)
	{
		if (textGlyphs == nullptr)
		{
			UpdateTextGlyphs();
		}
	}
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
	LinearGradientBrush linearBrush(0xFF00FF00, 0xFFFF00FF);
	AlphaBlendBrush blendBrush(*textGlyphs, linearBrush);

	renderer.FillQuad(args.RenderQuad, blendBrush);
	UIElement::RenderCore(renderer, std::move(args));
}

MPF::Visual::Quad TextBlock::MeasureSize()
{
	auto width = textGlyphs->GetWidth();
	auto height = textGlyphs->GetHeight();

	return Quad(Point(), Point(width, 0.f, 1.f, 0.f),
		Point(width, height, 1.f, 1.f), Point(0.f, height, 0.f, 1.f));
}