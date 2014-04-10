#pragma once
#include "../DependencyProperty.h"
#include "../DependencyObject.h"

NS_MPF
NS_UI

template<typename T>
class TemplateBinding
{
public:
	TemplateBinding(DependencyProperty<T>& source)
		:source(source), sourceObj(nullptr)
	{

	}
private:
	DependencyProperty<T>& source;
};

NS_ED
NS_ED