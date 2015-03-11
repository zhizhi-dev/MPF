#pragma once
#include "../include/Type.h"
#include "../include/Event.h"
#include "../include/visual/RenderCoreProviders.h"
#include "NativeEvents.h"
#include <windef.h>

NS_MPF
NS_VSL

class RenderCoreProvider;

//系统窗口
class NativeWindow
{
public:
	//创建 NativeWindow 的新实例
	NativeWindow();
	~NativeWindow();

	//创建
	void Create();
	//显示
	void Show() const;

	//获取标题
	String GetTitle() const;
	//设置标题
	void SetTitle(const String& title);

	//获取宽度
	uint32_t GetWidth() const;
	//设置宽度
	void SetWidth(uint32_t width);

	//获取高度
	uint32_t GetHeight() const;
	//设置高度
	void SetHeight(uint32_t height);

	//获取客户区宽度
	uint32_t GetClientWidth() const;

	//获取客户区高度
	uint32_t GetClientHeight() const;

	//获取本机标识符
	handle_t GetNativeHandle() const;

	//创建 RenderCoreProvider
	std::unique_ptr<RenderCoreProvider> CreateRenderCoreProvider(RenderCoreProviders provider);

	// 绘制事件
	Event<PaintEventHandler> Paint;
	// 鼠标左键释放点击事件
	Event<MPF::Input::NativeMouseEventHandler> MouseLeftButtonUp;
	// 鼠标左键按下点击事件
	Event<MPF::Input::NativeMouseEventHandler> MouseLeftButtonDown;
private:
	//窗口过程
	LRESULT CALLBACK WindowProc(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnPaint() const;
	LRESULT OnMouseLeftButtonUp(WPARAM wParam, LPARAM lParam) const;
	LRESULT OnMouseLeftButtonDown(WPARAM wParam, LPARAM lParam) const;
private:
	static void CreateWindowClass();
	static LRESULT CALLBACK WindowProcWrapper(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
private:
	HWND hWnd = nullptr;
};

NS_ED
NS_ED