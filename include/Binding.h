#pragma once
#include "any.h"

NS_MPF

class DependencyObject;

//绑定
class Binding
{
public:
	Binding(){}
	virtual ~Binding(){}

	virtual any& GetValue() const = 0;
};

NS_ED