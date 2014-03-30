#include "stdafx.h"
#include "../include/visual/PaintEventHandler.h"

using namespace MPF;

PaintEventHandler::PaintEventHandler(std::function<void()> handler) mnoexcept
:handler(handler)
{

}

void PaintEventHandler::Invoke() const
{
	massert(handler != nullptr);

	handler();
}

void PaintEventHandler::operator()() const
{
	Invoke();
}