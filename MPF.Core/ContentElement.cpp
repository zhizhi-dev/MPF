#include "stdafx.h"
#include "../include/ui/ContentElement.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(ContentElement, MPF::UI::ContentElement)
DEFINE_UI_VALUES(ContentElement)
DEFINE_UI_FUNCS(ContentElement, TextBlock)

DependencyProperty<UIElement*> ContentElement::ContentProperty(L"Content");
DependencyProperty<const MPF::Visual::Brush*> ContentElement::BackgroundProperty(L"Background");

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
	auto background = Background;
	if (background)
	{
		renderer.FillQuad(args.RenderQuad, *background);
	}

	auto content = Content;
	if (content)
	{
		auto padding = Padding;
		auto bound = MeasureContentBound(*content);
		bound.Transpose({ padding.Left + args.RenderQuad.PointA.X, padding.Top + args.RenderQuad.PointA.Y });
		content->Render(renderer, RenderArgs{ bound });

		UIElement::RenderCore(renderer, std::move(args));
	}
	else
	{
		TextBlock::RenderCore(renderer, std::move(args));
	}
}

void ContentElement::UpdateCore(MPF::Visual::RenderCoreProvider& renderer, float elapsedTime)
{
	auto content = Content;
	if (content)
	{
		content->Update(renderer, elapsedTime);
		UIElement::UpdateCore(renderer, elapsedTime);
	}
	else
	{
		TextBlock::UpdateCore(renderer, elapsedTime);
	}
}

MPF::Visual::Quad ContentElement::MeasureContentBound(UIElement& elem)
{
	return elem.MeasureBound();
}

MPF::Visual::Size ContentElement::MeasureSize()
{
	//根据内容计算大小
	auto content = Content;
	if (content)
	{
		auto size = UIElement::MeasureSize();

		auto quad = content->MeasureSize();
		size.Width += quad.Width;
		size.Height += quad.Height;

		//没有内容则返回边框大小
		return size;
	}
	else
	{
		return TextBlock::MeasureSize();
	}
}

const MPF::Visual::Brush* ContentElement::GetBackground() const
{
	return GetValue(BackgroundProperty);
}

void ContentElement::SetBackground(const MPF::Visual::Brush* value)
{
	SetValue(BackgroundProperty, value);
}