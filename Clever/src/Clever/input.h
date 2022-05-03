#pragma once

#include "Clever/Core.h"

namespace Clever
{

	class CLEVER_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance -> IsKeyPressedImpl(keycode);  }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->getMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->getMouseYImpl(); }
		inline static void SetMousePos(float x, float y) { s_Instance->SetMousePosition(x, y); }
		inline static void HideMouse(bool enabled) { s_Instance->hideMouse(enabled); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
		virtual void SetMousePosition(float x, float y) = 0;
		virtual void hideMouse(bool enabled) = 0;
	private:
		static Input* s_Instance;
	};

}