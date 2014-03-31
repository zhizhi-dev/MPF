#include "stdafx.h"
#include "../include/ui/Canvas.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;

DEFINE_TYPE(Canvas, MPF::UI::Canvas)
DEFINE_UI_VALUES(Canvas)
DEFINE_UI_FUNCS(Canvas, Panel)

DependencyProperty<float> Canvas::LeftProperty(std::make_shared<String>(L"Left"));
DependencyProperty<float> Canvas::TopProperty(std::make_shared<String>(L"Top"));

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
		auto content = child.lock();
		if (content)
		{
			auto& childRef = *content;

			auto bound = childRef.MeasureBound();
			auto left = childRef.GetValue(LeftProperty);
			auto top = childRef.GetValue(TopProperty);
			bound.Transform([&](Point& pt)
			{
				pt.X += left;
				pt.Y += top;
			});
			childRef.Render(renderer, RenderArgs{ bound });
		}
	}

	UIElement::RenderCore(renderer, std::move(args));
}