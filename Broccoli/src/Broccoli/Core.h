#pragma once

#ifdef BRCL_PLATFORM_WINDOWS
	#ifdef  BRCL_BUILD_DLL
		#define BRCL_API __declspec(dllexport)
	#else
		#define BRCL_API __declspec(dllimport)
	#endif //  BRCL_BUILD_DLL
#else
	#error Broccoli only supports Windows
#endif

#define BRCL_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)