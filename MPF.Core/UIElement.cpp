#include "stdafx.h"
#include "../include/ui/UIElement.h"
#include "../include/Enumerable.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(UIElement, MPF::UI::UIElement)
DEFINE_UI_VALUES(UIElement)
DEFINE_UI_FUNCS(UIElement, DependencyObject)

DependencyProperty<float> UIElement::WidthProperty(std::make_shared<String>(L"Width"));
DependencyProperty<float> UIElement::HeightProperty(std::make_shared<String>(L"Height"));
DependencyProperty<Visibility> UIElement::VisibilityProperty(std::make_shared<String>(L"Visibility"), Visibility::Visible);
DependencyProperty<Thickness> UIElement::MarginProperty(std::make_shared<String>(L"Margin"));

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

void UIElement::SetMargin(Thickness value)
{
	SetValue(MarginProperty, value);
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
	auto points = MeasureSize().GetPoints();
	for (auto& pt : points)
	{
		pt.X += margin.Left;
		pt.Y += margin.Top;
	}
	
	return Quad(points[0], points[1], points[2], points[3]);
}

MPF::Visual::Quad UIElement::MeasureSize()
{
	auto width = Width;
	auto height = Height;

	return Quad(Point(), Point(width, 0.f), Point(width, height), Point(0.f, height));
}