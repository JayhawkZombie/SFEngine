#include "OakTreeChurchInterior.h"
#include "Level/LevelObject.h"
#include "../../../../Game/RPGActor.h"
#include <map>
#include <cmath>


OakTreeChurchInterior::OakTreeChurchInterior(): BasicLevel({352,208},{0,0,352,208})
{
	LoadFromFile("./Projects/TestProject/testproject.json");
	std::vector<unsigned char> levelData(100000);
	levelData = {
		// row 0  1  2  3  4  5  6  7  8  9 10 11 12
		/*0*/ 43,42,42,41,41,40,40,40,41,41,42,42,43,
		/*1*/ 42,42,41,41,40, 1, 2, 3,40,41,41,42,42,
		/*2*/ 42,20,21,41,40, 5, 6, 7,40,41,22,23,42,
		/*3*/ 42,24,25,41,40, 9,10,11,40,41,26,27,42,
		/*4*/ 43,42,42,41,41,40,40,40,41,41,42,42,43,
		/*5*/ 52,57,57,57,57,57,57,57,57,57,57,57,55,
		/*6*/ 54,59,44,44,44,13,14,15,44,44,44,59,57,
		/*7*/  4, 8,56,44,44,17,18,19,44,44,58, 4, 8,
		/*8*/ 12,16,54,59,59,59,59,59,59,59,55,12,16,
		/*9*/ 52,53,49,50,50,50,50,50,50,50,51,52,53,
		/*10*/56,44,57,57,57,57,57,57,57,57,57,44,58,
		/*11*/56,45,46,46,46,47,44,45,46,46,46,47,58,
		/*12*/56,44,44,44,44,44,44,44,44,44,44,44,58,
		/*13*/56,45,46,46,46,47,44,45,46,46,46,47,58,
		/*14*/56,44,44,44,44,44,44,44,44,44,44,44,58,
		/*15*/56,45,46,46,46,47,44,45,46,46,46,47,58,
		/*16*/54,59,44,44,44,44,44,44,44,44,44,59,56,
		/*17*/28,29,56,45,46,47,44,45,46,47,58,30,31,
		/*18*/32,33,56,44,44,44,44,44,44,44,58,34,35,
		/*19*/36,37,56,45,46,47,44,45,46,47,58,38,39,
		/*20*/52,44,44,44,44,44,44,44,44,44,44,57,53,
		/*21*/54,59,59,59,59,59,59,59,59,59,59,59,56
	};
	TileMap->setSize({ 208,352 });
	TileMap->setGridSize({ 13,22 });
	TileMap->setTexture(*Textures["ChurchInterior"]);
	TileMap->setNumberOfTextureTilesPerRow(4);
	TileMap->setTextureTileSize({ 16,16 });
	TileMap->update(levelData, 13);

	//Segments

	//border
	//setJoint(0, 0);
	//nextSeg(13,0);
	//nextSeg(13, 22);
	//nextSeg(0, 22);
	//nextSeg(0, 0);

  Segments.push_back(BuildSegmentMesh('b', { 0,0 }, { 208,0 }));
  Segments.push_back(BuildSegmentMesh('b', { 208,0 }, { 208,352 }));
  Segments.push_back(BuildSegmentMesh('b', { 208,352 }, { 112,352 }));
  Segments.push_back(BuildSegmentMesh('b', { 0,352 }, { 96,352 }));
  Segments.push_back(BuildSegmentMesh('b', { 0,0 }, { 0,352 }));

	//Wall protection
	setJoint(0, 5);
	nextSeg(13, 5);

	//Stairs
	setJoint(2, 7);
	nextSeg(2, 10);
	nextSeg(11, 10);
	nextSeg(11, 7);
	setJoint(2, 9);
	nextSeg(11, 9);

	//Pews
	//frontLeft
	setJoint(1, 11);
	nextSeg(1, 12);
	nextSeg(6, 12);
	nextSeg(6, 11);
	//secondLeft
	setJoint(1, 13);
	nextSeg(1, 14);
	nextSeg(6, 14);
	nextSeg(6, 13);
	//ThirdLeft
	setJoint(1, 15);
	nextSeg(1, 16);
	nextSeg(6, 16);
	nextSeg(6, 15);
	//FourthLeft
	setJoint(3, 17);
	nextSeg(3, 18);
	nextSeg(6, 18);
	nextSeg(6, 17);
	//Bottom Left
	setJoint(3, 19);
	nextSeg(3, 20);
	nextSeg(6, 20);
	nextSeg(6, 19);
	//TopRight
	setJoint(7, 11);
	nextSeg(7, 12);
	nextSeg(12, 12);
	nextSeg(12, 11);
	//Second Right Pew
	setJoint(7, 13);
	nextSeg(7, 14);
	nextSeg(12, 14);
	nextSeg(12, 13);
	//Third Rigth Pew
	setJoint(7, 15);
	nextSeg(7, 16);
	nextSeg(12, 16);
	nextSeg(12, 15);
	//Fourth Right pew
	setJoint(7, 17);
	nextSeg(7, 18);
	nextSeg(10, 18);
	nextSeg(10, 17);
	//Last Right Pew
	setJoint(7, 19);
	nextSeg(7, 20);
	nextSeg(10, 20);
	nextSeg(10, 19);
	//podium
	setJoint(5, 7);
	nextSeg(5, 8);
	nextSeg(8, 8);
	nextSeg(8, 7);
	nextSeg(5, 7);
	//Confessional
	setJoint(0, 17);
	nextSeg(2, 17);
	nextSeg(2, 20);
	nextSeg(0, 20);
	nextSeg(0, 17);
	//Ladder
	setJoint(11, 20);
	nextSeg(11, 17);
	nextSeg(13, 17);
	nextSeg(13, 20);


	//Actor/View information
	std::shared_ptr<RPGActor> myActor = std::make_shared<RPGActor>();
	myActor->SetTexture(Textures["MyActor_sheet"]);
	SpawnActor(myActor,{ 6 * 16,20.5 * 16 });
	myActor->SetPosition({ 6 * 16,20.5 * 16 });
	myActor->SetActorSize({ 15,15 });//could be 16 but collisiions
	MainCharacter = myActor;

	sf::FloatRect myActor_spawnLocation(72.f, 72.f, 16.f, 16.f);
	sf::FloatRect full_map_view(0.f, 0.f, 208.f, 352.f);

	myActor_camera.AttachToActor(myActor);
//	myActor_camera.SetView(myActor_spawnLocation);
	myActor_camera.SetView({ 325.f,176.f,325.f,176.f });
	Gravity->x = 0;
	Gravity->y = 0;
	SetGravity(Gravity);

  std::shared_ptr <LevelObject> Church_Exit = std::make_shared<LevelObject>();
  Church_Exit->SetID("church_exit");
  Church_Exit->SetPosition({ 6*16,22*16 });
  Church_Exit->SetSize({ 32, 32 });
  Church_Exit->AddCollider(Collider2D::CreatePolygonMesh(4, 11.31f, (3.14159 / 4), { 6.5 * 16,22.5 * 16 }, { 0, 0 }, 1000000000000.f, 0.f, sf::Color::Red));
  LevelObjects["Church_Exit"] = Church_Exit;
}


