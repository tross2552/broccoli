#pragma once
#include "Broccoli/Application.h"

#ifdef BRCL_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	
	brcl::Log::Init();
	BRCL_CORE_WARN("Initialized log!");
	int a = 5;
	BRCL_INFO("Hello! a={0}", a);

	auto app = brcl::CreateApplication();
	app->Run();
	delete app;
}

#endif