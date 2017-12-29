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

#include "Level\BasicLevel.h"
#include "Actor\Actor.h"

#ifdef WITH_EDITOR

void BasicLevel::ShowSpawner()
{
  if (!ImGui::Begin("Spawner")) {
    ImGui::End();
    return;
  }

  ShowPhysicsSpawner();
  ImGui::End();
}

void BasicLevel::ShowPhysicsSpawner()
{
  static sf::Vector2f Pos = { 0.f, 0.f };
  static sf::Vector2f Vel = { 0.f, 0.f };
  static int radius = 5;
  static vec2d gravity = vec2d(0.f, 0.01f);
  static int numsides = 3;
  static float mass = 0.01f;
  static float coeffRest = 0.1f;
  static float rotation = 0.f;
  static sf::Color color = sf::Color::White;
  static std::shared_ptr<sf::RenderTexture> ballTex;
  static std::shared_ptr<sf::RenderTexture> polyTex;
  static bool created = false;
  static sf::Sprite bRect;
  static sf::Sprite pRect;
  static unsigned int BallTexID;
  static unsigned int PolyTexID;
  if (!created) {
    ballTex = std::make_shared<sf::RenderTexture>();
    polyTex = std::make_shared<sf::RenderTexture>();
    ballTex->create(100, 100);
    polyTex->create(100, 100);
    bRect.setTexture(ballTex->getTexture());
    pRect.setTexture(ballTex->getTexture());
    bRect.setTextureRect({ 0, 0, 100, 100 });
    pRect.setTextureRect({ 0, 0, 100, 100 });
    created = true;
  }
  static float drag = 0.5f;

  //ballTex.setActive(true);
  //polyTex.setActive(true);
  //ballTex.clear(sf::Color::Transparent);
  //polyTex.clear(sf::Color::Transparent);

  static std::shared_ptr<PhysicsEngineBaseMeshType> Mesh;

  if (ImGui::DragFloat("UpdateInterval", &updateInterval, 1.f, 10.f, 33.f)) {

  }

  if (ImGui::CollapsingHeader("Meshes <testing>")) {
    //mesh spawner logic
    ImGui::Separator();
    ImGui::Indent();

    ImGui::Text("Position and Size");
    if (ImGui::InputFloat("PosX", &Pos.x, 5.f, 15.f)) {
      if (Pos.x < 0) Pos.x = 0.f;
    }
    if (ImGui::InputFloat("PoxY", &Pos.y, 5.f, 15.f)) {
      if (Pos.y < 0) Pos.y = 0.f;
    }
    if (ImGui::InputInt("Radius", &radius, 1, 5)) {
      if (radius < 0) radius = 0;
    }
    ImGui::Separator();

    ImGui::Text("Velocity");
    ImGui::InputFloat("x", &Vel.x, 1.f, 5.f);
    ImGui::InputFloat("y", &Vel.y, 1.f, 5.f);
    ImGui::Separator();

    ImGui::Text("Gravity and Friction");
    if (ImGui::InputFloat("Mass", &mass, 0.01f, 0.1f)) {
      if (mass < 0.01f) mass = 0.01f;
    }
    if (ImGui::InputFloat("Coeff of rest", &coeffRest, 0.05f, 0.1f)) {
      if (coeffRest < 0.05f) coeffRest = 0.05f;
    }
    if (ImGui::InputFloat("Gravity X", &gravity.x, 0.01f, 0.1f)) {
      SetGravity(&gravity);
      for (auto & item : Segments) {
        auto ptr = dynamic_cast<waveSeg*>(item.get());
        if (ptr) {
          ptr->grav_N = gravity.y;
        }
      }
    }
    if (ImGui::InputFloat("Gravity Y", &gravity.y, 0.01f, 0.1f)) {
      SetGravity(&gravity);
    }
    ImGui::Separator();

    ImGui::Text("Color");
    static float R = 0, G = 0, B = 0, A = 0;
    if (ImGui::DragFloat("Red", &R, 0.01f, 0.f, 1.f)) {
      color.r = static_cast<sf::Uint8>(std::floor(R * 255));
    }
    if (ImGui::DragFloat("Green", &G, 0.01f, 0.f, 1.f)) {
      color.g = static_cast<sf::Uint8>(std::floor(G * 255));
    }
    if (ImGui::DragFloat("Blue", &B, 0.01f, 0.0f, 1.0f)) {
      color.b = static_cast<sf::Uint8>(std::floor(B * 255));
    }
    ImGui::Separator();

    if (ImGui::CollapsingHeader("Ball")) {
      Mesh = BuildBallMesh('B', { 50.f, 50.f }, { 0.f, 0.f }, radius, mass, coeffRest, color);
      //ballTex->setActive(true);
      ballTex->clear();
      ballTex->resetGLStates();
      Mesh->draw(*ballTex);
      ballTex->display();
      bRect.setTexture(ballTex->getTexture());
      ImGui::ImageButton(bRect);
      //ImGui::Image(ballTex.getTexture(), sf::Vector2f( 100, 100 ), sf::FloatRect( 0, 0, 100, 100));

      if (ImGui::Button("Spawn")) {
        ImGui::SameLine();
        SpawnBall('B', Pos, Vel, radius, mass, coeffRest, color);
      }
    }

    if (ImGui::CollapsingHeader("N-Poly")) {
      Mesh = BuildPolygonMesh(numsides, __TO_FLOAT__(radius), rotation, { 50.f, 50.f }, { 0.f ,0.f }, mass, coeffRest, color);

      if (ImGui::SliderFloat("Rotation", &rotation, 0.f, 2.f * ____PI)) {
        Mesh = BuildPolygonMesh(numsides, __TO_FLOAT__(radius), rotation, { 50.f, 50.f }, { 0.f ,0.f }, mass, coeffRest, color);
      }
      if (ImGui::InputInt("Num Sides", &numsides, 1, 5)) {
        if (numsides < 3)
          numsides = 3;

        Mesh = BuildPolygonMesh(numsides, __TO_FLOAT__(radius), rotation, { 50.f, 50.f }, { 0.f ,0.f }, mass, coeffRest, color);
      }
      //polyTex->setActive(true);
      polyTex->resetGLStates();
      polyTex->clear();
      Mesh->draw(*polyTex);
      polyTex->display();
      pRect.setTexture(polyTex->getTexture());
      //ImGui::Image(polyTex.getTexture(), sf::Vector2f(100, 100), sf::FloatRect(0, 0, 100, 100));
      ImGui::ImageButton(pRect);
      if (ImGui::Button("Spawn")) {
        ImGui::SameLine();
        SpawnNPoly(numsides, __TO_FLOAT__(radius), rotation, Pos, Vel, mass, coeffRest, color);
      }
    }

    ImGui::Unindent();
  }

  if (ImGui::CollapsingHeader("Waves")) {
    if (ImGui::InputFloat("Segment Drag", &drag, 0.05f, 0.1f)) {
      mvHit::drag = drag;
    }

    ImGui::Indent();

    static sf::Vector2i leftCorner{ 0, 0 }, rightCorner{ 0, 0 };
    static float waveRad = 5.f;
    static float ampL{ 0.f }, ampR{ 0.f }, wvR{ 0.f }, wvL{ 0.f }, frL{ 0.f }, frR{ 0.f };
    static float elev{ 0.f }, airDen{ 0.f }, fluidDen{ 0.f }, depth{ 0.f };

    ImGui::Separator();
    ImGui::Text("Position and Size");
    if (ImGui::InputInt("Left PosX", &leftCorner.x, 5, 15)) {
      if (Pos.x < 0) Pos.x = 0.f;
    }
    if (ImGui::InputInt("Left PoxY", &leftCorner.y, 5, 15)) {
      if (Pos.y < 0) Pos.y = 0.f;
    }
    if (ImGui::InputInt("Right PosX", &rightCorner.x, 5, 15)) {
      if (Pos.x < 0) Pos.x = 0.f;
    }
    if (ImGui::InputInt("Right PoxY", &rightCorner.y, 5, 15)) {
      if (Pos.y < 0) Pos.y = 0.f;
    }
    if (ImGui::InputFloat("Radius", &waveRad, 10.f, 20.f)) {
      if (waveRad < 5.f)
        waveRad = 5.f;
    }
    ImGui::Separator();

    ImGui::Text("Amplitude, Wavelen & Frequency");

    ImGui::Columns(2);
    ImGui::NewLine();
    ImGui::DragFloat("Amp", &ampL, 5.f, 0.f, 50.f);
    ImGui::DragFloat("Wavelen", &wvL, 5.f, 100.f, 1000.f);
    ImGui::DragFloat("Frequency", &frL, 0.0005f, 0.f, 0.05f);
    ImGui::NextColumn();
    ImGui::DragFloat("Amp", &ampR, 5.f, 0.f, 50.f);
    ImGui::DragFloat("Wavelen", &wvR, 5.f, 100.f, 1000.f);
    ImGui::DragFloat("Frequency", &frR, 0.0005f, 0.f, 0.05f);

    ImGui::Columns(1);
    ImGui::Separator();

    ImGui::Text("Elevation and Density");

    ImGui::InputFloat("Elevation", &elev, 5.f, 15.f);
    ImGui::InputFloat("Depth", &depth, 5.f, 15.f);
    ImGui::InputFloat("Air Density", &airDen, 0.00005f, 0.0001f);
    ImGui::InputFloat("Fluid Density", &fluidDen, 0.005f, 0.001f);

    if (ImGui::Button("Spawn")) {
      SpawnWave('W', leftCorner, rightCorner, __TO_FLOAT__(radius), false, 300u, ampR, wvR, frR, ampL, wvL, frL, elev, airDen, depth, fluidDen);
    }

    ImGui::Unindent();
  }

  if (ImGui::Selectable("Particles <empty>")) {
    //particle spawner logic
  }

  if (ImGui::CollapsingHeader("Entities")) {

	static sf::Vector2f Position = { 0.f, 0.f };

	ImGui::Indent();
	if (ImGui::CollapsingHeader("Actors")) {
		//entity spawner logic
		ImGui::Separator();
		ImGui::Indent();

		ImGui::Text("Position and Size");
		if (ImGui::InputFloat("PosX", &Position.x, 5.f, 15.f)) {
			if (Position.x < 0) Position.x = 0;
		}
		if (ImGui::InputFloat("PoxY", &Position.y, 5.f, 15.f)) {
			if (Position.y < 0) Position.y = 0;
		}
		if (ImGui::InputInt("Radius", &radius, 1, 5)) {
			if (radius < 0) radius = 0;
		}
		ImGui::Separator();

		ImGui::Text("Velocity");
		ImGui::InputFloat("x", &Vel.x, 1.f, 5.f);
		ImGui::InputFloat("y", &Vel.y, 1.f, 5.f);
		ImGui::Separator();
		ImGui::Text("Color");
		static float R = 0, G = 0, B = 0, A = 0;
		if (ImGui::DragFloat("Red", &R, 0.01f, 0.f, 1.f)) {
			color.r = static_cast<sf::Uint8>(std::floor(R * 255));
		}
		if (ImGui::DragFloat("Green", &G, 0.01f, 0.f, 1.f)) {
			color.g = static_cast<sf::Uint8>(std::floor(G * 255));
		}
		if (ImGui::DragFloat("Blue", &B, 0.01f, 0.0f, 1.0f)) {
			color.b = static_cast<sf::Uint8>(std::floor(B * 255));
		}
		ImGui::Separator();
		if (ImGui::Button("Spawn")) {
			ImGui::SameLine();
			auto actor = std::make_shared<GenericActor>();
			actor->GenerateActorMesh("Polygon", Position, mass, coeffRest, 4, 0);
			actor->SpriteTexture = Textures["ActorGuy"];
			actor->Sprite.setTexture(*actor->SpriteTexture);
			actor->Sprite.setScale(100 / 16.f, 100 / 16.f);
			actor->SetPosition(Position);

			SpawnActor(actor, Position);
		}

		ImGui::Unindent();
	}

	ImGui::Unindent();
  }

}

#endif
