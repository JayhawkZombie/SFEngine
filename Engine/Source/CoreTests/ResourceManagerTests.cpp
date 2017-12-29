#include "TestDefs.h"

#if ENGINE_TESTS

#ifndef RESOURCE_MANAGER_TESTS
#define RESOURCE_MANAGER_TESTS

#include "../../ThirdParty/UnitTesting/Catch.hpp"
#include "../Headers/BasicIncludes.h"

namespace
{
  std::pair<std::string, std::shared_ptr<sf::Texture>> Textures, Textures2;
}

SCENARIO("Resource Manager can asynch load textures") {
  Engine::Resource::ResourceManager manager;
  manager.Start();
  sf::RenderWindow win;
  
  GIVEN("A running manager") {

    WHEN("The manager just starts") {
      REQUIRE(manager.GetSizeOfFontPool() == 0);
      REQUIRE(manager.GetSizeOfFragmentShaderPool() == 0);
      REQUIRE(manager.GetSizeOfTexturePool() == 0);
      REQUIRE(manager.GetSizeOfVertexShaderPool() == 0);
    }
    
    WHEN("A request is made for a new resource") {
      manager.RequestTexture("./SFEngine/Samples/Textures/UI/ButtonBG.png", "TEX1",
            [=](const std::shared_ptr<sf::Texture> t, const std::string &ID) {
            Textures.first = ID;
            Textures.second = t;
          }
      );
      manager.RequestTexture("./SFEngine/Samples/Textures/UI/ButtonBG.png", "TEX1",
                             [=](const std::shared_ptr<sf::Texture> t, const std::string &ID) {
        Textures2.first = ID;
        Textures2.second = t;
      }
      );
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      REQUIRE(Textures.first == "TEX1");
      REQUIRE(Textures.second.get() != nullptr);
      REQUIRE(Textures2.first == Textures.first);
      REQUIRE(Textures.second.get() == Textures.second.get());
    }

  }

  manager.Shutdown();

}
#endif
#endif
