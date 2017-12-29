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

#include "Objects/TriggerVolume.h"

TriggerVolume::TriggerVolume(TriggerMethod Method)
{
}
TriggerVolume::TriggerVolume(std::function<void(void)> TriggerCB, std::function<bool(std::shared_ptr<LevelObject>)> TriggerCheckCB, bool DoTriggerCheck)
{
}
TriggerVolume::~TriggerVolume()
{
}
TriggerVolume::TriggerVolume(const TriggerVolume &)
{
}
std::shared_ptr<TriggerVolume> TriggerVolume::Clone() const
{
  return std::shared_ptr<TriggerVolume>();
}
void TriggerVolume::TickUpdate(const double & TickDelta)
{
}
void TriggerVolume::Render(std::shared_ptr<sf::RenderTarget> Target)
{
}
void TriggerVolume::DoTriggerChecks(std::map<std::string, std::shared_ptr<LevelObject>>& Objects)
{
}
void TriggerVolume::Cleanup()
{
}
void TriggerVolume::Sleep(bool MakeDefault)
{
}
void TriggerVolume::Wake()
{
}
void TriggerVolume::SleepFor(double Ms)
{
}
void TriggerVolume::Enable(bool MakeDefault)
{
}
void TriggerVolume::Disable(bool MakeDefault)
{
}
void TriggerVolume::Reset()
{
}
void TriggerVolume::SetCollider(std::shared_ptr<Collider2D> Collider)
{
}
void TriggerVolume::SetTriggerMethod(TriggerMethod Method, bool MakeDefault)
{
}
