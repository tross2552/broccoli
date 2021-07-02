﻿#pragma once
#include "Broccoli.h"

namespace Sandbox
{
	class ExampleLayer : public brcl::Layer
	{
	public:
		ExampleLayer();

		void OnUpdate(brcl::Timestep deltaTime) override;

		void OnEvent(brcl::Event& event) override;

		brcl::Vector4 color;

	private:

		std::shared_ptr<brcl::Shader> m_Shader;
		std::shared_ptr<brcl::VertexArray> m_VertexArray;
		std::shared_ptr<brcl::VertexArray> m_VertexArraySquare;
		std::shared_ptr<brcl::Texture2D> m_Texture;

		brcl::Camera m_Camera;
	};

	//temporary app gui!!!!!
	class ExampleImGuiLayer : public brcl::ImGuiLayer
	{
	public:

		ExampleImGuiLayer(ExampleLayer* layer) :
			ImGuiLayer("AppGuiLayer"), m_AppLayer(layer)
		{
		}

		void OnImGuiRender() override;

	private:

		ExampleLayer* m_AppLayer;
	};
}