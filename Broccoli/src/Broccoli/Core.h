#pragma once

#ifdef BRCL_PLATFORM_WINDOWS
	#define BRCL_API
#else
	#error Broccoli only supports Windows
#endif

#define BRCL_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)