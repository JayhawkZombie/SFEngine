#ifndef SFENGINE_ANIMATION_H
#define SFENGINE_ANIMATION_H

#include "BasicIncludes.h"
#include "Engine\BaseEngineInterface.h"

namespace Engine
{

  struct AnimationInfo
  {
    std::string TextureID, TexturePath;
    std::size_t NumberFrames;
    double Duration;
    std::vector<sf::IntRect> Frames;
  };

  class Animation : public BaseEngineInterface
  {
  public:
    //NEW
    Animation() : m_currentFrame(0), m_currentTime(0), m_frameTime(0), m_isPaused(true), m_isRendered(false) {}
    Animation(const Animation &Copy);
    std::shared_ptr<BaseEngineInterface> Clone() const override final;

    ~Animation();
    void Update(double deltaTime);
    void Play(bool loop = true, bool notifycomplete = false);
    void Pause();
    void Stop();
    void Move(float x, float y);
    void Move(const sf::Vector2f &pos);
    void SetPosition(float x, float y);
    void SetPosition(const sf::Vector2f &pos);
    void SetSize(const sf::Vector2f &size);
    void SetFrameTime(double fTime);
    void ResetFrames();
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;
    sf::Sprite* GetSprite();
    //OLD
    friend class SFEngine;
    void AddFrame(sf::IntRect frame);
    void RequestSpriteSheet(const std::string, const std::string id);
    void SetSpriteSheet(std::shared_ptr<sf::Texture> tex, const std::string &ID);
    std::shared_ptr<sf::Texture> GetSpriteSheet() const;
    std::size_t GetSize() const;
    const sf::IntRect& GetFrame(std::size_t n) const;
    void Render(std::shared_ptr<sf::RenderTarget> Target);
    void TickUpdate(const double& delta);
    void OnShutDown();

    std::string GetClass() const override;

    std::function<void(void)> AnimationComplete = []() {};
    void MakePingPong(bool ping) {
      m_pingpong = ping;
      FrameList.MakePingPong(ping);
    }

    void MakeLooped(bool b) {
      FrameList.MakeLooped(b);
      m_loop = b;
    }

    const sf::RectangleShape& GetRect() const {
      return AnimRect;
    }
    const sf::IntRect& GetCurrentFrame() const {
      return *(CurrFrame->Value);
    }
    bool IsPlaying() const {
      return (!m_isPaused && m_isRendered);
    }
  private:
    Util::DoublyLinkedList<sf::IntRect, true, false> FrameList;
    std::shared_ptr<Util::Node<sf::IntRect>> CurrFrame = nullptr;

    bool m_loop = true;
    bool m_notifyComplete = false;
    bool m_pingpong = false;
    int dir = 1; //1 -> forward, -1 -> backward
    bool m_isPaused;
    bool m_isRendered;
    int m_currentFrame;
    sf::Vector2f m_size;
    double m_currentTime;
    double m_frameTime;
    std::vector<sf::IntRect> m_frames;
    std::shared_ptr<sf::Texture> m_texture;
    sf::Sprite sprite;
    sf::RectangleShape AnimRect;
  };
}
#endif // SFENGINE_ANIMATION_H#pragma once