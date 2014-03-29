#include "stdafx.h"
#include "../include/Type.h"

using namespace MPF;

DEFINE_TYPE(Type, MPF::Type)

Type::Type(const std::shared_ptr<String> typeName)
:typeName(typeName)
{

}

bool Type::Equals(const std::shared_ptr<Type> type) const
{
	return this->typeName->GetDataPointer() == type->typeName->GetDataPointer();
}