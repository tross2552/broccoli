#pragma once

#include "Layer.h"

#include <vector>

namespace brcl
{
	class BRCL_API LayerStack
	{
	public:
		//essentially a wrapper for a Layer* vector. overlays in first half, layers in second half
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }


	private:
		std::vector<Layer*> m_Layers;
		int m_LayerInsertIndex;
	};
};

