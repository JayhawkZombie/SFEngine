#ifndef SFEDITOR_WINDOW_H
#define SFEDITOR_WINDOW_H

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

////////////////////////////////////////////////////////////
// Internal Headers
////////////////////////////////////////////////////////////
#include <UI/Screen.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////
#include <boost/any.hpp>
#include <SFML\Graphics.hpp>

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <thread>
#include <mutex>

namespace SFUI
{

  class Window
  {
  public:
    Window();
    Window(sf::RenderWindow *Win);
    ~Window();

    void Create(Vec2i Size, std::string Title, sf::Uint32 Style);
    void Add(Widget::Ptr widget, std::string ID = "");
    void Remove(std::string ID);
    void Remove(Widget::Ptr widget);
    void Close();
    void Open();
    void Hide();
    void Show();
    void LaunchAndLink(Widget::Ptr Connection, std::function<void(boost::any)> DoneCB);
    void Launch(std::function<void(boost::any)> DoneCB);

    bool IsOpen() const;
  protected:
    void MainLoop(std::function<void(boost::any)> DoneCB);
    void HandleEvent(sf::Event event);
    
    Screen::Ptr m_Screen;

    bool m_Open;
    bool m_Visible;
    std::shared_ptr<std::mutex> m_Mutex;
    std::thread m_Thread;
    std::shared_ptr<sf::RenderWindow> m_Window;
    Widget::Ptr m_ConnectedWidget;
  };

}

#endif // SFEDITOR_WINDOW_H