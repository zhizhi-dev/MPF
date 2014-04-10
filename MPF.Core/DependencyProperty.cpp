#include "stdafx.h"
#include "../include/DependencyProperty.h"
#include "../include/ui/Border.h"
#include "../include/ui/Button.h"
#include "../include/visual/SolidColorBrush.h"
#include "../include/ui/ControlTemplate.h"
#include "../include/ui/Window.h"
#include "../include/input/InputEventHandlers.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;
using namespace MPF::Input;

DEFINE_UI_VALUES(UIElement)
DEFINE_UI_VALUES(TextBlock)
DependencyProperty<float> UIElement::WidthProperty(L"Width", NAN);
DependencyProperty<float> UIElement::HeightProperty(L"Height", NAN);
DependencyProperty<Visibility> UIElement::VisibilityProperty(L"Visibility", Visibility::Visible);
DependencyProperty<Thickness> UIElement::MarginProperty(L"Margin");
DependencyProperty<Thickness> UIElement::PaddingProperty(L"Padding");
DependencyProperty<ControlTemplate*> UIElement::TemplateProperty(L"Template");
DependencyProperty<const MPF::Visual::Brush*> Border::BorderBrushProperty(L"BorderBrush");
DependencyProperty<MPF::Visual::Thickness> Border::BorderThicknessProperty(L"BorderThickness");
DependencyProperty<MPF::String> Window::TitleProperty(L"Title", String::GetEmpty());
RoutedEvent<MouseEventHandler> UIElement::MouseLeftButtonUpEvent(L"MouseLeftButtonUp", RoutedEventMode::Bubble);

SolidColorBrush defaultForegroundBrush(0xFF000000);
DependencyProperty<MPF::String> TextBlock::TextProperty(L"Text", String::GetEmpty());
DependencyProperty<MPF::Visual::Font> TextBlock::FontProperty(L"Font", MPF::Visual::Font(L"Microsoft YaHei", 15.f));
DependencyProperty<const MPF::Visual::Brush*> TextBlock::ForegroundProperty(L"Foreground", &defaultForegroundBrush);

struct ButtonInitializer
{
	ButtonInitializer()
		:borderBrush(0xFFACACAC), backBrush(0xFFECECEC), templ(border)
	{
		text.Text = L"Œ“ «∞¥≈•";
		border.BorderThickness = 1;
		border.BorderBrush = &borderBrush;
		border.Background = &backBrush;
		border.Content = &text;
		border.Padding = 5.f;

		Button::SetCommonStyleValue(UIElement::TemplateProperty, &templ);
	}

	Border border;
	TextBlock text;
	SolidColorBrush borderBrush;
	SolidColorBrush backBrush;
	ControlTemplate templ;
} buttonInit;