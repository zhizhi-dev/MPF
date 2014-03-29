#include "stdafx.h"
#include "../include/Object.h"
#include "../include/Type.h"

using namespace MPF;

DEFINE_TYPE(Object, MPF::Object)

Object::Object()
{

}

uint Object::GetHashCode() const mnoexcept
{
	return (uint)this;
}