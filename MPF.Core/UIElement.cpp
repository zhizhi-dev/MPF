#include "stdafx.h"
#include "../include/ui/UIElement.h"
#include "../include/Enumerable.h"
#include <stack>

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;
using namespace MPF::Input;

DEFINE_TYPE(UIElement, MPF::UI::UIElement)
DEFINE_UI_FUNCS(UIElement, DependencyObject)

UIElement::UIElement()
{
	InitializeEventHandlers();
}

UIElement::~UIElement()
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
		if (templateRoot)
		{
			templateRoot->Render(renderer, std::move(args));
		}
		else
		{
			RenderCore(renderer, std::move(args));
		}
	}
}

void UIElement::RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{
}

void UIElement::Update(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args)
{
	auto templ = Template;
	if (templ)
	{
		if (!templateInst) templateInst = templ(this);
		if (!templateRoot) templateRoot = templateInst->GetRoot();
		templateRoot->Update(renderer, std::move(args));
		relativeOffset = templateRoot->relativeOffset;
		size = templateRoot->size;
		renderBound = templateRoot->renderBound;
	}
	else
	{
		UpdateCore(renderer, std::move(args));
	}
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

MPF::Visual::Quad UIElement::GetRenderBound() const mnoexcept
{
	return renderBound.second;
}

void UIElement::InitializeEventHandlers()
{
	DEFINE_COMMON_ROUTEDEVENT(MouseLeftButtonUp, MouseEventArgs);
	DEFINE_ROUTED_EVENTWRAPPER(MouseLeftButtonUp, UIElement);
}

void UIElement::OnMouseLeftButtonUp(MPF::Input::MouseEventArgs& args)
{
}

void UIElement::SetParent(UIElement& element, UIElement* parent) mnoexcept
{
	element.parent = parent;
}

void UIElement::RaiseEventInternal(const IRoutedEvent& ent, RoutedEventArgs& args)
{
	massert(args.GetDestination() && args.GetSource());
	//自顶向下
	if (ent.GetMode() == RoutedEventMode::Tunnel)
	{
		//建立传递栈
		std::stack<UIElement*> uiList;
		auto end = args.GetDestination();
		while (true)
		{
			uiList.emplace(end);
			if (end == args.GetSource()) break;
			end = end->parent;
		}
		//开始引发事件
		while (!args.Handled && !uiList.empty())
		{
			auto elem = uiList.top();
			DoEvent(*elem, ent, args);
			uiList.pop();
		}
	}
	//自底向上
	if (ent.GetMode() == RoutedEventMode::Bubble)
	{
		for (UIElement* elem = args.GetSource(); !args.Handled; elem = elem->parent)
		{
			DoEvent(*elem, ent, args);
			if (elem == args.GetDestination()) break;
		}
	}
}

ControlTemplate UIElement::GetTemplate() const
{
	return GetValue(TemplateProperty);
}

void UIElement::SetTemplate(ControlTemplate&& value)
{
	SetValue(TemplateProperty, std::move(value));
}