#include "stdafx.h"
#include "../include/ui/UIElement.h"

using namespace MPF;
using namespace MPF::UI;

DEFINE_TYPE(UIElement, MPF::UI::UIElement)
DEFINE_UI_VALUES(UIElement)
DEFINE_UI_FUNCS(UIElement, DependencyObject)

DependencyProperty<float> UIElement::WidthPropery(std::make_shared<String>(L"Width"));
DependencyProperty<float> UIElement::HeightPropery(std::make_shared<String>(L"Height"));
DependencyProperty<Visibility> UIElement::VisibilityPropery(std::make_shared<String>(L"Visibility"), Visibility::Visible);

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
	return GetValue(WidthPropery);
}

void UIElement::SetWidth(float value)
{
	SetValue(WidthPropery, value);
}

float UIElement::GetHeight() const
{
	return GetValue(HeightPropery);
}

void UIElement::SetHeight(float value)
{
	SetValue(HeightPropery, value);
}

Visibility UIElement::GetVisibility() const
{
	return GetValue(VisibilityPropery);
}

void UIElement::SetVisibility(MPF::UI::Visibility value)
{
	SetValue(VisibilityPropery, value);
}

void UIElement::Render(MPF::Visual::RenderCoreProvider& renderer)
{
	if (Visibility == Visibility::Visible)
	{
		RenderCore(renderer);
	}
}

void UIElement::RenderCore(MPF::Visual::RenderCoreProvider& renderer)
{

}

void UIElement::Update(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime)
{

}