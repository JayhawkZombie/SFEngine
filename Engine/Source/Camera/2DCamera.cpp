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

#include "Camera/2DCamera.h"
#include "Actor/Actor.h"

Camera2D::Camera2D()
{
}

Camera2D::Camera2D(const Camera2D & camera)
  : 
  m_View(camera.m_View), 
  m_AttachedTo(camera.m_AttachedTo.lock()),
  m_Boundaries(camera.m_Boundaries)
{
}

void Camera2D::AttachToActor(std::shared_ptr<GenericActor> Actor)
{
  m_AttachedTo = Actor;
}

void Camera2D::DetachFromActor()
{
  m_AttachedTo.reset();
}

void Camera2D::SetBoundaries(const sf::FloatRect & BoundaryRect)
{
  m_Boundaries = BoundaryRect;
}

void Camera2D::SetView(const sf::FloatRect & Rect)
{
  m_View = Rect;
}

void Camera2D::CenterOnActor()
{
  sf::FloatRect ActorBounds = (
    m_AttachedTo.lock() ?
        m_AttachedTo.lock()->GetGlobalBounds() :
        sf::FloatRect(0, 0, 0, 0)
    );

  sf::Vector2f ViewSize = sf::Vector2f(m_View.width, m_View.height);
  sf::Vector2f SizeDiff = ViewSize - sf::Vector2f(ActorBounds.width, ActorBounds.height);

  m_View = sf::FloatRect(
    ActorBounds.left - (SizeDiff.x / 2.f),
    ActorBounds.top - (SizeDiff.y / 2.f),
    ViewSize.x,
    ViewSize.y
  );
}

void Camera2D::Update()
{
  if (m_AttachedTo.lock())
    CenterOnActor();

}

void Camera2D::Move(const sf::Vector2f & Delta)
{
  m_View.left += Delta.x;
  m_View.top += Delta.y;
}

sf::FloatRect Camera2D::GetView() const
{
  return m_View;
}

void Camera2D::CheckBoundaries()
{
  sf::Vector2f BoundaryOverlap;
  if (m_View.left < m_Boundaries.left)
    BoundaryOverlap.x = m_Boundaries.left - m_View.left;
  if (m_View.top < m_Boundaries.top)
    BoundaryOverlap.y = m_Boundaries.top - m_View.top;
  if (m_View.left + m_View.width > m_Boundaries.left + m_Boundaries.width)
    BoundaryOverlap.x = ((m_Boundaries.left + m_Boundaries.width) - (m_View.left + m_View.width));
  if (m_View.top + m_View.height > m_Boundaries.top + m_Boundaries.height)
    BoundaryOverlap.y = ((m_Boundaries.top + m_Boundaries.height) - (m_View.top + m_View.height));

  m_View.left += BoundaryOverlap.x;
  m_View.top += BoundaryOverlap.y;
}
