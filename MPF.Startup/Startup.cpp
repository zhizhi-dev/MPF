#include "stdafx.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, int nCmdShow)
{
	return MPFStartup(MPFMain);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return MPFStartup(MPFMain);
}

int wmain(int argc, wchar_t* argv[])
{
	return MPFConsoleStartup(MPFMain);
}

int main(int argc, char* argv[])
{
	return MPFConsoleStartup(MPFMain);
}