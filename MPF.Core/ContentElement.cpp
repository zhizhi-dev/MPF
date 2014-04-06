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
	if (value)
	{
		SetParent(*value, this);
	}
}

void ContentElement::RenderCore(MPF::Visual::RenderCoreProvider& renderer, RenderArgs&& args)
{
	auto background = Background;
	if (background)
	{
		renderer.FillQuad(renderBound.second, *background);
	}

	auto content = Content;
	if (content)
	{
		content->Render(renderer, RenderArgs{ args.ElapsedTime });

		UIElement::RenderCore(renderer, std::move(args));
	}
	else
	{
		TextBlock::RenderCore(renderer, std::move(args));
	}
}

void ContentElement::UpdateCore(MPF::Visual::RenderCoreProvider& renderer, UpdateArgs&& args)
{
	auto content = Content;
	if (content)
	{
		UIElement::UpdateCore(renderer, std::move(args));
		auto offset = args.ParentOffset + MakeContentOffset(*content) + relativeOffset.second;
		content->Update(renderer, { offset, args.ElapsedTime });
	}
	else
	{
		TextBlock::UpdateCore(renderer, std::move(args));
	}
}

MPF::Visual::Point ContentElement::MakeContentOffset(UIElement& elem)
{
	auto padding = Padding;
	return Point(padding.Left, padding.Top);
}

const MPF::Visual::Brush* ContentElement::GetBackground() const
{
	return GetValue(BackgroundProperty);
}

void ContentElement::SetBackground(const MPF::Visual::Brush* value)
{
	SetValue(BackgroundProperty, value);
}

MPF::Visual::Size ContentElement::AutoMeasureSize() mnoexcept
{
	//根据内容计算大小
	auto content = Content;
	if (content)
	{
		auto size = UIElement::AutoMeasureSize();
		auto& contentSize = content->MeasureSize();

		size.Width += contentSize.Width;
		size.Height += contentSize.Height;
		return size;
	}
	else
	{
		return TextBlock::AutoMeasureSize();
	}
}

bool ContentElement::HitTest(MPF::Visual::Point point, std::vector<UIElement*>& elements) mnoexcept
{
	auto hitted = UIElement::HitTest(point, elements);

	if (hitted)
	{
		auto content = Content;
		if (content)
		{
			content->HitTest(point, elements);
		}
		return true;
	}
	return false;
}