#include "stdafx.h"
#include "../include/UncaughtExceptionEventHandler.h"

using namespace MPF;

DEFINE_TYPE(UncaughtExceptionEventHandler, MPF::UncaughtExceptionEventHandler)

UncaughtExceptionEventHandler::UncaughtExceptionEventHandler(std::function<void(bool&)> handler) mnoexcept
:handler(handler)
{

}

void UncaughtExceptionEventHandler::Invoke(bool& isHandled) const
{
	massert(handler != nullptr);

	handler(isHandled);
}

void UncaughtExceptionEventHandler::operator()(bool& isHandled) const
{
	Invoke(isHandled);
}