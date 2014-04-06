#pragma once
#include "core.h"

NS_MPF
NS_UI
class UIElement;
NS_ED

class RoutedEventArgs
{
public:
	RoutedEventArgs(MPF::UI::UIElement* source, MPF::UI::UIElement* destination)
		:source(source), destination(destination), handled(false)
	{

	}

	MPF::UI::UIElement* GetSource() const mnoexcept{ return source; }
	MPF::UI::UIElement* GetDestination() const mnoexcept{ return destination; }

	bool GetHandled() const mnoexcept{ return handled; }
	void SetHandled(bool handled) mnoexcept{ this->handled = handled; }
	mproperty(bool, Handled);
private:
	MPF::UI::UIElement* source;
	MPF::UI::UIElement* destination;
	//标志事件已被处理
	bool handled;
};

NS_ED