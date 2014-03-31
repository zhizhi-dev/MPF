#include "stdafx.h"
#include "../include/ui/Canvas.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;

DEFINE_TYPE(Canvas, MPF::UI::Canvas)
DEFINE_UI_VALUES(Canvas)
DEFINE_UI_FUNCS(Canvas, Panel)

DependencyProperty<float> Canvas::LeftProperty(L"Left");
DependencyProperty<float> Canvas::TopProperty(L"Top");

Canvas::Canvas()
{

}

Canvas::~Canvas()
{

}

void Canvas::RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{
	auto children = GetChildren();
	for (auto child : children)
	{
		massert(child != nullptr);

		auto bound = child->MeasureBound();
		auto left = child->GetValue(LeftProperty);
		auto top = child->GetValue(TopProperty);
		bound.Transform([&](Point& pt)
		{
			pt.X += left;
			pt.Y += top;
		});
		child->Render(renderer, RenderArgs{ bound });
	}

	UIElement::RenderCore(renderer, std::move(args));
}

float Canvas::GetLeft(const UIElement& elem)
{
	return elem.GetValue(LeftProperty);
}

void Canvas::SetLeft(UIElement& elem, float value)
{
	elem.SetValue(LeftProperty, value);
}

float Canvas::GetTop(const UIElement& elem)
{
	return elem.GetValue(TopProperty);
}

void Canvas::SetTop(UIElement& elem, float value)
{
	elem.SetValue(TopProperty, value);
}

std::pair<float, float> Canvas::GetPosition(const UIElement& elem)
{
	return std::make_pair(GetLeft(elem), GetTop(elem));
}

void Canvas::SetPosition(UIElement& elem, const std::pair<float, float>& position)
{
	SetLeft(elem, position.first);
	SetTop(elem, position.second);
}