#pragma once
#include "../Type.h"
#include "../Binding.h"

NS_MPF
NS_UI

class UIElement;

class TemplateInstance
{
public:
	TemplateInstance(){}
	virtual ~TemplateInstance(){};

	virtual UIElement* GetRoot() = 0;
};

//¿Ø¼þÄ£°å
using ControlTemplate = std::function<std::unique_ptr<TemplateInstance>(UIElement*)>;

static bool operator!=(const ControlTemplate& left, const ControlTemplate& right) noexcept
{
	return false;
}

NS_ED
NS_ED