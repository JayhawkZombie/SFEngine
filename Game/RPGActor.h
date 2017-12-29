#ifndef RPG_ACTOR_H
#define RPG_ACTOR_H

#include <string>

#include "Actor/Actor.h"
#include "Physics/Collider.h"
#include "Physics\Occluder.h"

enum class WalkingDirection
{
  Up, Down, Left, Right
};

class RPGActor : public GenericActor
{
public:
  //constructor/destructor
  RPGActor();
  ~RPGActor();

  void AddAnimations();

  //getters/setters
  std::string getName() const;
  std::string getFilePath() const;
  void setName(std::string name);
  void setFilePath(std::string filePath);

  void HandleInputEvent(const UserEvent &evnt) override;
  virtual void TickUpdate(const double &delta) override;
  virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;

private:
  std::string m_name;
  std::string m_filePath;
  sf::Vector2i m_Cell;
  sf::Texture myActor_texture;
  WalkingDirection m_Direction;

  virtual void HandleCollisionWithObject(LevelObject *Object) override;
  virtual void HandleCollisionWithObject(std::weak_ptr<Collider2D> Collided);
};

#endif
