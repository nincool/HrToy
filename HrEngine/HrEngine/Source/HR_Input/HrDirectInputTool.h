#pragma once
#include "HrCommon.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace HR
{
	class CHrDirectInputTool
	{
	public:
		CHrDirectInputTool(void);
		~CHrDirectInputTool(void);

	public:
		HRESULT				Initialize(HWND hWnd, HINSTANCE hInstance, DWORD dwKeyBoardCoopFlags, DWORD dwMouseCoopFlags);

		void				GetInput();

		bool				IsKeyDown(int iKey);

		bool				CheckMouseButtonDown(int iButton);
		float				MouseDX();
		float				MouseDY();
		float				MouseDZ();
	private:
		IDirectInput8*			m_pDirectInput;
		IDirectInputDevice8*	m_pKeyBoardDevice;
		char					m_cKeyBufferArr[256];

		IDirectInputDevice8*	m_pMouseDevice;
		DIMOUSESTATE			m_stMouseState;
	};

}
