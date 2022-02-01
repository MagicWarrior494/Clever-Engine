#pragma once

#include "CLever/Layer.h"

#include "Clever/Events/KeyEvent.h"
#include "Clever/Events/MouseEvent.h"
#include "Clever/Events/ApplicationEvent.h"


namespace Clever
{

	class CLEVER_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}