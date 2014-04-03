#include "stdafx.h"
#include "../include/ui/Button.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(Button, MPF::UI::Button)
DEFINE_UI_VALUES(Button)
DEFINE_UI_FUNCS(Button, ButtonBase)

Button::Button()
{

}

Button::~Button()
{

}

void Button::SetBorderBrush(const MPF::Visual::Brush* value)
{
	SetValue(Border::BorderBrushProperty, value);
}

MPF::Visual::Thickness Button::GetBorderThickness() const
{
	return GetValue(Border::BorderThicknessProperty);
}

void Button::SetBorderThickness(const MPF::Visual::Thickness& value)
{
	SetValue(Border::BorderThicknessProperty, value);
}