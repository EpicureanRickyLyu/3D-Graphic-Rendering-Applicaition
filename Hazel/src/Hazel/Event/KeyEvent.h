#pragma once

#include "Event.h"
#include "Hazel/Core/KeyCode.h"

#include <sstream>

namespace Hazel
{

	class KeyEvent :public Event
	{
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

		public:
			KeyCode GetKeyCode() const { return m_KeyCode; }

		protected:
			KeyEvent(const KeyCode keycode)
				: m_KeyCode(keycode) {}

			KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
		EVENT_CLASS_TYPE(KeyPressed)

	public:
		KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
			: KeyEvent(keycode), m_IsRepeat(isRepeat) {}

		bool IsRepeat() const { return m_IsRepeat; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
			return ss.str();
		}

	private:
		bool m_IsRepeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
		EVENT_CLASS_TYPE(KeyReleased)
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

	};

	class KeyTypedEvent : public KeyEvent
	{
		EVENT_CLASS_TYPE(KeyTyped)
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

	};


}

