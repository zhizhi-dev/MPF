#include "stdafx.h"
#include "../include/ui/ContentElement.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(ContentElement, MPF::UI::ContentElement)
DEFINE_UI_VALUES(ContentElement)
DEFINE_UI_FUNCS(ContentElement, UIElement)

DependencyProperty<UIElement*> ContentElement::ContentProperty(L"Content");

ContentElement::ContentElement()
{

}

ContentElement::~ContentElement()
{

}

UIElement* ContentElement::GetContent() const
{
	return GetValue(ContentProperty);
}

void ContentElement::SetContent(UIElement* value)
{
	SetValue(ContentProperty, value);
}

void ContentElement::RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{
	auto content = Content;
	if (content)
	{
		auto padding = Padding;
		auto bound = MeasureContentBound(*content);
		bound.Transform([&](Point& pt)
		{
			pt.X += padding.Left + args.RenderQuad.PointA.X;
			pt.Y += padding.Top + args.RenderQuad.PointA.Y;
		});

		content->Render(renderer, RenderArgs{ bound });
	}

	UIElement::RenderCore(renderer, std::move(args));
}

void ContentElement::UpdateCore(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime)
{
	auto content = Content;
	if (content)
	{
		content->Update(renderer, elapsedTime);
	}

	UIElement::UpdateCore(renderer, elapsedTime);
}

MPF::Visual::Quad ContentElement::MeasureContentBound(UIElement& elem)
{
	return elem.MeasureBound();
}

MPF::Visual::Size ContentElement::MeasureSize()
{
	auto size = UIElement::MeasureSize();

	//根据内容计算大小
	auto content = Content;
	if (content)
	{
		auto quad = content->MeasureSize();
		size.Width += quad.Width;
		size.Height += quad.Height;
	}
	//没有内容则返回边框大小
	return size;
}