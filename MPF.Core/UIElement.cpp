#include "stdafx.h"
#include "../include/ui/UIElement.h"
#include "../include/Enumerable.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(UIElement, MPF::UI::UIElement)
DEFINE_UI_VALUES(UIElement)
DEFINE_UI_FUNCS(UIElement, DependencyObject)

DependencyProperty<float> UIElement::WidthProperty(L"Width", NAN);
DependencyProperty<float> UIElement::HeightProperty(L"Height", NAN);
DependencyProperty<Visibility> UIElement::VisibilityProperty(L"Visibility", Visibility::Visible);
DependencyProperty<Thickness> UIElement::MarginProperty(L"Margin");
DependencyProperty<Thickness> UIElement::PaddingProperty(L"Padding");

UIElement::UIElement()
{

}

UIElement::~UIElement()
{

}

void UIElement::Initialize()
{

}

float UIElement::GetWidth() const
{
	return GetValue(WidthProperty);
}

void UIElement::SetWidth(float value)
{
	SetValue(WidthProperty, value);
}

float UIElement::GetHeight() const
{
	return GetValue(HeightProperty);
}

void UIElement::SetHeight(float value)
{
	SetValue(HeightProperty, value);
}

Visibility UIElement::GetVisibility() const
{
	return GetValue(VisibilityProperty);
}

void UIElement::SetVisibility(MPF::UI::Visibility value)
{
	SetValue(VisibilityProperty, value);
}

Thickness UIElement::GetMargin() const
{
	return GetValue(MarginProperty);
}

void UIElement::SetMargin(const Thickness& value)
{
	SetValue(MarginProperty, value);
}

Thickness UIElement::GetPadding() const
{
	return GetValue(PaddingProperty);
}

void UIElement::SetPadding(const Thickness& value)
{
	SetValue(PaddingProperty, value);
}

void UIElement::Render(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{
	if (Visibility == Visibility::Visible)
	{
		RenderCore(renderer, std::move(args));
	}
}

void UIElement::RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{

}

void UIElement::Update(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime)
{
	UpdateCore(renderer, elapsedTime);
}

void UIElement::UpdateCore(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime)
{

}

MPF::Visual::Quad UIElement::MeasureBound()
{
	auto margin = Margin;
	auto size = MeasureSize();
	auto left = margin.Left;
	auto top = margin.Top;
	auto right = left + size.Width;
	auto bottom = top + size.Height;

	return Quad(Point(left, top), Point(right, top, 1.f), Point(right, bottom, 1.f, 1.f),
		Point(left, bottom, 0.f, 1.f));
}

MPF::Visual::Size UIElement::MeasureSize()
{
	auto width = Width;
	auto height = Height;
	auto padding = Padding;

	if (std::isnan(width))width = padding.Left + padding.Right;
	if (std::isnan(height))height = padding.Top + padding.Bottom;

	return{ width, height };
}