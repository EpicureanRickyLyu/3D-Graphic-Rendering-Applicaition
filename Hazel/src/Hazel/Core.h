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

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x,...) {if(!(x)) { HZ_LOG_ERROR("Assertion Fail: {0}", __VA_ARGS__); __debugbreak();}}
	#define HZ_CORE_ASSERT(x,...) {if(!(x)) { HZ_LOG_CORE_ERROR("Assertion Fail: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define HZ_ASSERT(x,...)
	#define HZ_CORE_ASSERT(x,...)
#endif // HZ_ENABLE_ASSERTS

#define BIND_EVENT_FN_1(funcName) std::bind(&funcName, this, std::placeholders::_1) 

#define MAKE_SINGLETON(className) \
private:\
className() = default;\
const className(const className& other) = delete;\
const className& operator = (const className& other) = delete;\
public:\
inline static className& GetInstance() { static className instance; return instance; };\

#define MAKE_NONCOPYABLE(className) \
private:\
const className(const className& other) = delete;\
const className& operator = (const className& other) = delete;\

