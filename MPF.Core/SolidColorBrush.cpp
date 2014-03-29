#include "stdafx.h"
#include "../include/visual/SolidColorBrush.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(SolidColorBrush, MPF::Visual::SolidColorBrush)

SolidColorBrush::SolidColorBrush() mnoexcept
{

}

SolidColorBrush::SolidColorBrush(color_t color) mnoexcept
:color(color)
{

}

color_t SolidColorBrush::GetColor() const mnoexcept
{
	return color;
}

void SolidColorBrush::SetColor(color_t color) mnoexcept
{
	this->color = color;
}

color_t SolidColorBrush::TakeSample(float u, float v) const
{
	return color;
}