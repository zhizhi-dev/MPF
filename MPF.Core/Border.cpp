#include "stdafx.h"
#include "../include/ui/Border.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(Border, MPF::UI::Border)
DEFINE_UI_VALUES(Border)
DEFINE_UI_FUNCS(Border, ContentElement)

DependencyProperty<const MPF::Visual::Brush*> Border::BorderBrushProperty(L"BorderBrush");
DependencyProperty<MPF::Visual::Thickness> Border::BorderThicknessProperty(L"BorderThickness");

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
	ContentElement::RenderCore(renderer, std::move(args));
	auto borderBrush = BorderBrush;
	if (borderBrush)
	{
		renderer.DrawQuad(args.RenderQuad, *borderBrush);
	}
}

MPF::Visual::Quad Border::MeasureContentBound(UIElement& elem)
{
	auto border = BorderThickness;
	auto bound(elem.MeasureBound());
	bound.Transform([&](Point& pt)
	{
		pt.X += border.Left;
		pt.Y += border.Top;
	});

	return bound;
}