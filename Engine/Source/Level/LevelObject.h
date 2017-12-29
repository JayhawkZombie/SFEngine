#pragma once

#include "Engine\BaseEngineInterface.h"
#include "Animation\Animation.h"
#include "Components\ComponentBase.h"

#include "ThirdParty/PhysicsEngine.h"
#include <Thor\Animations.hpp>

namespace Engine
{
  class GenericActor;
  class Player;
  class Level;
  class BasicLevel;
  class Collider2DComponent;
  class Collider2D;
  class Occluder2D;
  class Interact2DComponent;

  enum class OverlapAction
  {
    KILL_ACTOR = 0,
    DISALLOW_ACTOR_OVERLAP = 1,
    CUSTOM_ACTION
  };

  class LevelObject : public BaseEngineInterface
  {
  public:
	friend class Level;
  friend class BasicLevel;
    LevelObject();
    virtual ~LevelObject();

    //Forbid implicit copy construction and assignment definitions
    //We [MUST] use a clone method
    LevelObject(const LevelObject &obj);
    LevelObject& operator=(const LevelObject &) = delete;
    
    virtual std::shared_ptr<BaseEngineInterface> Clone() const override;

    static void BindScriptMethods(chaiscript::ModulePtr module);
    virtual void ScriptInit();
    virtual void TickUpdate(const double &delta) override;
    virtual void PhysicsUpdate();
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;
    virtual void SetPosition(const sf::Vector2f &pos);
    virtual void SetSize(const sf::Vector2f &size);
    virtual void SetTexture(std::shared_ptr<sf::Texture> mytexture);
    virtual void SetTextureRect(sf::IntRect myRect);
    virtual sf::Vector2i getTopRight() const;
    virtual sf::Vector2i getTopLeft() const;
    virtual sf::Vector2i getBottomLeft() const;
    virtual sf::Vector2i getBottomRight() const;
    std::shared_ptr<sf::Texture> GetTexture() const;
    sf::Vector2f GetSize() const;
    sf::IntRect GetTextureRect() const;

    virtual void HandleCollisionWithObject(LevelObject *Object);
    virtual void SetCollisionHandleCallback(std::function<void(LevelObject*)> Callback);
    virtual void HandleCollisionWithCollider(SPtrShared<Collider2D> Collider);
    virtual void HandleCollisionWithSegment(PhysicsEngineSegmentType *Segment);
    virtual void SetSegmentCollisionCallback(std::function<void(PhysicsEngineSegmentType*)> Callback);

    virtual void HandleInputEvent(const UserEvent &evnt);
    virtual void SetID(const std::string &ID) override;

    virtual void OnGameStart();
    virtual void OnGameEnd();
    virtual void OnKilled();
    virtual void OnSpawn();
    virtual void Reset();
    virtual void Freeze();
    virtual void Unfreeze();
    bool IsFrozen() const;

    static void AddItemAnimation(std::shared_ptr<LevelObject> Item, const std::string &animName);
    sf::FloatRect GetGlobalBounds() const;

    virtual void Move(const sf::Vector2f &delta);
    virtual void Move(float x, float y);
    virtual void Move(int x, int y);

    void MoveObject(const sf::Vector2f &delta);

    std::vector<std::shared_ptr<Collider2D>> GetColliders() const;
    void AddCollider(std::shared_ptr<Collider2D> Collider);

    std::vector<std::shared_ptr<Collider2D>> GetOccluders() const;
    void AddOccluder(std::shared_ptr<Occluder2D> Occluder);
    void AddOccluder(std::shared_ptr<Collider2D> Collider);

    void AddFrameAnimation(const std::string &ID, const std::vector<sf::IntRect> &Frames, sf::Time Duration);
    virtual std::string GetClass() const override {
      return "LevelObject";
    }

  protected:
    bool m_IsFrozen = false;
    thor::AnimationMap<sf::Sprite, std::string> m_AnimationMap;
    thor::Animator<sf::Sprite, std::string> m_Animator;
    std::unordered_map<std::string, thor::FrameAnimation> m_FrameAnimations;

    std::vector<std::shared_ptr<Collider2D>> m_Colliders;
    std::vector<std::shared_ptr<Collider2D>> m_Occluders;
    std::function<void(LevelObject *)> m_HandleCollisionWithObject;
    std::function<void(PhysicsEngineSegmentType*)> m_HandleSegmentWithSegment;

  	std::shared_ptr<sf::Texture> SpriteTexture;
	  sf::Sprite Sprite;
    sf::IntRect TextureRect;
    sf::RectangleShape ObjectRect;
    sf::Vector2f Velocity;
    sf::Vector2f Acceleration;
    sf::Vector2f Position;
    sf::Vector2f Size;
    float MeshRadius = 0.f;
    bool AllowsActorOverlap; //if false, then actors will never be allowed to cross over this object
    bool RenderOutlined;
    bool TestingCollisions;
  };
}
