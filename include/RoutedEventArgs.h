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

	MPF::UI::UIElement* GetSource() const noexcept{ return source; }
	MPF::UI::UIElement* GetDestination() const noexcept{ return destination; }

	bool GetHandled() const noexcept{ return handled; }
	void SetHandled(bool handled) noexcept{ this->handled = handled; }
	mproperty(bool, Handled);
private:
	MPF::UI::UIElement* source;
	MPF::UI::UIElement* destination;
	//标志事件已被处理
	bool handled;
};

NS_ED