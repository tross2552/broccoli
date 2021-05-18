#pragma once

#ifdef BRCL_PLATFORM_WINDOWS

extern brcl::Application* brcl::CreateApplication();

int main(int argc, char** argv)
{
	printf("Welcome to Broccoli Engine!\n");
	auto app = brcl::CreateApplication();
	app->Run();
	delete app;
}

#endif