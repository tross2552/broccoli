#pragma once
#include "Broccoli/Input.h"

namespace brcl
{
	class WindowsInput : public Input
	{
	protected:
		 bool IsKeyPressedImpl(const int keycode) const override;
		 bool IsMouseButtonPressedImpl(const int button) const override;
		 float GetMouseXImpl() const override;
		 float GetMouseYImpl() const override;
	};
}


