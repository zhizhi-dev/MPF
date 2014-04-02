#pragma once
#include "Type.h"
#include "String.h"
#include "Event.h"

NS_MPF

class Thread;

//线程启动参数
struct ThreadStartParameter
{
	Thread* thread;
	void* param;

	ThreadStartParameter(Thread* thread, void* param)
		:thread(thread), param(param)
	{

	}
};

//线程
class Thread : public Object
{
public:
	//创建 Thread 的新实例
	MPF_API Thread(std::function<void(void*)> startup);

	//销毁 Thread 实例
	MPF_API ~Thread();

	Thread(Thread&) = delete;

	//运行
	MPF_API void Start(void* param = nullptr);
	//挂起
	MPF_API void Suspend();
	//继续
	MPF_API void Resume();
	//停止
	MPF_API void Abort();

	//未捕获异常
	Event<UncaughtExceptionEventHandler> UncaughtException;

	//获取类型
	MPF_API DECLARE_GETTYPE(Thread)
protected:
	MPF_API void OnUncaughtException(bool& isHandled) const;
private:
	static dword_t _stdcall Invoke(void* startParam);
private:
	std::function<void(void*)> startup;
	std::shared_ptr<ThreadStartParameter> startParam;
	handle_t handle = nullptr;
	//线程 Id
	dword_t threadId = 0;
	bool isSuspend = false;
	DECLARE_TYPE(Thread)
};

NS_ED