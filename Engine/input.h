#pragma once
#include "Vector2.h"
#include <vector>

namespace nu {
	class Input {
	public:
		enum class MouseButton {
			Left = 1,
			Middle,
			Right
		};

		//enum Handed {
		//	Right,
		//	Left
		//};

		bool Initialize();
		void Shutdown();

		void Update();

		bool GetKeyDown(int key) const { return m_keyStates[key]; }
		bool GetPrevKeyDown(int key) const { return m_prevKeyStates[key]; }
		bool GetKeyPressed(int key) const { return m_keyStates[key] && !m_prevKeyStates[key]; }
		bool GetKeyReleased(int key) const { return !m_keyStates[key] && m_prevKeyStates[key]; }

		bool GetMouseDown(MouseButton button) const { return m_buttonStates & GetButtonBit(button); }
		bool GetPrevMouseDown(MouseButton button) const { return m_prevButtonStates & GetButtonBit(button); }
		bool GetMousePressed(MouseButton button) const { return !GetPrevMouseDown(button) && GetMouseDown(button); }
		bool GetMouseReleased(MouseButton button) const { return GetPrevMouseDown(button) && !GetMouseDown(button); }

		Vector2 GetMousePosition() const { return m_mousePosition; }
			
	private:
		uint32_t GetButtonBit(MouseButton button) const;
		std::vector<bool> m_keyStates;
		std::vector<bool> m_prevKeyStates;

		uint32_t m_buttonStates = 0;
		uint32_t m_prevButtonStates = 0;

		Vector2 m_mousePosition{ 0, 0 };
	};
}