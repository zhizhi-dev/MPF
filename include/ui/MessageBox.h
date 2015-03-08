#pragma once
#include "../String.h"

NS_MPF
NS_UI

//消息框图标
enum class MessageBoxIcons
{
	//无
	None,
	//消息
	Information,
	//警告
	Warning,
	//错误
	Error
};

MPF_API void MPF_CALL MessageBox(const String& title, const String& text,
	MessageBoxIcons icon = MessageBoxIcons::None);

NS_ED
NS_ED