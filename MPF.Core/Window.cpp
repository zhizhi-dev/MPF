#include "stdafx.h"
#include "../include/ui/Window.h"
#include "../include/visual/Font.h"
#include "NativeWindow.h"
#include <sstream>

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;
using namespace MPF::Input;

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
		nativeWindow = std::make_unique<NativeWindow>();
		nativeWindow->Create();
		nativeWindow->SetTitle(Title);
		nativeWindow->SetWidth(Width);
		nativeWindow->SetHeight(Height);
		renderer = nativeWindow->CreateRenderCoreProvider(provider);
		AddEventHandlers();
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

	Update(renderRef, UpdateArgs{});

	renderRef.BeginDraw();
	Render(renderRef, RenderArgs{ 1.f });
	renderRef.EndDraw();

	renderRef.Present();
}

void Window::UpdateRelativeOffset() mnoexcept
{
	relativeOffset.second = Point();
	relativeOffset.first = false;
}

void Window::AddEventHandlers()
{
	auto window = nativeWindow.get();

	window->MouseClick += [=](const MouseEventArgs& e)
	{
		auto pos = e.GetPosition(*this);
		std::wstringstream ss;
		ss << L"Left: " << pos.X << std::endl << L"Top: " << pos.Y;
		MessageBox((HWND)window->GetNativeHandle(), ss.str().c_str(), 
			L"LeftMouseButton Up!", MB_OK | MB_ICONINFORMATION);
	};
}