#include "stdafx.h"
#include "../include/ui/Panel.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(Panel, MPF::UI::Panel)
DEFINE_UI_VALUES(Panel)
DEFINE_UI_FUNCS(Panel, UIElement)

Panel::Panel()
{

}

Panel::~Panel()
{
	GetChildren().clear();
}

const std::vector<UIElement*>& Panel::GetChildren() const
{
	return children;
}

std::vector<UIElement*>& Panel::GetChildren()
{
	return children;
}

void Panel::RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{
	for (auto child : children)
	{
		massert(child != nullptr);
		child->Render(renderer, RenderArgs{ args.ElapsedTime });
	}

	UIElement::RenderCore(renderer, std::move(args));
}

MPF::Visual::Point Panel::MakeChildOffset(UIElement& elem)
{
	return Point();
}

void Panel::UpdateCore(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args)
{
	UIElement::UpdateCore(renderer, std::move(args));

	for (auto child : children)
	{
		massert(child != nullptr);
		auto offset = args.ParentOffset + MakeChildOffset(*child) + relativeOffset.second;
		child->Update(renderer, UpdateArgs{ offset });
	}
}

void Panel::AddChild(UIElement& elem)
{
	children.emplace_back(&elem);
	SetParent(elem, this);
}

void Panel::AddChildren(std::initializer_list<std::reference_wrapper<UIElement>> elems)
{
	children.reserve(children.size() + elems.size());
	for (auto elem : elems)
	{
		AddChild(elem);
	}
}

bool Panel::HitTest(MPF::Visual::Point point, std::vector<UIElement*>& elements) mnoexcept
{
	if (UIElement::HitTest(point, elements))
	{
		for (auto child : children)
		{
			massert(child);
			if (child->HitTest(point, elements))
			{
				break;
			}
		}
		return true;
	}
	return false;
}

MPF::Visual::Size Panel::AutoMeasureSize() mnoexcept
{
	//根据内容计算大小
	Size size = UIElement::AutoMeasureSize();
	for (auto child : children)
	{
		massert(child);
		
	}
	return{ 800, 600 };
}