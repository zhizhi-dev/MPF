#include "stdafx.h"
#include "NativeWindow.h"
#include "../include/Application.h"
#include "GDI/GDIRenderCoreProvider.h"

using namespace MPF;
using namespace MPF::Visual;

const wchar_t MPFWindowClassName[] = L"MPF_Window_Wrapper";
const wchar_t MPFWindowHandlePropName[] = L"MPF_Window_Handle";

NativeWindow::NativeWindow()
{
	CreateWindowClass();
}

NativeWindow::~NativeWindow()
{
	if (hWnd)
	{
		DestroyWindow(hWnd);
		hWnd = nullptr;
	}
}

void NativeWindow::CreateWindowClass()
{
	static bool isSucceed = false;
	if (!isSucceed)
	{
		WNDCLASSEX wndCls = { 0 };

		wndCls.cbSize = sizeof(wndCls);
		wndCls.hInstance = (HINSTANCE)Application::GetCurrent().GetNativeHandle();
		wndCls.style = CS_HREDRAW | CS_VREDRAW;
		wndCls.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndCls.lpszClassName = MPFWindowClassName;
		wndCls.lpfnWndProc = (WNDPROC)WindowProcWrapper;

		isSucceed = RegisterClassEx(&wndCls) != 0;
	}
	massert(isSucceed);
}

LRESULT CALLBACK NativeWindow::WindowProcWrapper(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto window = (NativeWindow*)GetProp(hWnd, MPFWindowHandlePropName);

	if (uMsg == WM_NCCREATE)
	{
		//»ñÈ¡ this
		auto createParam = (LPCREATESTRUCT)lParam;
		window = (NativeWindow*)createParam->lpCreateParams;
		SetProp(hWnd, MPFWindowHandlePropName, window);
	}

	if (window)
	{
		return window->WindowProc(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK NativeWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		OnPaint();
		break;
	case WM_LBUTTONUP:
		OnMouseClick();
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void NativeWindow::Create()
{
	hWnd = CreateWindowEx(0, MPFWindowClassName, String::GetEmpty().GetDataPointer(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		nullptr, nullptr, (HINSTANCE)Application::GetCurrent().GetNativeHandle(), this);

	massert(hWnd != nullptr);
}

void NativeWindow::Show() const
{
	ShowWindow(hWnd, SW_SHOW);
}

String NativeWindow::GetTitle() const
{
	auto len = GetWindowTextLength(hWnd);
	auto text = new wchar_t[len + 1];
	GetWindowText(hWnd, text, len);

	return String(text, true);
}

void NativeWindow::SetTitle(const String& title)
{
	SetWindowText(hWnd, title.GetDataPointer());
}

uint NativeWindow::GetWidth() const
{
	RECT rect;
	GetWindowRect(hWnd, &rect);

	return rect.right - rect.left;
}

void NativeWindow::SetWidth(uint width)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, nullptr, rect.left, rect.top, width, rect.bottom - rect.top, NULL);
}

uint NativeWindow::GetHeight() const
{
	RECT rect;
	GetWindowRect(hWnd, &rect);

	return rect.bottom - rect.top;
}

void NativeWindow::SetHeight(uint height)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, nullptr, rect.left, rect.top, rect.right - rect.left, height, NULL);
}

handle_t NativeWindow::GetNativeHandle() const
{
	return hWnd;
}

std::unique_ptr<RenderCoreProvider> NativeWindow::CreateRenderCoreProvider(RenderCoreProviders provider)
{
	std::unique_ptr<RenderCoreProvider> render = nullptr;

	switch (provider)
	{
	case MPF::Visual::RenderCoreProviders::GDI:
		render = std::make_unique<GDI::GDIRenderCoreProvider>(*this);
		break;
	default:
		break;
	}
	return render;
}

uint NativeWindow::GetClientWidth() const
{
	RECT rect;

	GetClientRect(hWnd, &rect);
	return rect.right - rect.left;
}

uint NativeWindow::GetClientHeight() const
{
	RECT rect;

	GetClientRect(hWnd, &rect);
	return rect.bottom - rect.top;
}

void NativeWindow::OnPaint() const
{
	Paint([&](PaintEventHandler handler)
	{
		handler();
	});
}

void NativeWindow::OnMouseClick() const
{
	MouseClick([&](MouseEventHandler handler)
	{
		handler();
	});
}