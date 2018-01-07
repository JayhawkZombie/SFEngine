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

#include <cereal/archives/portable_binary.hpp>
#include <fstream>
#include <string>
#include <memory>

template<typename T>
bool SerializeToArchive(std::shared_ptr<T> ToSerialize, const std::string &Filename)
{
  std::ofstream ofile(Filename, std::ios_base::binary);

  if (!ofile)
    return false;

  try
  {
    {
      cereal::PortableBinaryOutputArchive archive(ofile);
      archive(*ToSerialize);
    }

    return true;
  }
  catch (const std::exception &err)
  {
    ERR_STREAM << "Error serializing to file \"" << Filename << "\": " << err.what() << "\n";
    return false;
  }

}

template<typename T>
bool DeserializeFromArchive(std::shared_ptr<T> ToDeserialize, const std::string &Filename)
{
  std::ifstream ifile(Filename, std::ios_base::binary);

  if (!ifile)
    return false;

  try
  {
    {
      cereal::PortableBinaryInputArchive archive(ifile);
      archive(*ToDeserialize);
    }

    return true;
  }
  catch (const std::exception &err)
  {
    ERR_STREAM << "Error deserializing from file \"" << Filename << "\": " << err.what() << "\n";
    return false;
  }

}

