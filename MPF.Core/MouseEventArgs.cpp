#include "stdafx.h"
#include "../include/input/MouseEventArgs.h"
#include "../include/ui/UIElement.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;
using namespace MPF::Input;

MPF::Visual::Point MouseEventArgs::GetPosition(const UIElement& element) const noexcept
{
	return position - element.GetRenderBound().PointA;
}