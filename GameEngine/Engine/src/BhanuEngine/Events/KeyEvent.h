#pragma once

#include "BhanuEngine/Events/Event.h"
#include "BhanuEngine/Core/Input.h"

namespace BhanuEngine 
{

	class KeyEvent : public Event
	{
		protected:
		    KeyEvent(KeyCode keycode)
			    : m_KeyCode(keycode) {}

			KeyCode m_KeyCode;

		public:
		    inline KeyCode GetKeyCode() const { return m_KeyCode; }

		    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class KeyPressedEvent : public KeyEvent
	{
		private:
		    int m_RepeatCount;

		public:
		    KeyPressedEvent(KeyCode keycode, int repeatCount)
			    : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

			inline int GetRepeatCount() const { return m_RepeatCount; }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyPressed)
	};

	class KeyReleasedEvent : public KeyEvent
	{
		public:
		    KeyReleasedEvent(KeyCode keycode)
			    : KeyEvent(keycode) {}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyReleasedEvent: " << m_KeyCode;
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
		public:
		    KeyTypedEvent(KeyCode keycode)
			    : KeyEvent(keycode) {}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyTypedEvent: " << m_KeyCode;
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyTyped)
	};
}