#pragma once
#include "../datatypes.h"

#ifdef MPFVISUAL_EXPORTS
#define MPFVSL_API __declspec(dllexport)
#else
#define MPFVSL_API __declspec(dllimport)
#endif