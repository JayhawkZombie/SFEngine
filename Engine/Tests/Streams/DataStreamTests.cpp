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

#include "DataStreamTests.h"

void RunDataStreamTests()
{

  float fVal = 500.f;
  int iVal = -25;
  unsigned int uiVal = 37;

  FormattedDataStream FStream;

  try
  {
    FStream << fVal;
    FStream << iVal;
    FStream << uiVal;

    float extFVal;
    int extIVal;
    unsigned int extUIVal;

    FStream >> extFVal;
    FStream >> extIVal;
    FStream >> extUIVal;

    std::cout << "FVal  : " << extFVal << "\n";
    std::cout << "IVal  : " << extIVal << "\n";
    std::cout << "UIVal : " << extUIVal << "\n";
  }
  catch (std::runtime_error &err)
  {
    std::cout << "FormattedDataStream error\n";
  }
}

