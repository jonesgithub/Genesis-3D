/****************************************************************************
Copyright (c) 2007,Radon Labs GmbH
Copyright (c) 2011-2013,WebJet Business Division,CYOU

http://www.genesis-3d.com.cn

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
****************************************************************************/
#if WIN32

#include "input/input_stdneb.h"
#include "input/win32/win32inputserver.h"
#include "input/inputkeyboard.h"
#include "input/inputmouse.h"
#include "input/inputgamepad.h"

namespace Win32Input
{
__ImplementClass(Win32Input::Win32InputServer, 'W3IS', Input::InputServerBase);

using namespace Input;

//------------------------------------------------------------------------------
/**
*/
Win32InputServer::Win32InputServer()
{
}

//------------------------------------------------------------------------------
/**
*/
Win32InputServer::~Win32InputServer()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**    
*/
void
Win32InputServer::Open()
{
    n_assert(!this->IsOpen());
    InputServerBase::Open();

	this->defaultKeyboard = InputKeyboard::Create();
	this->AttachInputHandler(InputPriority::Game, this->defaultKeyboard.upcast<InputHandler>());   
    this->defaultMouse = InputMouse::Create();
    this->AttachInputHandler(InputPriority::Game, this->defaultMouse.upcast<InputHandler>());
}

//------------------------------------------------------------------------------
/**    
*/
void
Win32InputServer::Close()
{
    n_assert(this->IsOpen());

    // call parent class
    InputServerBase::Close();
}

//------------------------------------------------------------------------------
/**    
*/
void
Win32InputServer::OnFrame()
{
    InputServerBase::OnFrame();
}

} // namespace Win32Input

#endif
