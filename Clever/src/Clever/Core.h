#pragma once

#ifdef CV_PLATFORM_WINDOWS
	#ifdef CV_BUILD_DLL
		#define CLEVER_API __declspec(dllexport)
	#else
		#define CLEVER_API __declspec(dllimport)
	#endif
#else
	#error Clever only supports Windows
#endif
