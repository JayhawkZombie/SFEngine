#ifndef GAME_LEVEL_OAK_TREE_H
#define GAME_LEVEL_OAK_TREE_H

#include "../../../../Engine/Source/Level/BasicLevel.h"
#include "../../../../Engine/Source/Globals/GlobalHooks.h"
#include "../../../../Engine/Source/Camera/2DCamera.h"
#include "OakTreeChurchInterior.h"

#include "Engine/Source/Physics/Occluder.h"
#include "Engine/Source/Lights/LightingSystem.h"

class OakTreeLevel : public BasicLevel
{
public:
  OakTreeLevel();
  OakTreeLevel(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines = false, const sf::Vector2f &GridSpacing = { 0,0 });

  void TickUpdate(const double &delta) override;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override;
  void HandleInputEvent(const UserEvent &evnt) override;
  void OnBegin() override;
  void OnEnd() override;
  void makeSegment(sf::Vector2i endPoint1, sf::Vector2i endPoint2);
  void makeSegment(int pt1x, int pt1y, int pt2x, int pty);
  std::string GetClass() const override final;
  void setLastSegmentPos(sf::Vector2i last);
  void nextSeg(int x, int y);//makes a segment with the last segment position, and updates last segment position
  void treeBaseSeg(int x, int y);//makes a square around the given vertices


protected:
  LightSystem m_LightSystem;

  std::shared_ptr<OakTreeChurchInterior> OakTreeChurchInteriorLevelPtr;
	std::shared_ptr<GenericActor> MainCharacter;
	Camera2D myActor_camera;
  /*If using this tool, first change,
  *       "Window = new sf::RenderWindow(sf::VideoMode(1700, 900), "SFEngine", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar, csettings);"
  * to
  *       "Window = new sf::RenderWindow(sf::VideoMode(800, 800), "SFEngine", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar, csettings);"
  * on line 21 in, 
  *       "/SFEngine/Source/Definitions/Engine/Startup.cpp"
  *
  */
  static const bool line_segment_builder_tool = false;
  static const bool snap_to_16x16 = true;
  sf::Vector2i lastPos;
  sw::TileMap top;
};

#endif
