#pragma once
#include "Hazel/Layer.h"
namespace Hazel
{
	class ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();

		~ImGuiLayer();

		void OnAttach() override;

		void OnDetach() override;

		void OnUpdate() override;

		void OnEvent(Event& event) override;

	private:

	};
}