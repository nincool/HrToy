/*
 -----------------------------------------------------------------------------
 This source file is part of OGRE
 (Object-oriented Graphics Rendering Engine)
 For the latest info, see http://www.ogre3d.org/
 
 Copyright (c) 2000-2014 Torus Knot Software Ltd
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 -----------------------------------------------------------------------------
 */
#ifndef __InputContext_H__
#define __InputContext_H__

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Event/HrEvent.h"
#include "HrOIS/includes/OIS.h"
#include "HrCommon/include/HrSingleton.h"


#if OIS_VERSION >= 0x010300     //  OIS_VERSION >= 1.3.0
#define OIS_WITH_MULTITOUCH     1
#else                           //  OIS_VERSION == 1.2.0
#define OIS_WITH_MULTITOUCH     0
#endif

namespace Hr
{
	class HrInputEventListener : public OIS::KeyListener, public OIS::MouseListener
	{
	public:
		virtual bool keyPressed(const OIS::KeyEvent &arg) override;

		virtual bool keyReleased(const OIS::KeyEvent &arg) override;

		virtual bool mouseMoved(const OIS::MouseEvent &arg) override;

		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;

		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;

	protected:
		HrEventKeyboard::EnumKeyCode GetKeyCodeMap(OIS::KeyCode keyCode);
		HrEventMouse::EnumMouseButtonID GetMouseButtonMap(OIS::MouseButtonID mouseID);
	};

    class HrInputManager : 
		public HrSingleTon<HrInputManager>
    {
	public:
		HrInputManager()
        {
            mKeyboard = 0;
            mMouse = 0;
#if OIS_WITH_MULTITOUCH
            mMultiTouch = 0;
#endif
            mAccelerometer = 0;

			m_pInputManager = nullptr;
        }

        void Capture() const
        {
            if(mKeyboard)
                mKeyboard->capture();
            if(mMouse)
                mMouse->capture();
#if OIS_WITH_MULTITOUCH
            if(mMultiTouch)
                mMultiTouch->capture();
#endif
            if(mAccelerometer)
                mAccelerometer->capture();
        }

		void CreateInputSystem();

        bool IsKeyDown(OIS::KeyCode key) const
        {
            return mKeyboard && mKeyboard->isKeyDown(key);
        }

        bool GetCursorPosition(float& x, float& y) const
        {
            // prefer mouse
            if(mMouse)
            {
                x = (float)mMouse->getMouseState().X.abs;
                y = (float)mMouse->getMouseState().Y.abs;
                return true;
            }
            
#if OIS_WITH_MULTITOUCH
            // than touch device
            if(mMultiTouch)
            {
                std::vector<OIS::MultiTouchState> states = mMultiTouch->getMultiTouchStates();
                if(states.size() > 0)
                {
                    x = (float)states[0].X.abs;
                    y = (float)states[0].Y.abs;
                    return true;
                }
            }
#endif

            // fallback
            x = y = 0.0;
            return false;
        }

		bool GetMouseWheelSlidingDistance(float& z)
		{
			if (mMouse)
			{
				z = (float)mMouse->getMouseState().Z.rel;

				return true;
			}

			z = 0.0;
			return false;
		}

        OIS::Keyboard* mKeyboard;         // context keyboard device
        OIS::Mouse* mMouse;               // context mouse device
#if OIS_WITH_MULTITOUCH
        OIS::MultiTouch* mMultiTouch;     // context multitouch device
#endif
        OIS::JoyStick* mAccelerometer;    // context accelerometer device

		OIS::InputManager* m_pInputManager;

		HrInputEventListener m_inputEventListener;
    };
}

#endif
