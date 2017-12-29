#include "RPGActor.h"
//Constructors/Destructors

#include <Thor\Animations.hpp>

RPGActor::RPGActor()
{
  m_name = "";
  m_filePath = "";
  this->AddCollider(Engine::Collider2D::CreatePolygonMesh(4, 10.f, (3.14159 / 4), Sprite.getPosition(), { 0, 0 }, 1.f, 0.f, sf::Color::Blue, true));
  //this->AddOccluder(Engine::Collider2D::CreatePolygonMesh(4, 10.f, (3.14159 / 4), Sprite.getPosition(), { 0, 0 }, 1.f, 0.f, sf::Color::White));
  //m_Colliders[0]->SetCollisionCallback(
  //  [this](LevelObject* ptr) { 
  //  this->HandleCollisionWithObject(ptr); }
  //);
  //m_Colliders[0]->SetSegmentCallback([](auto seg) {std::cerr << "RPGActor Hit Segment" << std::endl; });

  AddAnimations();
  m_Animator.play() << "myActor_standDown";
  m_Animator.animate(Sprite);
}


RPGActor::~RPGActor()
{
}

//Getters/Setters
std::string RPGActor::getName() const
{
  return m_name;
}

std::string RPGActor::getFilePath() const
{
  return m_filePath;
}

void RPGActor::setName(std::string name)
{
  m_name = name;
}

void RPGActor::setFilePath(std::string filePath)
{
  m_filePath = filePath;
}

void RPGActor::HandleInputEvent(const Engine::UserEvent & evnt)
{
  auto c_v = m_Colliders[0]->GetMesh().lock();

  if (evnt.EventType == Engine::UserEventType::KeyboardPress)
  {
    if (evnt.Key == sf::Keyboard::A || evnt.Key == sf::Keyboard::Left) {
      //m_Animator.play() << "myActor_walkLeft" << thor::Playback::loop("myActor_walkLeft");
      c_v->v.y = 0.f;
      c_v->v.x = -1.f;
      m_Direction = WalkingDirection::Left;

    }
    if (evnt.Key == sf::Keyboard::S || evnt.Key == sf::Keyboard::Down) {
      //m_Animator.play() << "myActor_walkDown" << thor::Playback::loop("myActor_walkDown");
      c_v->v.x = 0.f;
      c_v->v.y = 1.f;
      m_Direction = WalkingDirection::Down;
    }
    if (evnt.Key == sf::Keyboard::D || evnt.Key == sf::Keyboard::Right) {
      //m_Animator.play() << "myActor_walkRight" << thor::Playback::loop("myActor_walkRight");
      c_v->v.y = 0.f;
      c_v->v.x = 1.f;
      m_Direction = WalkingDirection::Right;
    }
    if (evnt.Key == sf::Keyboard::W || evnt.Key == sf::Keyboard::Up) {
      //m_Animator.play() << "myActor_walkUp" << thor::Playback::loop("myActor_walkUp");
      c_v->v.x = 0.f;
      c_v->v.y = -1.f;
      m_Direction = WalkingDirection::Up;
    }

    switch (m_Direction) {
    case WalkingDirection::Left:
      m_Animator.play() << "myActor_walkLeft" << thor::Playback::loop("myActor_walkLeft");
      break;
    case WalkingDirection::Right:
      m_Animator.play() << "myActor_walkRight" << thor::Playback::loop("myActor_walkRight");
      break;
    case WalkingDirection::Up:
      m_Animator.play() << "myActor_walkUp" << thor::Playback::loop("myActor_walkUp");
      break;
    case WalkingDirection::Down:
      m_Animator.play() << "myActor_walkDown" << thor::Playback::loop("myActor_walkDown");
      break;
    }
  }

  if (evnt.EventType == Engine::UserEventType::KeyboardRelease)
  {
    if ((evnt.Key == sf::Keyboard::A || evnt.Key == sf::Keyboard::Left) && m_Direction == WalkingDirection::Left) {
      c_v->v = { 0.f, c_v->v.y };
      m_Animator.play() << "myActor_standLeft";
    }
    if ((evnt.Key == sf::Keyboard::D || evnt.Key == sf::Keyboard::Right) && m_Direction == WalkingDirection::Right) {
      c_v->v = { 0.f, c_v->v.y };
      m_Animator.play() << "myActor_standRight";
    }
    if ((evnt.Key == sf::Keyboard::S || evnt.Key == sf::Keyboard::Down) && m_Direction == WalkingDirection::Down) {
      c_v->v = { c_v->v.x, 0.f };
      m_Animator.play() << "myActor_standDown";
    }
    if ((evnt.Key == sf::Keyboard::W || evnt.Key == sf::Keyboard::Up) && m_Direction == WalkingDirection::Up) {
      c_v->v = { c_v->v.x, 0.f };
      m_Animator.play() << "myActor_standUp";
    }
  }
}

