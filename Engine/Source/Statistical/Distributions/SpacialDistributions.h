#pragma once

#include "NumericalDistributions.h"
#include <SFML/Graphics.hpp>

class ISpacialDistribution
{
public:

  virtual ~ISpacialDistribution() = default;

  virtual sf::Vector2f operator()() = 0;

};


/* Radial - generate points along the circumference of a circle */
class RadialDistribution : public ISpacialDistribution
{
public:

  RadialDistribution();
  RadialDistribution(const sf::Vector2f &Center, float Radius);

  virtual ~RadialDistribution() = default;

  virtual sf::Vector2f operator()() override;

  void SetCenter(const sf::Vector2f &Center);
  void SetRadius(float Radius);

protected:

  float m_Radius;
  sf::Vector2f m_Center;
  UniformRealDistribution<float> m_AngleDistribution;

};

/* Circular - generate points anywhere inside a circle */

class CircularDistribution : public RadialDistribution
{
public:

  CircularDistribution();
  CircularDistribution(const sf::Vector2f &Center, float Radius);

  sf::Vector2f operator()() override;

private:

  UniformRealDistribution<float> m_DistanceDistribution;

};

class RectangularDistribution : public ISpacialDistribution
{
public:

  RectangularDistribution() = default;
  RectangularDistribution(float left, float top, float width, float height);

  sf::Vector2f operator()() override;

  void SetBounds(float left, float top, float width, float height);

private:

  UniformRealDistribution<float> m_XDirDist;
  UniformRealDistribution<float> m_YDirDist;

  sf::FloatRect m_Bounds;

};


/* Directional - random directions with a + or - random deviation */

class DirectionalDistribution : public ISpacialDistribution
{
public:

  DirectionalDistribution();
  DirectionalDistribution(float Angle, float Deviation);

  sf::Vector2f operator()() override;

private:

  float m_Angle;
  float m_Deviation;

  UniformRealDistribution<float> m_DeviationDistribution;

};

/* Line - random points along a line */

class LineDistribution : public ISpacialDistribution
{
public:

  LineDistribution();
  LineDistribution(const sf::Vector2f &Start, const sf::Vector2f &End);

  sf::Vector2f operator()() override;

  void SetPoints(const sf::Vector2f &Start, const sf::Vector2f &End);

private:

  sf::Vector2f m_Start;
  sf::Vector2f m_End;

  UniformRealDistribution<float> m_DistanceDistribution;

};
