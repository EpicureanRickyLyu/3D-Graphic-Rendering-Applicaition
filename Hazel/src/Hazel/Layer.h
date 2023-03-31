#pragma once
#include "Hazel/Core.h"
#include "Hazel/Event/Event.h"


/// <summary>
/// Layers Stored in a stack
/// Used to decide render order, event order etc.
/// </summary>
namespace Hazel
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_debugName; }

	protected:
		std::string m_debugName;
	};


}