OakTreeChurchInterior::~OakTreeChurchInterior()
{
}

void OakTreeChurchInterior::TickUpdate(const double & delta)
{
	BasicLevel::TickUpdate(delta);
	//LevelObjects["MainGuy"]->TickUpdate(delta);
	myActor_camera.Update();
}

void OakTreeChurchInterior::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
	sf::View view(myActor_camera.GetView());
	view.setViewport({ 0.f,0.f,1.f,1.f });

	Texture->setView(view);

	Texture->draw(*TileMap);
	BasicLevel::RenderOnTexture(Texture);
}

void OakTreeChurchInterior::HandleInputEvent(const UserEvent & evnt)
{
	MainCharacter->HandleInputEvent(evnt);
}

void OakTreeChurchInterior::OnBegin()
{
	SetGravity(Gravity);
  MainCharacter->SetActorPosition({ 6 * 16,20.5 * 16 });

}

void OakTreeChurchInterior::OnEnd()
{
}

void OakTreeChurchInterior::setJoint(int x, int y)
{
	lastPos = { x,y };
}

void OakTreeChurchInterior::nextSeg(int x, int y)
{
	Segments.push_back(BuildSegmentMesh('b', { lastPos.x * 16,lastPos.y * 16 }, { x * 16,y * 16 }));
	lastPos = { x,y };
}
std::string OakTreeChurchInterior::GetClass() const
{
	return std::string("OakTreeChurchInterior");
}
