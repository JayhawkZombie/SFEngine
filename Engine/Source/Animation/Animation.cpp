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

#include "Animation\Animation.h"

Animation::Animation(const Animation & Copy)
  : BaseEngineInterface()
{
}

std::shared_ptr<BaseEngineInterface> Animation::Clone() const
{
  auto Anim = std::make_shared<Animation>(*this);

  return Anim;
}

Animation::~Animation()
{
  CurrFrame = FrameList.GetHead();
  if (CurrFrame)
    CurrFrame->Destroy();
  m_texture.reset();
}
//NEW
void Animation::Update(double delta) {

}
void Animation::Play(bool loop, bool notifycomplete) {
  m_isPaused = false;
  CurrFrame = FrameList.GetHead();
  if (!m_isRendered) {
    m_isRendered = true;
    m_currentFrame = 0;
    m_loop = loop;
  }
}

void Animation::SerializeOut(std::ofstream &out) {

}

void Animation::SerializeIn(std::ifstream & in)
{
}

void Animation::Pause() {
  m_isPaused = true;
}
void Animation::Stop() {
  m_isRendered = false;
  m_isPaused = true;
  m_currentFrame = 0;
  if (m_notifyComplete)
    AnimationComplete();
}
void Animation::Move(float x, float y) {
  sprite.move(x, y);
}
void Animation::Move(const sf::Vector2f &pos) {
  sprite.move(pos);
}
void Animation::SetPosition(float x, float y) {
  sprite.setPosition(x, y);
  AnimRect.setPosition({ x, y });
}
void Animation::SetPosition(const sf::Vector2f &pos) {
  sprite.setPosition(pos);
  AnimRect.setPosition(pos);
}
void Animation::SetSize(const sf::Vector2f & size)
{
  m_size = size;
  AnimRect.setSize(size);
}
void Animation::SetFrameTime(double fTime) {
  m_frameTime = fTime;
}
void Animation::ResetFrames()
{
  m_frames.clear();
}
sf::Sprite* Animation::GetSprite() {
  return &sprite;
}
//OLD
void Animation::Render(std::shared_ptr<sf::RenderTarget> Target) {
  if (m_isRendered) {
    //sprite.setTextureRect(m_frames[m_currentFrame]);
    //Target->draw(sprite);
    Target->draw(AnimRect);
  }
}
void Animation::TickUpdate(const double& delta)
{
  if (!m_isPaused && m_isRendered)
  {
    m_currentTime += delta;
    // if current time is bigger then the frame time advance one frame
    if (m_currentTime >= m_frameTime)
    {
      // reset time, but keep the remainder
      //m_currentTime = m_currentTime - m_frameTime;
      m_currentTime -= m_frameTime;

      m_currentFrame += 1;
      CurrFrame = FrameList.Advance(CurrFrame);

      //if (m_currentFrame >= m_frames.size()) {

      //  if (m_loop)
      //    m_currentFrame = 0;
      //  else
      //    Stop();
      //}

      //if (m_currentFrame >= m_frames.size()) {
      //  if (m_loop)
      //    m_currentFrame = 0;
      //  else
      //    Stop();

      //  if (m_pingpong)
      //    dir = -1;
      //  else
      //    dir = 1;
      //}
      //if (m_currentFrame < 0) {
      //  m_currentFrame = 0;
      //  dir = 1;
      //}
      AnimRect.setTextureRect(*CurrFrame->Value);
        //AnimRect.setTextureRect(m_frames[m_currentFrame]);
    }
  }
}
void Animation::OnShutDown() {}

std::string Animation::GetClass() const
{
  return std::string("Animation");
}

void Animation::AddFrame(sf::IntRect rect)
{
  m_frames.push_back(rect);
  FrameList.InsertBack(std::make_shared<sf::IntRect>(rect));
  if (!CurrFrame)
    CurrFrame = FrameList.GetTail();
}
void Animation::RequestSpriteSheet(const std::string Filepath, const std::string ID) {
  m_texture;
  SetSpriteSheet(LoadTexture(Filepath, ID), ID);
  //ResourceManager->RequestTexture(Filepath, ID,
  //                                [this](std::shared_ptr<sf::Texture> t, const std::string &s) {this->SetSpriteSheet(t, s); }
  //);
}
void Animation::SetSpriteSheet(std::shared_ptr<sf::Texture> tex, const std::string &ID) {
  sprite.setTexture(*tex.get());
  AnimRect.setTexture(tex.get());
  m_texture = tex;
}

std::shared_ptr<sf::Texture> Animation::GetSpriteSheet() const {
  return m_texture;
}

std::size_t Animation::GetSize() const
{
  return m_frames.size();
}

const sf::IntRect& Animation::GetFrame(std::size_t n) const
{
  return m_frames[n];
}