void RPGActor::AddAnimations()
{
  sf::IntRect myActor_standDown_frame1(0, 0, 256, 256);
  sf::IntRect myActor_standUp_frame1(256, 0, 256, 256);
  sf::IntRect myActor_standLeft_frame1(512, 0, 256, 256);
  sf::IntRect myActor_standRight_frame1(768, 0, 256, 256);
  sf::IntRect myActor_walkDown_frame1(0, 0, 256, 256);
  sf::IntRect myActor_walkDown_frame2(0, 256, 256, 256);
  sf::IntRect myActor_walkDown_frame3(0, 512, 256, 256);
  sf::IntRect myActor_walkUp_frame1(256, 0, 256, 256);
  sf::IntRect myActor_walkUp_frame2(256, 256, 256, 256);
  sf::IntRect myActor_walkUp_frame3(256, 512, 256, 256);
  sf::IntRect myActor_walkLeft_frame1(512, 0, 256, 256);
  sf::IntRect myActor_walkLeft_frame2(512, 256, 256, 256);
  sf::IntRect myActor_walkLeft_frame3(512, 512, 256, 256);
  sf::IntRect myActor_walkRight_frame1(768, 0, 256, 256);
  sf::IntRect myActor_walkRight_frame2(768, 256, 256, 256);
  sf::IntRect myActor_walkRight_frame3(768, 512, 256, 256);

  thor::FrameAnimation myActor_standDown;
  myActor_standDown.addFrame(1.f, myActor_standDown_frame1);
  thor::FrameAnimation myActor_standUp;
  myActor_standUp.addFrame(1.f, myActor_standUp_frame1);
  thor::FrameAnimation myActor_standLeft;
  myActor_standLeft.addFrame(1.f, myActor_standLeft_frame1);
  thor::FrameAnimation myActor_standRight;
  myActor_standRight.addFrame(1.f, myActor_standRight_frame1);

  thor::FrameAnimation myActor_walkDown;
  myActor_walkDown.addFrame(1.f, myActor_walkDown_frame1);
  myActor_walkDown.addFrame(1.f, myActor_walkDown_frame2);
  myActor_walkDown.addFrame(1.f, myActor_walkDown_frame1);
  myActor_walkDown.addFrame(1.f, myActor_walkDown_frame3);

  thor::FrameAnimation myActor_walkUp;
  myActor_walkUp.addFrame(1.f, myActor_walkUp_frame1);
  myActor_walkUp.addFrame(1.f, myActor_walkUp_frame2);
  myActor_walkUp.addFrame(1.f, myActor_walkUp_frame1);
  myActor_walkUp.addFrame(1.f, myActor_walkUp_frame3);

  thor::FrameAnimation myActor_walkLeft;
  myActor_walkLeft.addFrame(1.f, myActor_walkLeft_frame1);
  myActor_walkLeft.addFrame(1.f, myActor_walkLeft_frame2);
  myActor_walkLeft.addFrame(1.f, myActor_walkLeft_frame1);
  myActor_walkLeft.addFrame(1.f, myActor_walkLeft_frame3);

  thor::FrameAnimation myActor_walkRight;
  myActor_walkRight.addFrame(1.f, myActor_walkRight_frame1);
  myActor_walkRight.addFrame(1.f, myActor_walkRight_frame2);
  myActor_walkRight.addFrame(1.f, myActor_walkRight_frame1);
  myActor_walkRight.addFrame(1.f, myActor_walkRight_frame3);

  m_AnimationMap.addAnimation("myActor_standDown", myActor_standDown, sf::microseconds(1));
  m_AnimationMap.addAnimation("myActor_standUp", myActor_standUp, sf::microseconds(1));
  m_AnimationMap.addAnimation("myActor_standLeft", myActor_standLeft, sf::microseconds(1));
  m_AnimationMap.addAnimation("myActor_standRight", myActor_standRight, sf::microseconds(1));
  m_AnimationMap.addAnimation("myActor_walkDown", myActor_walkDown, sf::seconds(0.6f));
  m_AnimationMap.addAnimation("myActor_walkUp", myActor_walkUp, sf::seconds(0.6f));
  m_AnimationMap.addAnimation("myActor_walkLeft", myActor_walkLeft, sf::seconds(0.6f));
  m_AnimationMap.addAnimation("myActor_walkRight", myActor_walkRight, sf::seconds(0.6f));

  //myActor_texture.loadFromFile("./Projects/TestProject/Textures/Guy12FSpriteSheetBig.png");
  Sprite.scale({ 16 / 256.f, 16 / 256.f });
}

void RPGActor::TickUpdate(const double & delta)
{
  Engine::LevelObject::TickUpdate(delta);
  this->MoveObject({ Velocity.x*(float)delta*(float).1, Velocity.y*(float)delta*(float).1 });
  static sf::Clock c;
  m_Animator.update(c.restart());
  m_Animator.animate(Sprite);
  //std::cout << "xPos: " << this->Position.x << " yPos: " << this->Position.y << "\n";//debugging code
}

void RPGActor::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  Engine::LevelObject::Render(Target);
}

void RPGActor::HandleCollisionWithObject(Engine::LevelObject * Object)
{
  if (Object->GetID() == "oaktree_churchdoor") {
    Engine::LoadLevelByName("oaktree_church");
  }
  else if (Object->GetID() == "church_exit") {
    Engine::LoadLevelByName("oaktree");
  }
}

void RPGActor::HandleCollisionWithObject(std::weak_ptr<Engine::Collider2D> Collided)
{
  
}
