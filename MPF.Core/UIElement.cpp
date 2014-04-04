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

const Thickness& UIElement::GetMargin() const
{
	return GetValue(MarginProperty);
}

void UIElement::SetMargin(const Thickness& value)
{
	SetValue(MarginProperty, value);
}

const Thickness& UIElement::GetPadding() const
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

void UIElement::Update(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args)
{
	UpdateCore(renderer, std::move(args));
}

void UIElement::UpdateCore(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args)
{
	if (relativeOffset.first)
		UpdateRelativeOffset();

	if (size.first)
		UpdateSize();

	if (renderBound.first)
		UpdateRenderBound(args.ParentOffset);
}

void UIElement::UpdateRelativeOffset() mnoexcept
{
	auto margin = Margin;
	auto& offset = relativeOffset.second;
	offset.X = margin.Left;
	offset.Y = margin.Top;
	relativeOffset.first = false;
}

void UIElement::UpdateSize() mnoexcept
{
	auto& size = this->size.second;
	auto width = Width;
	auto height = Height;

	if (std::isnan(width) || std::isnan(height))
	{
		auto autoSize = AutoMeasureSize();
		if (std::isnan(width)) size.Width = autoSize.Width;
		if (std::isnan(height)) size.Height = autoSize.Height;
	}
	else
	{
		size.Width = width;
		size.Height = height;
	}
	this->size.first = false;
}

void UIElement::UpdateRenderBound(MPF::Visual::Point parentOffset) mnoexcept
{
	auto offset = relativeOffset.second + parentOffset;
	auto size = this->size.second;

	renderBound.second = Quad(Point(offset.X, offset.Y),
		Point(offset.X + size.Width, offset.Y + size.Height, 1.f, 1.f));
	renderBound.first = false;
}

bool UIElement::HitTest(MPF::Visual::Point point, std::vector<UIElement*>& elements) mnoexcept
{
	if (renderBound.second.Contains(point))
	{
		elements.emplace_back(this);
		return true;
	}
	return false;
}

MPF::Visual::Size UIElement::MeasureSize() mnoexcept
{
	if (size.first)UpdateSize();
	return size.second;
}

MPF::Visual::Size UIElement::AutoMeasureSize() mnoexcept
{
	auto padding = Padding;
	auto width = padding.Left + padding.Right;
	auto height = padding.Top + padding.Bottom;

	return{ width, height };
}

std::vector<UIElement*> UIElement::HitTest(MPF::Visual::Point point) mnoexcept
{
	std::vector<UIElement*> elements;

	HitTest(point, elements);
	return elements;
}