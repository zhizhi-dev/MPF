#include "stdafx.h"
#include "../include/Type.h"

using namespace MPF;

DEFINE_TYPE(Type, MPF::Type)

Type::Type(const String& typeName)
:typeName(typeName)
{

}

bool Type::Equals(const Type& type) const
{
	return this->typeName== type.typeName;
}