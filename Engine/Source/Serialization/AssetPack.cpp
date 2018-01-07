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

#include "AssetPack.h"
#include <fstream>

#include <filesystem>

namespace filesystem = std::experimental::filesystem;

bool AssetPacker::PackTexture(const std::string &Filename)
{

  auto path = std::experimental::filesystem::path(filesystem::current_path() / Filename);
  if (filesystem::exists(path) && filesystem::is_regular_file(path))
  {
    std::ifstream ifile(Filename, std::ios_base::binary);
    auto filesize = filesystem::file_size(path);

    std::cout << "Texture file size : " << filesize << "\n";

    auto packedIT = m_TextureAssets.insert({ Filename, {} });

    if (packedIT.second)
    {
      PackedTextureAsset &packedTexture = packedIT.first->second;

      packedTexture.RawData.resize(filesize);
      ifile.read(reinterpret_cast<char *>(packedTexture.RawData.data()), filesize);
      ifile.close();

      std::cout << "Stored binary data: " << packedTexture.RawData.size() << "\n";

      return true;
    }
  }

  return false;
}

bool AssetPacker::PackAudio(const std::string &Filename)
{
  auto path = filesystem::path(filesystem::current_path() / Filename);
  if (filesystem::exists(path) && filesystem::is_regular_file(path))
  {
    std::ifstream ifile(Filename, std::ios_base::binary);
    auto filesize = filesystem::file_size(path);

    auto packedIT = m_AudioAssets.insert({ Filename, {} });
   
    if (packedIT.second)
    {
      PackedAudioAsset &packedAudio = packedIT.first->second;

      packedAudio.RawData.resize(filesize);
      ifile.read(reinterpret_cast<char*>(packedAudio.RawData.data()), filesize);
      ifile.close();

      return true;
    }
  }

  return false;
}

bool AssetPacker::PackFont(const std::string &Filename)
{
  auto path = filesystem::path(filesystem::current_path() / Filename);
  if (filesystem::exists(path) && filesystem::is_regular_file(path))
  {
    std::ifstream ifile(Filename, std::ios_base::binary);
    auto filesize = filesystem::file_size(path);

    auto packedIT = m_FontAssets.insert({ Filename, {} });

    if (packedIT.second)
    {
      PackedFontAsset &packedFont = packedIT.first->second;

      packedFont.RawData.resize(filesize);
      ifile.read(reinterpret_cast<char*>(packedFont.RawData.data()), filesize);
      ifile.close();

      return true;
    }
  }

  return false;
}

std::optional<PackedTextureAsset*> AssetPacker::GetTexture(const std::string &Filename)
{
  auto it = m_TextureAssets.find(Filename);

  if (it == m_TextureAssets.end())
    return std::nullopt;

  return std::make_optional(&it->second);
}

std::optional<PackedAudioAsset*> AssetPacker::GetSoundBuffer(const std::string &Filename)
{
  auto it = m_AudioAssets.find(Filename);

  if (it == m_AudioAssets.end())
    return std::nullopt;

  return std::make_optional(&it->second);
}

std::optional<PackedFontAsset*> AssetPacker::GetFont(const std::string &Filename)
{
  auto it = m_FontAssets.find(Filename);

  if (it == m_FontAssets.end())
    return std::nullopt;

  return std::make_optional(&it->second);
}
