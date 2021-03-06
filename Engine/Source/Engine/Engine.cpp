////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//
////////////////////////////////////////////////////////////

#include "Engine/stdafx.h"
#include "Engine\Engine.h"

#ifdef SPLATFORM_WINDOWS
#include "Processsnapshot.h"
#endif

SFEngine::SFEngine()
{
  CommmandLineArgumentsDescription.add_options()
    ( "benchmark", "benchmark performance" )
    ( "restart", "restart from previous run" )
    ( "report", "report crash from previous run" )
    ( "?", boost::program_options::value<std::vector<std::string>>(), "add initialization key/value pair (as if from ini)" )
    ( "defaults-file", boost::program_options::value<std::string>(), "file containing default initialization values" )
    ( "options-file", boost::program_options::value<std::string>(), "file containing additional configuration options" )
    ;
}

SFEngine::~SFEngine()
{

}


TimerManager* SFEngine::GetTimerManager()
{
  return m_GlobalTimerManager.get();
}

void SFEngine::LoadLevel(std::string lvl)
{

}

void SFEngine::SwitchToLevel(std::string lvl)
{

}

bool SFEngine::IsKeyLeftDown()
{
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}
