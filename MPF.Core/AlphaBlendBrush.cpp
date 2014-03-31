#include "stdafx.h"
#include "../include/visual/AlphaBlendBrush.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(AlphaBlendBrush, MPF::Visual::AlphaBlendBrush)

AlphaBlendBrush::AlphaBlendBrush(const BitmapData<byte>& alpha,
const Brush& secondBrush) mnoexcept
:alpha(&alpha), secondBrush(&secondBrush)
{
}

const BitmapData<byte>& AlphaBlendBrush::GetAlpha() const mnoexcept
{
	return *alpha;
}

void AlphaBlendBrush::SetAlpha(const BitmapData<byte>& value) mnoexcept
{
	alpha = &value;
}

const Brush& AlphaBlendBrush::GetSecondBrush() const mnoexcept
{
	return *secondBrush;
}

void AlphaBlendBrush::SetSecondBrush(const Brush& value) mnoexcept
{
	secondBrush = &value;
}

color_t AlphaBlendBrush::TakeSample(float u, float v) const
{
	argb_color orgColor(secondBrush->TakeSample(u, v));
	uint x = std::roundf(u * alpha->GetWidth());
	uint y = std::roundf(v * alpha->GetHeight());
	auto a(alpha->GetDataPointer()[y * alpha->GetPitch() + x] / 255.f);
	
	orgColor.alpha *= a;
	return orgColor;
}