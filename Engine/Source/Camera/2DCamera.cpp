#include "Camera/2DCamera.h"
#include "Actor/Actor.h"

namespace Engine
{

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

}
