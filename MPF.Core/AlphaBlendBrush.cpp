#include "stdafx.h"
#include "../include/visual/AlphaBlendBrush.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(AlphaBlendBrush, MPF::Visual::AlphaBlendBrush)

AlphaBlendBrush::AlphaBlendBrush(const BitmapData<byte>& alpha,
const Brush& secondBrush) noexcept
:alpha(&alpha), secondBrush(&secondBrush)
{
}

const BitmapData<byte>& AlphaBlendBrush::GetAlpha() const noexcept
{
	return *alpha;
}

void AlphaBlendBrush::SetAlpha(const BitmapData<byte>& value) noexcept
{
	alpha = &value;
}

const Brush& AlphaBlendBrush::GetSecondBrush() const noexcept
{
	return *secondBrush;
}

void AlphaBlendBrush::SetSecondBrush(const Brush& value) noexcept
{
	secondBrush = &value;
}

color_t AlphaBlendBrush::TakeSample(float u, float v) const
{
	argb_color orgColor(secondBrush->TakeSample(u, v));
	uint32_t x = std::roundf(u * alpha->GetWidth());
	uint32_t y = std::roundf(v * alpha->GetHeight());
	auto a(alpha->GetDataPointer()[y * alpha->GetPitch() + x] / 255.f);
	
	orgColor.alpha *= a;
	return orgColor;
}