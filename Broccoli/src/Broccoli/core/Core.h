#pragma once

#ifdef BRCL_PLATFORM_WINDOWS
	#define BRCL_API
#else
	#error Broccoli only supports Windows
#endif

#ifdef BRCL_DEBUG
#define BRCL_ENABLE_ASSERTS
#endif

#ifdef BRCL_ENABLE_ASSERTS
#define BRCL_ASSERT(x, ...) { if(!(x)) { BRCL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define BRCL_CORE_ASSERT(x, ...) { if(!(x)) { BRCL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define BRCL_ASSERT(x, ...)
#define BRCL_CORE_ASSERT(x, ...)
#endif

#define BRCL_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1) //todo: replace with lambda