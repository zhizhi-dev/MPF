#include "stdafx.h"
#include "../include/threading/Thread.h"
#include "../include/raii.h"
#include <iostream>

using namespace MPF;
using namespace MPF::Threading;

DEFINE_TYPE(Thread, MPF::Threading::Thread)

Thread::Thread(std::function<void(void*)> startup)
:startup(startup)
{
}

Thread::~Thread()
{
	if (handle)
	{
		TerminateThread(handle, -1);
		handle = nullptr;
	}
}

void Thread::Start(void* param)
{
	startParam = std::make_shared<ThreadStartParameter>(this, param);
	
	handle = CreateThread(nullptr, 0, Thread::Invoke, startParam.get(), 0, &threadId);
	massert(handle != nullptr);
}

void Thread::Suspend()
{
	if (!isSuspend)
	{
		isSuspend = SuspendThread(handle) != (DWORD)-1;
		massert(isSuspend);
	}
}

void Thread::Resume()
{
	if (isSuspend)
	{
		isSuspend = ResumeThread(handle) != (DWORD)-1;
		massert(!isSuspend);
	}
}

void Thread::Abort()
{
	if (handle)
	{
		auto r = TerminateThread(handle, -1);
		massert(r == 0);
		handle = nullptr;
	}
}

dword_t _stdcall Thread::Invoke(void* startParam)
{
	if (auto param = (ThreadStartParameter*)startParam)
	{
		auto& handle = param->thread->handle;
		//线程结束
		AtFinally([&]{ handle = nullptr; });

		try
		{
			param->thread->startup(param->param);
		}
		catch (...)
		{
			bool handled = false;
			param->thread->OnUncaughtException(handled);
			//异常未处理
			if (!handled)
			{
				throw;
			}
		}
	}

	return 0;
}

void Thread::OnUncaughtException(bool& isHandled) const
{
	UncaughtException([&](UncaughtExceptionEventHandler handler)
	{
		handler(isHandled);
	});
}