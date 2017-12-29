#ifndef SFENGINE_WEATHER_SYSTEM_H
#define SFENGINE_WEATHER_SYSTEM_H

#include <Thor\Particles.hpp>

#include <set>
#include <random>

namespace Engine
{
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

}

#endif
