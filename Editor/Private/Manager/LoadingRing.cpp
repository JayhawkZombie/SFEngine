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

/************************************************************************/
/*                         Internal  Headers                            
/************************************************************************/
#include "Globals.h"
#if defined (SF_EDITOR)

/************************************************************************/
/*                       Dependency  Headers                            
/************************************************************************/
#include <SelbaWard/Ring.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       
/************************************************************************/

/************************************************************************/
/*                         MainWindow                                   
/************************************************************************/
/*                                                                      
/*                                                                      
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/10                                  
/************************************************************************/

namespace SFEngine
{

  class LoadingRing {
  public:

    void Render(SPtrShared<sf::RenderWindow> Window) {
      Window->draw(m_Ring);
    }

    void TickUpdate(const double &delta) {
      if (m_IsFilling) {
        m_CurrentTime += (float)(delta);
        m_CurrentFillAmount += (float)(delta * m_FillRate);

        if (m_FillingUp && m_CurrentFillAmount >= m_FinalFillAmount) {
          m_CurrentFillAmount = m_FinalFillAmount;
          m_IsFilling = false;
        }
        else if (!m_FillingUp && m_CurrentFillAmount <= m_FinalFillAmount) {
          m_CurrentFillAmount = m_FinalFillAmount;
          m_IsFilling = false;
        }

        m_Ring.setSectorSize(m_CurrentFillAmount);
      }
      else
        m_CurrentTime = 0.0;
    }

    void SetRadius(float Radius) {
      m_Ring.setRadius(Radius);
    }

    void SetHoleRatio(float Radius) {
      m_Ring.setHole(Radius);
    }

    void SetArcFill(float Size) {
      m_Ring.setSectorSize(Size);
    }

    void SetColor(sf::Color Color) {
      m_Ring.setColor(Color);
    }

    void SetPosition(const sf::Vector2f &pos) {
      m_Ring.setPosition(pos);
    }

    void SetFillRate(float PercPerMs) {
      m_FillRate = PercPerMs;
      m_TimeBetweenFills = 1.f / m_FillRate;
    }

    void Fill(float ms) {
      m_FinalFillAmount = 1.f;
      m_FillRate = (m_FinalFillAmount - m_CurrentFillAmount) / ms;
      m_IsFilling = true;
      m_FillingUp = (m_FillRate > 0.f);
    }

    void FillTo(float Perc, float ms) {
      m_FinalFillAmount = Perc;
      m_FillRate = (m_FinalFillAmount - m_CurrentFillAmount) / ms;
      m_IsFilling = true;
      m_FillingUp = (m_FillRate > 0.f);
    }

    void Empty(float ms) {
      m_FinalFillAmount = 0.f;
      m_FillRate = (m_FinalFillAmount - m_CurrentFillAmount) / ms;
      m_IsFilling = true;
      m_FillingUp = false;
    }


  private:
    double m_FillRate = 0.0;
    double m_FillPerc = 0.0;
    double m_TimeBetweenFills = 0.0;
    double m_CurrentTime = 0.0;

    bool m_IsFilling = false;
    bool m_FillingUp = false;
    float m_CurrentFillAmount = 0.f;
    float m_FinalFillAmount = 0.f;

    sw::Ring m_Ring;
  };

} // namespace SFEngine

#endif // if defined (SF_EDITOR)
