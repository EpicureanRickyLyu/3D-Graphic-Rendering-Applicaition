#pragma once
#include "Hazel/core.h"
#include "Layer.h"

#include <vector>

namespace Hazel
{
	class LayerStack
	{
	public:
		LayerStack();
		virtual ~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector <Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector <Layer*>::iterator end() { return m_Layers.end(); }

	private:

		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerLastInsert;
	};
}