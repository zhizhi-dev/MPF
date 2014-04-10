#pragma once
#include "../Type.h"
#include "../Binding.h"
#include "TemplateBinding.h"

NS_MPF
NS_UI

class UIElement;

//控件模板
class ControlTemplate : public Object
{
public:
	MPF_API ControlTemplate(UIElement& element);
	MPF_API virtual ~ControlTemplate();

	//获取模板
	MPF_API UIElement& GetTemplate() const mnoexcept;
	//设置模板
	MPF_API void SetTemplate(UIElement& element) mnoexcept;
	//获取或设置模板
	mproperty(UIElement&, Template);

	//设置模板绑定
	template<typename T>
	void SetTemplateBinding(UIElement& element, DependencyProperty<T>& property)
	{

	}

	//获取类型
	MPF_API DECLARE_GETTYPE(ControlTemplate);
	MPF_API DECLARE_GETINSTANTTYPE(ControlTemplate);
private:
	UIElement* element;
	
	DECLARE_TYPE(ControlTemplate);
};

NS_ED
NS_ED