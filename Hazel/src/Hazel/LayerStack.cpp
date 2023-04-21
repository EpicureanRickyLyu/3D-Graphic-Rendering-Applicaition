#include "pch.h"
#include "LayerStack.h"
namespace Hazel
{

	LayerStack::LayerStack()
	{
		m_LayerLastInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	//push layer after the last layer
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerLastInsert = m_Layers.emplace(m_LayerLastInsert, layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerLastInsert--;
		}
	}

	//All the overlay always get pushed after the layers
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{ 
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		m_Layers.erase(it);
	}

}