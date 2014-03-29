#include "stdafx.h"
#include "../include/ui/Window.h"
#include "../include/visual/Font.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

DEFINE_TYPE(Window, MPF::UI::Window)
DEFINE_UI_VALUES(Window)
DEFINE_UI_FUNCS(Window, ContentElement)

DependencyProperty<std::shared_ptr<MPF::String>> Window::TitlePropery(std::make_shared<String>(L"Title"), String::GetEmpty());

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

std::shared_ptr<MPF::String> Window::GetTitle() const
{
	return GetValue(TitlePropery);
}

void Window::SetTitle(std::shared_ptr<MPF::String> value)
{
	SetValue(TitlePropery, value);
}

void Window::Show()
{
	if (nativeWindow)
	{
		nativeWindow->Show();
	}
}