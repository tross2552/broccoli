#pragma once
#include "Broccoli/Layer.h"
namespace Sandbox
{
	class ExampleLayer : public brcl::Layer
	{
	public:
		ExampleLayer() : Layer("Example") {}

		void OnUpdate() override;

		void OnEvent(brcl::Event& event) override;

	};
}
