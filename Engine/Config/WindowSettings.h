#pragma once

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2018 Kurt Slagle - kurt_slagle@yahoo.com
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

#include <SFML/Graphics.hpp>

#include <string>

class WindowSettings
{
public:

  sf::Vector2u GetSize() const { return m_Size; }
  std::string GetTitle() const { return m_Title; }
  bool IsResizable() const { return m_CanBeResized; }
  bool HasTitlebar() const { return m_HasTitlebar; }
  bool HasCloseButton() const { return m_HasCloseButton; }
  bool CanBeMoved() const { return m_CanBeMoved; }
  bool IsFullscreen() const { return m_IsFullscreen; }

private:

  sf::Vector2u m_Size = sf::Vector2u(800u, 800u);
  std::string m_Title = std::string("SFEngine");

  bool m_CanBeResized = true;
  bool m_HasTitlebar = true;
  bool m_HasCloseButton = true;
  bool m_CanBeMoved = true;
  bool m_IsFullscreen = false;

};
