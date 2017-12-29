#pragma once

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

#include "BasicIncludes.h"

namespace Engine
{

  enum class ShaderType {
    VertexShader = 0,
    FragmentShader
  };

  template<typename T>
  struct ShaderParameter {
    T value;
    std::string ID;
    ShaderType Type;
  };

  template<typename T>
  struct ShaderArrayParameter {
    T* values;
    std::string ID;
    std::size_t ArraySize;
    ShaderType Type;

    void SetValues(std::size_t i, T* vals) {
      if (values)
        delete[] values;

      values = new T[i];
      for (std::size_t _ = 0; _ < i; _++) {
        values[_] = vals[_];
      }
    }
  };

  class Shader
  {
  public:
    Shader(const std::string &file);
    ~Shader();

    void AddFloatParameter(const std::string &param);
    void AddFloatArrayParameter(const std::string &param, const std::size_t &ArraySize);
    void AddColorParameter(const std::string &param);
    void AddTextureParameter(const std::string &param);

  private:
    
    std::map<std::string, ShaderParameter<float>> FloatParameters;
    std::map<std::string, ShaderParameter<sf::Color>> ColorParameters;
    std::map<std::string, ShaderArrayParameter<float>> FloatArrayParameters;

  };

}
