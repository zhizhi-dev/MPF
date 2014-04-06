#include "stdafx.h"
#include "../include/ui/ControlTemplate.h"
#include "../include/ui/UIElement.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;

DEFINE_TYPE(ControlTemplate, MPF::UI::ControlTemplate)

ControlTemplate::ControlTemplate(UIElement& element)
:element(&element)
{

}

ControlTemplate::~ControlTemplate()
{

}

UIElement& ControlTemplate::GetTemplate() const mnoexcept
{
	massert(element);
	return *element;
}

void ControlTemplate::SetTemplate(UIElement& element) mnoexcept
{
	this->element = &element;
}