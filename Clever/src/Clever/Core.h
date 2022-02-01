#pragma once

#ifdef CV_PLATFORM_WINDOWS
#if CV_DYNAMIC_LINK
	#ifdef CV_BUILD_DLL
		#define CLEVER_API __declspec(dllexport)
	#else
		#define CLEVER_API __declspec(dllimport)
	#endif
#else
	#define CLEVER_API
#endif

#else
	#error Clever only supports Windows
#endif

#ifdef CV_ENABLE_ASSERTS
	#define CV_ASSERT(x, ...){ if(!(x)) { CV_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CV_CORE_ASSERT(x, ...){ if(!(x)) {  CV_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CV_ASSERT(x, ...);
	#define CV_CORE_ASSERT(x, ...);
#endif 

#define BIT(x) (1 << x) 

#define CV_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)