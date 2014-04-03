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

MPF::Visual::Size Border::MeasureSize()
{
	auto size = ContentElement::MeasureSize();
	auto border = BorderThickness;
	size.Width += border.Left + border.Right;
	size.Height += border.Top + border.Bottom;

	return size;
}

void Border::RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{
	auto bound = args.RenderQuad -= BorderThickness;
	ContentElement::RenderCore(renderer, { bound });
	auto borderBrush = BorderBrush;
	if (borderBrush)
	{
		renderer.DrawQuad(args.RenderQuad, *borderBrush);
	}
}

MPF::Visual::Quad Border::MeasureContentBound(UIElement& elem)
{
	auto borderThick = BorderThickness;
	auto bound = ContentElement::MeasureContentBound(elem);
	bound.Transpose({ borderThick.Left, borderThick.Top });
	return bound;
}