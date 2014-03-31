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