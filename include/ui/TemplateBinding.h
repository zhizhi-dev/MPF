#pragma once
#include "../DependencyProperty.h"

NS_MPF
NS_UI

class Binding
{
public:
	Binding(){}
	virtual ~Binding() = 0;
};

template<typename T>
class TemplateBinding : public Binding
{
public:
	TemplateBinding(DependencyProperty<T>& source);
	~TemplateBinding(){}
};

NS_ED
NS_ED