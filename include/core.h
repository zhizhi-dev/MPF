#pragma once
#include "datatypes.h"

#ifdef MPFCORE_EXPORTS
#define MPF_API __declspec(dllexport)
#else
#define MPF_API __declspec(dllimport)
#endif