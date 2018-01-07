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

#include "Serialization.h"
#include <optional>
#include <cereal/types/unordered_map.hpp>

struct PackedTextureAsset
{
  std::vector<unsigned char> RawData;

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(RawData);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(RawData);
  }
};

struct PackedAudioAsset
{
  std::vector<unsigned char> RawData;

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(RawData);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(RawData);
  }
};

struct PackedFontAsset
{
  std::vector<unsigned char> RawData;

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(RawData);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(RawData);
  }
};

class AssetPacker
{
public:
  AssetPacker() = default;
  ~AssetPacker() = default;

  bool PackTexture(const std::string &Filename);
  bool PackAudio(const std::string &Filename);
  bool PackFont(const std::string &Filename); 

  std::optional<PackedTextureAsset*> GetTexture(const std::string &Filename);
  std::optional<PackedAudioAsset*>GetSoundBuffer(const std::string &Filename);
  std::optional<PackedFontAsset*> GetFont(const std::string &Filename);

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(m_AudioAssets);
    ar(m_TextureAssets);
    ar(m_FontAssets);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(m_AudioAssets);
    ar(m_TextureAssets);
    ar(m_FontAssets);
  }

  std::unordered_map<std::string, PackedAudioAsset> m_AudioAssets;
  std::unordered_map<std::string, PackedFontAsset> m_FontAssets;
  std::unordered_map<std::string, PackedTextureAsset> m_TextureAssets;

};
