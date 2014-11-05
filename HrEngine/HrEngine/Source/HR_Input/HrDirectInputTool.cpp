#include "HrDirectInputTool.h"

#include <cassert>

using namespace HR;
CHrDirectInputTool::CHrDirectInputTool(void)
{
	m_pKeyBoardDevice = NULL;
	m_pMouseDevice = NULL;
	m_pDirectInput = NULL;
}

CHrDirectInputTool::~CHrDirectInputTool(void)
{
	if (m_pKeyBoardDevice != NULL)
	{
		m_pKeyBoardDevice->Unacquire();
	}
	if (m_pMouseDevice != NULL)
	{
		m_pMouseDevice->Unacquire();
	}
	SAFE_RELEASE(m_pKeyBoardDevice);
	SAFE_RELEASE(m_pMouseDevice);
	SAFE_RELEASE(m_pDirectInput);
}

HRESULT CHrDirectInputTool::Initialize(HWND hWnd, HINSTANCE hInstance, DWORD dwKeyBoardCoopFlags, DWORD dwMouseCoopFlags)
{
	FAILED_RETURN(DirectInput8Create(hInstance, DIRECTINPUT_VERSION
		, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	FAILED_RETURN(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyBoardDevice, NULL));

	FAILED_RETURN(m_pKeyBoardDevice->SetCooperativeLevel(hWnd, dwKeyBoardCoopFlags));
	FAILED_RETURN(m_pKeyBoardDevice->SetDataFormat(&c_dfDIKeyboard));
	FAILED_RETURN(m_pKeyBoardDevice->Acquire());
	FAILED_RETURN(m_pKeyBoardDevice->Poll());

	FAILED_RETURN(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouseDevice, NULL));
	FAILED_RETURN(m_pMouseDevice->SetCooperativeLevel(hWnd, dwMouseCoopFlags));
	FAILED_RETURN(m_pMouseDevice->SetDataFormat(&c_dfDIMouse));
	FAILED_RETURN(m_pMouseDevice->Acquire());
	FAILED_RETURN(m_pMouseDevice->Poll());

	return S_OK;
}

void CHrDirectInputTool::GetInput()
{
	HRESULT hr = m_pKeyBoardDevice->GetDeviceState(sizeof(m_cKeyBufferArr), (LPVOID)m_cKeyBufferArr);
	if (hr)
	{
		m_pKeyBoardDevice->Acquire();
		m_pKeyBoardDevice->GetDeviceState(sizeof(m_cKeyBufferArr), (LPVOID)m_cKeyBufferArr);
	}

	hr = m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_stMouseState);
	if (hr)
	{
		m_pMouseDevice->Acquire();
		m_pMouseDevice->GetDeviceState(sizeof(m_stMouseState), (LPVOID)&m_stMouseState);
	}
}

bool CHrDirectInputTool::IsKeyDown(int iKey)
{
	assert(iKey >= 0 && iKey < 256);
	if (m_cKeyBufferArr[iKey] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CHrDirectInputTool::CheckMouseButtonDown(int iButton)
{
	assert(iButton >= 0 && iButton < 4);
	return ((m_stMouseState.rgbButtons[iButton] & 0x80) != 0);
}

float CHrDirectInputTool::MouseDX()
{
	return (float)m_stMouseState.lX;
}

float CHrDirectInputTool::MouseDY()
{
	return (float)m_stMouseState.lY;
}

float CHrDirectInputTool::MouseDZ()
{
	return (float)m_stMouseState.lZ;
}


