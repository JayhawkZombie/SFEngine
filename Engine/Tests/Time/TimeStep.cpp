#ifdef SFENGINE_TESTS

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

#include "catch/catch.hpp"

#include "stdafx.h"

#include <Engine/Source/Time/TimeStep.h>
#include <thread>
#include <chrono>

/*
Tests for TimeStep class
*/

TEST_CASE("TimeStep can accumulate time for a single step", "[time][step]")
{

  GIVEN("A TimeStep that has not been started")
  {
    TimeStep step;
    step.SetStep(16.666);
    step.SetMaxAccumulation(60.0);

    WHEN("The TimeStep is started")
    {
      step.Start();

      THEN("The TimeStep should not have any accumulated steps")
      {
        CHECK_FALSE(step.ShouldStep());
      }
    }

    WHEN("A single step has passed")
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
      step.Update();

      THEN("The TimeStep should have an accumulated step")
      {
        CHECK(step.ShouldStep());
      }
      THEN("The TimeStep should not have any additional steps accumulated")
      {
        CHECK_FALSE(step.ShouldStep());
      }
    }
  }
}

TEST_CASE("TimeStep will not acculate time longer than the max step", "[time][step]")
{
  GIVEN("A TimeStep")
  {
    TimeStep step;
    step.SetStep(16.666);
    step.SetMaxAccumulation(60.0);

    step.Start();

    WHEN("More than a single step time has passed")
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));

      step.Update();

      THEN("The TimeStep should have steps accumulated")
      {
        CHECK(step.ShouldStep());
      }
      THEN("The accumulated steps should not amount to more than the max step")
      {
        double totalTime = 16.666;
        while (step.ShouldStep()) totalTime += 16.666;

        CHECK(totalTime < 100.0);
      }
    }
  }
}


#endif // SFENGINE_TESTS
