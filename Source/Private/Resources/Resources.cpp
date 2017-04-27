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
/*                         Internal  Headers                            */
/************************************************************************/
#include "Resources/Resources.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        Resources                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

namespace SFEngine
{

  namespace
  {
    SStringTextureMap     Textures;
    SStringFontMap        Fonts;
    SStringShaderMap      Shaders;
    SStringSoundBufferMap SoundBuffers;
    SStringMusicMap       Music;
  }


  SharedTexture LoadTexture(const SString & path, const SString &ID)
  {
    auto it = Textures.find(ID);
    if (it != Textures.end())
      return it->second;
    else {
      Textures[path] = std::make_shared<sf::Texture>();
      auto _it = Textures[path];
      if (!_it->loadFromFile(path)) {
        std::cerr << "Unable to load : " << path << " from file " << std::endl;
        return nullptr;
      }

      return _it;
    }
  }

  bool ReleaseTexture(const SString &ID)
  {
    auto it = Textures.find(ID);
    if (it != Textures.end()) {
      it->second.reset();

      return (it->second.use_count() == 0);
    }

    return false;
  }

  void ForceClearTextures()
  {
    for (auto & tex : Textures) {
      delete tex.second.get();
    }
    Textures.clear();
  }

  void ClearTextures()
  {
    Textures.clear();
  }

  SharedFont LoadFont(const SString & path, const SString &ID)
  {
    auto it = Fonts.find(ID);
    if (it != Fonts.end()) {
      return it->second;
    }

    else {
      Fonts[ID] = std::make_shared<sf::Font>();
      auto _it = Fonts[ID];

      if (!_it->loadFromFile(path))
        return nullptr;
      return _it;
    }
  }

  bool ReleaseFont(const SString & ID)
  {
    auto it = Fonts.find(ID);
    if (it != Fonts.end()) {
      it->second.reset();

      return (it->second.use_count() == 0);
    }

    return false;
  }

  void ForceClearFonts()
  {
    for (auto & font : Fonts)
      delete font.second.get();

    Fonts.clear();
  }

  void ClearFonts()
  {
    Fonts.clear();
  }

  std::shared_ptr<sf::Shader> LoadShader(const SString & path, const SString &ID, const sf::Shader::Type &type)
  {
    auto it = Shaders.find(ID);

    if (it != Shaders.end())
      return it->second;
    else {
      Shaders[ID] = std::make_shared<sf::Shader>();
      auto _it = Shaders[ID];
      if (!_it->loadFromFile(path, type))
        return nullptr;
      return _it;
    }
  }

  bool ReleaseShader(const SString & ID)
  {
    auto it = Shaders.find(ID);
    if (it != Shaders.end()) {
      it->second.reset();

      return (it->second.use_count() == 0);
    }

    return false;
  }

  void ForceClearShaders()
  {
    for (auto & shader : Shaders)
      delete shader.second.get();

    Shaders.clear();
  }

  void ClearShaders()
  {
    Shaders.clear();
  }

  SharedSoundBuffer LoadSoundBuffer(const SString & path, const SString &ID)
  {
    auto it = SoundBuffers.find(ID);
    if (it != SoundBuffers.end())
      return it->second;
    else {
      SoundBuffers[ID] = std::make_shared<sf::SoundBuffer>();
      auto _it = SoundBuffers[ID];

      if (!_it->loadFromFile(path))
        return nullptr;
      return _it;
    }
  }

  bool ReleaseSoundBuffer(const SString & ID)
  {
    auto it = SoundBuffers.find(ID);
    if (it != SoundBuffers.end()) {
      it->second.reset();
      return (it->second.use_count() == 0);
    }

    return false;
  }

  void ForceClearSoundBuffers()
  {
    for (auto & sndbuf : SoundBuffers)
      sndbuf.second.reset();

    SoundBuffers.clear();
  }

  void ClearSoundBuffers()
  {
    SoundBuffers.clear();
  }

  void StreamMusic(const SString & path)
  {
    auto it = Music.find(path);

    if (it != Music.end()) {
      it->second->stop();
      it->second->play();
    }
  }

  void PauseMusic(const SString & path)
  {
    auto it = Music.find(path);
    if (it != Music.end()) {
      it->second->pause();
    }
  }

  void PlayMusic(const SString & path)
  {
    auto it = Music.find(path);
    if (it != Music.end()) {
      it->second->play();
    }
  }


} // namespace SFEngine
