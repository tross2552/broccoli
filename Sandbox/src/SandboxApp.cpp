#include <Broccoli.h>

class Sandbox : public brcl::Application
{

};

brcl::Application* brcl::CreateApplication()
{
	return new Sandbox();
}