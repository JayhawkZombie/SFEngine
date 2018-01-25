#pragma once

#include <random>

template<typename T>
class UniformIntegralDistribution
{
public:

  UniformIntegralDistribution()
    : m_Engine(m_RDevice()) { }

  UniformIntegralDistribution(T Low, T High)
    : UniformIntegralDistribution()
    , m_Distribution(Low, High) { }

  UniformIntegralDistribution(const UniformIntegralDistribution &IDist)
    : m_Distribution(IDist.m_Distribution)
    , m_Engine(IDist.m_Engine)
    , m_Max(IDist.m_Max)
    , m_Min(IDist.m_Min)
    , m_RDevice(IDist.m_RDevice) { }

  UniformIntegralDistribution& operator=(const UniformIntegralDistribution &IDist)
  {
    m_Distribution = IDist.m_Distribution;
    m_Engine = IDist.m_Engine;
    m_Max = IDist.m_Max;
    m_Min = IDist.m_Min;
    m_RDevice = IDist.m_RDevice;
    return *this;
  }

  template<typename U>
  void Seed(U val)
  {
    m_Engine.seed(val);
  }

  T operator()()
  {
    return m_Distribution(m_Engine);
  }

private:

  T m_Min;
  T m_Max;

  std::uniform_int_distribution<T> m_Distribution;
  std::mt19937 m_Engine;
  std::random_device m_RDevice;

};


template<typename T>
class UniformRealDistribution
{
public:

  UniformRealDistribution()
    : m_Engine(m_RDevice()) { }

  UniformRealDistribution(T Low, T High)
    : UniformRealDistribution()
    , m_Distribution(Low, High) { }

  UniformRealDistribution(const UniformRealDistribution &UDist)
    : m_Distribution(UDist.m_Distribution)
    , m_Engine(UDist.m_Engine)
    , m_Max(UDist.m_Max)
    , m_Min(UDist.m_Min)
    , m_RDevice(UDist.m_RDevice)
  { }

  UniformRealDistribution<float>& operator=(const UniformRealDistribution &UDist)
  {
    m_Distribution = UDist.m_Distribution;
    m_Engine = UDist.m_Engine;
    m_Max = UDist.m_Max;
    m_Min = UDist.m_Min;
    m_RDevice = UDist.m_RDevice;
    return *this;
  }

  template<typename U>
  void Seed(U val)
  {
    m_Engine.seed(val);
  }

  T operator()()
  {
    return m_Distribution(m_Engine);
  }

private:

  T m_Min;
  T m_Max;

  std::uniform_real_distribution<T> m_Distribution;
  std::mt19937 m_Engine;
  std::random_device m_RDevice;
};
