// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO:  在此处引用程序需要的其他头文件
#include "../include/MPF.h"
#include "../include/io/FileStream.h"
#include "../include/media/ImageSource.h"
#include "../include/io/BinaryReader.h"

#ifdef _DEBUG
#pragma comment(lib, "../Debug/MPF.Core.lib")
#pragma comment(lib, "../Debug/MPF.Startup.lib")
#else
#pragma comment(lib, "../Release/MPF.Core.lib")
#pragma comment(lib, "../Release/MPF.Startup.lib")
#endif
//#pragma comment(lib, "../Debug/MPF.Visual.lib")