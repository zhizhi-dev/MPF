#include "stdafx.h"
#include "../include/ui/Border.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(Border, MPF::UI::Border)
DEFINE_UI_VALUES(Border)
DEFINE_UI_FUNCS(Border, ContentElement)

Border::Border()
{

}

Border::~Border()
{

}

const MPF::Visual::Brush* Border::GetBorderBrush() const
{
	return GetValue(BorderBrushProperty);
}

void Border::SetBorderBrush(const MPF::Visual::Brush* value)
{
	SetValue(BorderBrushProperty, value);
}

MPF::Visual::Thickness Border::GetBorderThickness() const
{
	return GetValue(BorderThicknessProperty);
}

void Border::SetBorderThickness(const MPF::Visual::Thickness& value)
{
	SetValue(BorderThicknessProperty, value);
}

MPF::Visual::Size Border::AutoMeasureSize() noexcept
{
	auto size = ContentElement::AutoMeasureSize();

	auto border = BorderThickness;
	size.Width += border.Left + border.Right;
	size.Height += border.Top + border.Bottom;
	return size;
}

void Border::RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{
	ContentElement::RenderCore(renderer, std::move(args));
	auto borderBrush = BorderBrush;
	if (borderBrush)
	{
		renderer.DrawQuad(renderBound.second, *borderBrush);
	}
}

MPF::Visual::Point Border::MakeContentOffset(UIElement& elem)
{
	auto offset = ContentElement::MakeContentOffset(elem);
	auto borderThick = BorderThickness;
	return offset + Point(borderThick.Left, borderThick.Top);
}