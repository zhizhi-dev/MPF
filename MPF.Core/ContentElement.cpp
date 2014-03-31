#include "stdafx.h"
#include "../include/ui/ContentElement.h"

using namespace MPF;
using namespace MPF::UI;

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
		content->Render(renderer, RenderArgs{ content->MeasureBound() });
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