#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
//using name HAZEL_API replace "__declspec(dllexport)" for export dll file
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif // HZ_BUILD_DLL
#else
	#error Hazel only for windows!
#endif // HZ_PLAFRORM_WINDOWS