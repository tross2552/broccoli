#pragma once
#include "Broccoli/Input.h"

namespace brcl
{
	class WindowsInput : public Input
	{
	protected:
		 bool IsKeyPressedImpl(const KeyCode keycode) const override;
		 bool IsMouseButtonPressedImpl(const MouseCode mousecode) const override;
		 float GetMouseXImpl() const override;
		 float GetMouseYImpl() const override;
	};
}


