#pragma once
#include "../Type.h"
#include "../Event.h"
#include "PaintEventHandler.h"

NS_MPF
NS_VSL

class RenderCoreProvider;

enum class RenderCoreProviders
{
	//GDI
	GDI
};

//系统窗口
class NativeWindow : public Object
{
public:
	//创建 NativeWindow 的新实例
	MPF_API NativeWindow();
	MPF_API ~NativeWindow();

	//创建
	MPF_API void Create();
	//显示
	MPF_API void Show() const;

	//获取标题
	MPF_API String GetTitle() const;
	//设置标题
	MPF_API void SetTitle(const String& title);

	//获取宽度
	MPF_API uint GetWidth() const;
	//设置宽度
	MPF_API void SetWidth(uint width);

	//获取高度
	MPF_API uint GetHeight() const;
	//设置高度
	MPF_API void SetHeight(uint height);

	//获取客户区宽度
	MPF_API uint GetClientWidth() const;

	//获取客户区高度
	MPF_API uint GetClientHeight() const;

	//获取本机标识符
	MPF_API handle_t GetNativeHandle() const;

	//创建 RenderCoreProvider
	MPF_API std::unique_ptr<RenderCoreProvider> CreateRenderCoreProvider(RenderCoreProviders provider);

	//绘制事件
	Event<PaintEventHandler> Paint;

	//获取类型
	MPF_API DECLARE_GETTYPE(NativeWindow)
protected:
	//窗口过程
	MPF_API long _w64 _stdcall WindowProc(handle_t handle, uint msg, uint _w64 wParam, long _w64 lParam);
	MPF_API void OnPaint() const;
private:
	static void CreateWindowClass();
	static long _w64 _stdcall WindowProcWrapper(handle_t hWnd, uint msg, uint _w64 wParam, long _w64 lParam);
private:
	handle_t handle = nullptr;
	DECLARE_TYPE(NativeWindow)
};

NS_ED
NS_ED