#include "TestDefs.h"

#if ENGINE_TESTS

#ifndef EVENT_HANDLER_TESTS
#define EVENT_HANDLER_TESTS

#include "../../ThirdParty/UnitTesting/Catch.hpp"
#include "../Headers/Events/EventHandler.h"

namespace
{
  sf::Keyboard::Key _k = sf::Keyboard::A;
  sf::Keyboard::Key _konrelease = sf::Keyboard::A;
  sf::Vector2i _pos(0, 0);
  sf::Mouse::Button _b = sf::Mouse::Button::Left;




  sf::Keyboard::Key _SimKey = sf::Keyboard::Comma;
  sf::Vector2i _SimPos(100, 100);
  sf::Mouse::Button _SimButton = sf::Mouse::Button::Right;
}

void _Test_Key_Press(const sf::Keyboard::Key &k) {
  _k = k;
}

void _Test_Mouse_Press(const sf::Vector2i &pos, const sf::Mouse::Button &b) {
  _pos = pos;
  _b = b;
}


SCENARIO("Event handler is created") {

  Engine::EventHandler Handler;

  GIVEN("A new event handler") {

    WHEN("No callbacks have been registered") {
      REQUIRE(_k == sf::Keyboard::A);
      REQUIRE(_pos == sf::Vector2i(0, 0));
      REQUIRE(_b == sf::Mouse::Button::Left);

      THEN("Invoking callbacks should not throw exceptions") {
        REQUIRE_NOTHROW(Handler.HandleKeyPress(_SimKey));
        REQUIRE_NOTHROW(Handler.HandleMousePress(_SimPos, _SimButton));
        REQUIRE_NOTHROW(Handler.HandleKeyRelease(_SimKey));
        REQUIRE_NOTHROW(Handler.HandleMouseRelease(_SimPos, _SimButton));
        REQUIRE_NOTHROW(Handler.HandleMouseMovement(_SimPos));
        REQUIRE_NOTHROW(Handler.HandleMouseOver(_SimPos));
        REQUIRE_NOTHROW(Handler.HandleMouseExit(_SimPos));
        REQUIRE_NOTHROW(Handler.HandleMouseScroll(_SimPos));
        REQUIRE_NOTHROW(Handler.HandleTextEntered(_SimKey));
      }
    }

    WHEN("Key Pressed is registered") {
      Handler.BindCallback(Engine::Events::KeyPressed, [=](const sf::Keyboard::Key &k) {_Test_Key_Press(k); });

      THEN("Invoking the callback should change _k") {
        Handler.HandleKeyPress(sf::Keyboard::B);

        REQUIRE(_k == sf::Keyboard::B);
      }
    }

    WHEN("Key Release is registered") {
      Handler.BindCallback(Engine::Events::KeyReleased, [=](const sf::Keyboard::Key &k) {_Test_Key_Press(k); });

      THEN("Invoking the callback should change _k") {
        Handler.HandleKeyRelease(sf::Keyboard::Z);

        REQUIRE(_k == sf::Keyboard::Z);
      }
    }

    WHEN("Mouse Press is registered") {
      Handler.BindCallback(Engine::Events::MouseDown, [=](const sf::Vector2i &p, const sf::Mouse::Button &b) {_Test_Mouse_Press(p, b); });

      THEN("Invoking the callback should change _b") {
        Handler.HandleMousePress(sf::Vector2i(20, 20), sf::Mouse::Button::XButton1);

        REQUIRE(_pos == sf::Vector2i(20, 20));
        REQUIRE(_b == sf::Mouse::Button::XButton1);
      }
    }

  }

}
#endif
#endif
