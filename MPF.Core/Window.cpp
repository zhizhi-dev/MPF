#include "stdafx.h"
#include "../include/ui/Window.h"
#include "../include/visual/Font.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(Window, MPF::UI::Window)
DEFINE_UI_VALUES(Window)
DEFINE_UI_FUNCS(Window, ContentElement)

DependencyProperty<MPF::String> Window::TitleProperty(L"Title", String::GetEmpty());

Window::Window()
{
}

Window::~Window()
{
	
}

void Window::Initialize(RenderCoreProviders provider)
{
	if (nativeWindow == nullptr)
	{
		nativeWindow = std::make_shared<NativeWindow>();
		nativeWindow->Create();
		nativeWindow->SetTitle(Title);
		nativeWindow->SetWidth(Width);
		nativeWindow->SetHeight(Height);
		renderer = nativeWindow->CreateRenderCoreProvider(provider);
	}

	ContentElement::Initialize();
}

const MPF::String& Window::GetTitle() const
{
	return GetValue(TitleProperty);
}

void Window::SetTitle(const MPF::String& value)
{
	SetValue(TitleProperty, value);
}

void Window::SetTitle(MPF::String&& value)
{
	SetValue(TitleProperty, std::move(value));
}

void Window::Show()
{
	if (nativeWindow)
	{
		nativeWindow->Show();
	}
}

void Window::DoFrame()
{
	auto& renderRef = *renderer;

	Update(renderRef, 1.0);

	renderRef.BeginDraw();
	Render(renderRef, RenderArgs{ MeasureBound() });
	renderRef.EndDraw();

	renderRef.Present();
}