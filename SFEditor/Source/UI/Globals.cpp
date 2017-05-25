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
#include <UI/Globals.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <random>
#include <chrono>
#include <unordered_set>

namespace SFUI
{

  namespace {
    //IDs that have been used. Can search this to verify an ID has not been used already
    std::unordered_set<std::uint32_t> UsedIDs;
    int MaxIDGenerationAttempts = 30;
  }

  bool IsIDUsed(const int & ID)
  {
    return ( UsedIDs.find(ID) != UsedIDs.end() );;
  }

  void FreeID(const int & ID)
  {
    auto it = UsedIDs.find(ID);
    if (it != UsedIDs.end())
      UsedIDs.erase(it);
  }

  int GenerateID()
  {
    int ID = 0;
    int Tries = 0;

    static std::default_random_engine generator;
    generator.seed(static_cast<unsigned int>( std::chrono::system_clock::now().time_since_epoch().count() ));
    std::uniform_int_distribution<std::uint32_t> dist(1, std::numeric_limits<std::uint32_t>::max() - 1);

    ID = dist(generator);

    //If we couldn't do so, we will try a set number of times to generate one
    while (IsIDUsed(ID))
    {
      if (Tries >= MaxIDGenerationAttempts) {
        throw std::runtime_error("Cannot generate an ID for widget");
      }
      Tries++;
      ID = dist(generator);
    }

    UsedIDs.insert(ID);
    return ID;
  }

}
