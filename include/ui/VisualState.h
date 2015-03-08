/*!
 * VisualState 视状态
 * 
 */

#pragma once
#include "UIElement.h"

NS_MPF
NS_UI

/* 视状态 */
class VisualState
{
public:
	/*! 
	 * \brief 初始化 VisualState 的新实例
	 * \param name 名称
	 */
	MPF_API VisualState(const String& name);
private:
	String name;		//!< 名称
};

NS_ED
NS_ED