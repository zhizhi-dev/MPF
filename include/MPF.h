#pragma once

//Core
#include "common.h"
#include "datatypes.h"
#include "any.h"
#include "raii.h"
#include "Enumerable.h"
#include "core.h"
#include "Object.h"
#include "Type.h"
#include "String.h"
#include "Array.h"
#include "Application.h"
#include "threading/Thread.h"
#include "DependencyProperty.h"
#include "RoutedEvent.h"
#include "EventWrapper.h"
#include "DependencyObject.h"

//Visual
#include "visual/Visual.h"
#include "visual/Size.h"
#include "visual/Thickness.h"
#include "visual/Point.h"
#include "visual/DPIHelper.h"
#include "visual/geometry.h"
#include "visual/line.h"
#include "visual/Triangle.h"
#include "visual/Quad.h"
#include "visual/Font.h"
#include "visual/BitmapData.h"
#include "visual/Brush.h"
#include "visual/SolidColorBrush.h"
#include "visual/LinearGradientBrush.h"
#include "visual/ImageBrush.h"
#include "visual/AlphaBlendBrush.h"
#include "visual/RenderCoreProvider.h"

//Input
#include "input/MouseButtons.h"
#include "input/MouseEventArgs.h"
#include "input/InputEventHandlers.h"

//UI
#include "ui/Visibility.h"
#include "ui/UIElement.h"
#include "ui/ControlTemplate.h"
#include "ui/TextBlock.h"
#include "ui/ContentElement.h"
#include "ui/Border.h"
#include "ui/Window.h"
#include "ui/Panel.h"
#include "ui/Canvas.h"
#include "ui/ButtonBase.h"
#include "ui/Button.h"
#include "ui/MessageBox.h"

void _stdcall MPFMain();