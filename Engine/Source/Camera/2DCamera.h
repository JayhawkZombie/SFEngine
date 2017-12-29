#ifndef SFENGINE_2DCAMERA_H
#define SFENGINE_2DCAMERA_H

#include "../BasicIncludes.h"

namespace Engine
{

  class GenericActor;

  class Camera2D
  {
  public:
    Camera2D();
    Camera2D(const Camera2D &camera);

    void AttachToActor(std::shared_ptr<GenericActor> Actor);
    void DetachFromActor();
    void SetBoundaries(const sf::FloatRect &BoundaryRect);
    void SetView(const sf::FloatRect &Rect);
    void CenterOnActor();
    void Update();
    void Move(const sf::Vector2f &Delta);
    sf::FloatRect GetView() const;

  protected:
    void CheckBoundaries();

    sf::FloatRect m_View;
    sf::FloatRect m_DefaultView;
    std::weak_ptr<GenericActor> m_AttachedTo;
    sf::FloatRect m_Boundaries;
  };

}

#endif
