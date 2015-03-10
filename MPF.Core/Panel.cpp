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

}

const std::vector<UIElement*>& Panel::GetChildren() const
{
	return children;
}

std::vector<UIElement*>& Panel::GetChildren()
{
	return children;
}

void Panel::RenderCore(MPF::Visual::RenderCoreProvider& renderer, const RenderArgs& args)
{
	for (auto child : children)
	{
		massert(child != nullptr);
		child->Render(renderer, args);
	}

	UIElement::RenderCore(renderer, args);
}

MPF::Visual::Point Panel::MakeChildOffset(UIElement& elem)
{
	return Point();
}

void Panel::UpdateCore(MPF::Visual::RenderCoreProvider& renderer, const UpdateArgs& args)
{
	UIElement::UpdateCore(renderer, args);

	for (auto child : children)
	{
		massert(child != nullptr);
		auto offset = args.ParentOffset + MakeChildOffset(*child) + relativeOffset.second;
		child->Update(renderer, UpdateArgs{ offset, args.ElapsedTime });
	}
}

void Panel::AddChild(UIElement& elem)
{
	children.emplace_back(&elem);
	SetParent(elem, this);
}

bool Panel::HitTest(MPF::Visual::Point point, std::vector<UIElement*>& elements) noexcept
{
	if (UIElement::HitTest(point, elements))
	{
		for (auto child : children)
		{
			massert(child);
			if (child->HitTest(point, elements))
				return true;
		}
	}
	return false;
}

MPF::Visual::Size Panel::AutoMeasureSize() noexcept
{
	//根据内容计算大小
	Size size = UIElement::AutoMeasureSize();
	for (auto child : children)
	{
		massert(child);
		
	}
	return{ 800, 600 };
}