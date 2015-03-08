#include "stdafx.h"
#include "../include/visual/SolidColorBrush.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(SolidColorBrush, MPF::Visual::SolidColorBrush)

SolidColorBrush::SolidColorBrush() noexcept
{

}

SolidColorBrush::SolidColorBrush(color_t color) noexcept
:color(color)
{

}

color_t SolidColorBrush::GetColor() const noexcept
{
	return color;
}

void SolidColorBrush::SetColor(color_t color) noexcept
{
	this->color = color;
}

color_t SolidColorBrush::TakeSample(float u, float v) const
{
	return color;
}