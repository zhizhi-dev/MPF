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

Window::Window(MPF::Visual::RenderCoreProviders provider)
:provider(provider)
{
}

Window::~Window()
{

}

void Window::CreateNativeWindow()
{
	nativeWindow = std::make_unique<NativeWindow>();
	nativeWindow->Create();
	nativeWindow->SetTitle(Title);
	nativeWindow->SetWidth(Width);
	nativeWindow->SetHeight(Height);
	renderer = nativeWindow->CreateRenderCoreProvider(provider);
	InitializeNativeWindowEventHandlers();
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
	if (!nativeWindow) CreateNativeWindow();
	massert(nativeWindow);
	nativeWindow->Show();
}

void Window::DoFrame()
{
	massert(renderer);
	auto& renderRef = *renderer;

	Update(renderRef, UpdateArgs{});

	renderRef.BeginDraw();
	Render(renderRef, RenderArgs{ 1.f });
	renderRef.EndDraw();

	renderRef.Present();
}

void Window::UpdateRelativeOffset() noexcept
{
	relativeOffset.second = Point();
	relativeOffset.first = false;
}

void Window::InitializeNativeWindowEventHandlers()
{
	auto window = nativeWindow.get();

	auto mouseEventHandler = [=](NativeMouseEventArgs& e)
	{
		auto hit = HitTest(e.Position);
		massert(hit.size());
		MouseEventArgs args(hit.back(), hit.front(), e.Position);
		RaiseEvent(MouseLeftButtonUpEvent, args);
	};

	window->MouseLeftButtonUp += mouseEventHandler;
}

void Window::UpdateRenderBound(MPF::Visual::Point parentOffset) noexcept
{
	auto offset = relativeOffset.second + parentOffset;
	
	renderBound.second = Quad(Point(offset.X, offset.Y), Point(offset.X + renderer->GetBackBufferWidth(),
		offset.Y + renderer->GetBackBufferHeight(), 1.f, 1.f));
	renderBound.first = false;
}