#include "stdafx.h"
#include "../include/visual/AlphaBlendBrush.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(AlphaBlendBrush, MPF::Visual::AlphaBlendBrush)

AlphaBlendBrush::AlphaBlendBrush(std::shared_ptr<BitmapData<byte>> alpha,
std::shared_ptr<Brush> secondBrush) mnoexcept
:alpha(alpha), secondBrush(secondBrush)
{
	massert(alpha != nullptr);
	massert(secondBrush != nullptr);
}

std::shared_ptr<BitmapData<byte>> AlphaBlendBrush::GetAlpha() const mnoexcept
{
	return alpha;
}

void AlphaBlendBrush::SetAlpha(std::shared_ptr<BitmapData<byte>> value) mnoexcept
{
	massert(value != nullptr);
	alpha = value;
}

std::shared_ptr<Brush> AlphaBlendBrush::GetSecondBrush() const mnoexcept
{
	return secondBrush;
}

void AlphaBlendBrush::SetSecondBrush(std::shared_ptr<Brush> value) mnoexcept
{
	massert(value != nullptr);
	secondBrush = value;
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