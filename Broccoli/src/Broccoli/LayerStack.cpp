#include "brclpch.h"
#include "LayerStack.h"

namespace brcl
{
	LayerStack::LayerStack()
	{
		m_LayerInsertIndex = 0;
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		auto it = m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex = static_cast<int>(it - m_Layers.begin());
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin()+ m_LayerInsertIndex, layer);
		if (it != m_Layers.begin()+m_LayerInsertIndex)
		{
			(*it)->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
			
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			(*it)->OnDetach();
			m_Layers.erase(it);
		}
			
	}
}