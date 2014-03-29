#include "stdafx.h"
#include "../include/ui/ContentElement.h"

using namespace MPF;
using namespace MPF::UI;

DEFINE_TYPE(ContentElement, MPF::UI::ContentElement)
DEFINE_UI_VALUES(ContentElement)
DEFINE_UI_FUNCS(ContentElement, UIElement)

DependencyProperty<std::weak_ptr<UIElement>> ContentElement::ContentPropery(std::make_shared<String>(L"Content"));

ContentElement::ContentElement()
{

}

ContentElement::~ContentElement()
{

}

std::weak_ptr<UIElement> ContentElement::GetContent() const
{
	return GetValue(ContentPropery);
}

void ContentElement::SetContent(std::weak_ptr<UIElement> value)
{
	SetValue(ContentPropery, value);
}

void ContentElement::RenderCore(MPF::Visual::RenderCoreProvider& renderer)
{
	auto content = Content.lock();
	if (content)
	{
		content->Render(renderer);
	}

	UIElement::RenderCore(renderer);
}