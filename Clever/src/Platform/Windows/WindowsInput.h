#include "Clever/input.h"

namespace Clever
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;

		virtual std::pair<float, float> GetMousePositionImpl() override;
	};
}