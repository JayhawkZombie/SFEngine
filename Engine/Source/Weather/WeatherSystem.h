#pragma once

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

#include <Thor\Particles.hpp>

#include <set>
#include <random>

class LightningBolt;

class WeatherEvent
{
public:
  WeatherEvent();
  ~WeatherEvent();

  virtual void Start() = 0;
  virtual void End() = 0;
  virtual void TickUpdate(const double &delta) = 0;
  virtual void Render(std::shared_ptr<sf::RenderTarget> Target) = 0;

  float GetTotalDuration();
  float GetCurrentDuration();

  bool IsDone();

  void SetDoneCallback(std::function<void(void)> Callback);
protected:
  bool m_Done = false;
  bool m_Started = false;
  float m_TotalDuration;
  float m_CurrentDuration;
  int m_Intensity;
  std::function<void(void)> m_DoneCallback;
};

class LightningStorm : public WeatherEvent
{
public:
  LightningStorm();
  ~LightningStorm();

  void Start() override;
  void End() override;
  void TickUpdate(const double &delta) override;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override;

  void SetTotalDuration(float Duration);

  void IncreaseIntensity(int delta);
  void DecreaseIntensity(int delta);

  void AllocateBolts(std::size_t NumBolts);
  void FreeBolt(std::size_t Index);
  void SpawnBolt(std::size_t Index);
protected:
  float m_BoltSparkRate;
  float m_BoltSpawnRate;
  std::random_device rd;
  std::mt19937 rand_generator;
  std::uniform_real_distribution<float> m_random_dist;
  std::vector<std::shared_ptr<LightningBolt>> m_Bolts;
  std::set<std::size_t> m_FreeBolts;

};

class WeatherSystem
{
public:
  WeatherSystem();
  ~WeatherSystem();

  void SpawnEvent(std::shared_ptr<WeatherEvent> Event, std::function<void(void)> Completed = []() {});
  void TickUpdate(const double &delta);
  void Render(std::shared_ptr<sf::RenderTarget> Target);
protected:
  std::vector<std::shared_ptr<WeatherEvent>> m_Events;

};
