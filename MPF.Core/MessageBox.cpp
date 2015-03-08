#include "stdafx.h"

#pragma push_macro("MessageBox")
#ifdef MessageBox
#undef MessageBox
#endif

#include "../include/ui/MessageBox.h"

using namespace MPF;

uint32_t messageBoxIcons[] = { 0, MB_ICONINFORMATION, MB_ICONWARNING, MB_ICONERROR };

void MPF_CALL MPF::UI::MessageBox(const String& title, const String& text, MessageBoxIcons icon)
{
	::MessageBoxW(GetActiveWindow(), text.GetDataPointer(), title.GetDataPointer(), 
		MB_OK | messageBoxIcons[(uint32_t)icon]);
}

#pragma pop_macro("MessageBox")