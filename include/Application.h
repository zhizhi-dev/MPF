#pragma once
#include "Type.h"
#include "String.h"
#include "Event.h"
#include "UncaughtExceptionEventHandler.h"

NS_MPF

//MPF 程序入口
typedef void(_stdcall*MPFMainHandler)();

//应用程序
class Application : Object
{
public:
	//创建 Application 的新实例
	MPF_API Application();
	Application(const Application& app) = delete;
	const Application& operator=(const Application& app) = delete;

	//运行
	MPF_API void Run(MPFMainHandler handler) const;

	//开始运行
	MPF_API void Run() const;

	//获取应用程序的本机标识符
	MPF_API handle_t GetNativeHandle() const;

	//获取命令行
	MPF_API String GetCommandLines() const;

	//获取当前 Application
	MPF_API static Application& GetCurrent() mnoexcept;

	//未捕获异常
	Event<UncaughtExceptionEventHandler> UncaughtException;

	//获取类型
	MPF_API DECLARE_GETTYPE(Application)
protected:
	MPF_API void OnUncaughtException(bool& isHandled) const;
private:
private:
	DECLARE_TYPE(Application)
};

NS_ED

extern "C" MPF_API int _stdcall MPFStartup(MPF::MPFMainHandler handler);
extern "C" MPF_API int _stdcall MPFConsoleStartup(MPF::MPFMainHandler handler);