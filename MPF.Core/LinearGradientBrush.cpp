#include "stdafx.h"
#include "../include/visual/LinearGradientBrush.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(LinearGradientBrush, MPF::Visual::LinearGradientBrush)

LinearGradientBrush::LinearGradientBrush(color_t startColor, color_t endColor) mnoexcept
:startColor(startColor), endColor(endColor)
{

}

color_t LinearGradientBrush::GetStartColor() const mnoexcept
{
	return startColor;
}

void LinearGradientBrush::SetStartColor(color_t color) mnoexcept
{
	this->startColor = color;
}

color_t LinearGradientBrush::GetEndColor() const mnoexcept
{
	return endColor;
}

void LinearGradientBrush::SetEndColor(color_t color) mnoexcept
{
	this->endColor = color;
}

color_t LinearGradientBrush::TakeSample(float u, float v) const
{
	const auto dr = (int)endColor.red - (int)startColor.red;
	const auto dg = (int)endColor.green - (int)startColor.green;
	const auto db = (int)endColor.blue - (int)startColor.blue;
	const auto weight = (u + v) * 0.5f;

	argb_color color = startColor;
	color.red = startColor.red + dr * weight;
	color.green = startColor.green + dg * weight;
	color.blue = startColor.blue + db * weight;
	
	return color;
}