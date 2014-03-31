#include "stdafx.h"
#include "../include/ui/Panel.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(Panel, MPF::UI::Panel)
DEFINE_UI_VALUES(Panel)
DEFINE_UI_FUNCS(Panel, UIElement)

DependencyProperty<std::vector<std::weak_ptr<UIElement>>> Panel::ChildrenProperty(std::make_shared<String>(L"Children"), std::vector<std::weak_ptr<UIElement>>());

Panel::Panel()
{

}

Panel::~Panel()
{
	GetChildren().clear();
}

const std::vector<std::weak_ptr<UIElement>>& Panel::GetChildren() const
{
	return GetValue(ChildrenProperty);
}

std::vector<std::weak_ptr<UIElement>>& Panel::GetChildren()
{
	return GetValue(ChildrenProperty);
}

void Panel::RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{
	auto children = GetChildren();
	for (auto child : children)
	{
		auto content = child.lock();
		if (content)
		{
			content->Render(renderer, RenderArgs{ content->MeasureBound() });
		}
	}

	UIElement::RenderCore(renderer, std::move(args));
}

void Panel::UpdateCore(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime)
{
	auto children = GetChildren();
	for (auto child : children)
	{
		auto content = child.lock();
		if (content)
		{
			content->Update(renderer, elapsedTime);
		}
	}

	UIElement::UpdateCore(renderer, elapsedTime);
}