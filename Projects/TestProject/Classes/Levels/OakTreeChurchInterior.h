#ifndef GAME_LEVEL_OAK_TREE_CHURCH_INTERIOR_H
#define GAME_LEVEL_OAK_TREE_CHURCH_INTERIOR_H

#include "../../../../Engine/Source/Level/BasicLevel.h"
#include "../../../../Engine/Source/Globals/GlobalHooks.h"
#include "../../../../Engine/Source/Camera/2DCamera.h"


class OakTreeChurchInterior : public Engine::BasicLevel
{
public:
	OakTreeChurchInterior();
	//OakTreeChurchInterior(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines = false, const sf::Vector2f &GridSpacing = { 0,0 });
	~OakTreeChurchInterior();

	void TickUpdate(const double &delta) override;
	void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override;
	void HandleInputEvent(const Engine::UserEvent &evnt) override;
	void OnBegin() override;
	void OnEnd() override;
	std::string GetClass() const override final;
	void setJoint(int x, int y);
	void nextSeg(int x, int y);

protected:
	std::shared_ptr<Engine::GenericActor> MainCharacter;
	Engine::Camera2D myActor_camera;
	sf::Vector2i lastPos;
};

#endif