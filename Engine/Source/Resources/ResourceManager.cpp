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

#include "Resources\ResourceManager.h"

#include <iterator>

namespace
{
  std::map<std::string, std::shared_ptr<sf::Texture>> Textures;
  std::map<std::string, std::shared_ptr<sf::Font>> Fonts;
  std::map<std::string, std::shared_ptr<sf::Shader>> Shaders;
  std::map<std::string, std::shared_ptr<sf::SoundBuffer>> SoundBuffers;

  std::map<std::string, std::shared_ptr<sf::Music>> Music;
}

namespace Engine
{

  std::shared_ptr<sf::Texture> LoadTexture(const std::string & path, const std::string &ID)
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

  bool ReleaseTexture(const std::string &ID)
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

  std::shared_ptr<sf::Font> LoadFont(const std::string & path, const std::string &ID)
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

  bool ReleaseFont(const std::string & ID)
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

  std::shared_ptr<sf::Shader> LoadShader(const std::string & path, const std::string &ID, const sf::Shader::Type &type)
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

  bool ReleaseShader(const std::string & ID)
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

  std::shared_ptr<sf::SoundBuffer> LoadSoundBuffer(const std::string & path, const std::string &ID)
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

  bool ReleaseSoundBuffer(const std::string & ID)
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

  void StreamMusic(const std::string & path)
  {
    auto it = Music.find(path);

    if (it != Music.end()) {
      it->second->stop();
      it->second->play();
    }
  }

  void PauseMusic(const std::string & path)
  {
    auto it = Music.find(path);
    if (it != Music.end()) {
      it->second->pause();
    }
  }

  void PlayMusic(const std::string & path)
  {
    auto it = Music.find(path);
    if (it != Music.end()) {
      it->second->play();
    }
  }

  //namespace Resource
  //{

  //  ResourceManager::ResourceManager()
  //  {
  //    PushQueueLock = new std::mutex;
  //    ActiveQueueLock = new std::mutex;
  //    LoadLock = new std::mutex;
  //    WakeUpThread = new std::condition_variable;
  //    StorageAccessLock = new std::mutex;
  //    ThreadQuit = new bool;
  //    *ThreadQuit = false;
  //    ThreadWorkToDo = new bool;
  //    *ThreadWorkToDo = false;

  //    started = false;

  //    VertexShaders = new std::map<std::string, std::shared_ptr<sf::Shader>>;
  //    FragmentShaders = new std::map<std::string, std::shared_ptr<sf::Shader>>;
  //    Textures = new std::map<std::string, std::shared_ptr<sf::Texture>>;
  //    Fonts = new std::map<std::string, std::shared_ptr<sf::Font>>;
  //    SoundBuffers = new std::map<std::string, std::shared_ptr<sf::SoundBuffer>>;
  //    Sounds = new std::map<std::string, std::shared_ptr<sf::Sound>>;

  //    TextureQueue = new std::queue <std::pair<DoubleStringPair
  //      , std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>>;

  //    FragmentShaderQueue = new std::queue<std::pair<DoubleStringPair
  //      , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>>;

  //    VertexShaderQueue = new std::queue<std::pair<DoubleStringPair
  //      , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>>;

  //    FontQueue = new std::queue<std::pair<DoubleStringPair
  //      , std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>>;

  //    SoundQueue = new std::queue<DoubleStringPair>;

  //    ActiveTextureQueue = new std::queue <std::pair<DoubleStringPair
  //      , std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>>;

  //    ActiveFragmentShaderQueue = new std::queue<std::pair<DoubleStringPair
  //      , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>>;

  //    ActiveVertexShaderQueue = new std::queue<std::pair<DoubleStringPair
  //      , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>>;

  //    ActiveFontQueue = new std::queue<std::pair<DoubleStringPair
  //      , std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>>;

  //    ActiveSoundQueue = new std::queue<DoubleStringPair>;

  //    AudioPlayQueue = new std::queue<std::string>;
  //  }

  //  void ResourceManager::Start()
  //  {
  //    if (!started) {
  //      started = true;
  //      LoaderThread = std::thread([this]() {this->ThreadMethod(); });
  //    }
  //  }

  //  ResourceManager::~ResourceManager()
  //  {
  //    *ThreadQuit = true;
  //    WakeUpThread->notify_all();
  //    LoaderThread.join();

  //    delete ActiveQueueLock;
  //    delete PushQueueLock;
  //    delete LoadLock;
  //    delete WakeUpThread;
  //    delete StorageAccessLock;
  //    delete ThreadQuit;
  //    delete ThreadWorkToDo;

  //    delete VertexShaders;
  //    delete FragmentShaders;
  //    delete Textures;
  //    delete Fonts;

  //    delete TextureQueue;
  //    delete FragmentShaderQueue;
  //    delete VertexShaderQueue;
  //    delete FontQueue;
  //    delete AudioPlayQueue;
  //    
  //    delete Sounds;
  //    delete SoundQueue;
  //    delete ActiveSoundQueue;

  //    delete ActiveTextureQueue;
  //    delete ActiveFragmentShaderQueue;
  //    delete ActiveVertexShaderQueue;
  //    delete ActiveFontQueue;
  //  }

  //  void ResourceManager::ReleaseAllResources()
  //  {
  //    for (auto & sound : *Sounds) {
  //      sound.second->stop();
  //      sound.second->resetBuffer();
  //      sound.second.reset();
  //    }
  //  }

  //  void ResourceManager::Shutdown()
  //  {
  //    std::cerr << "Notifying thread of shutdown request" << std::endl;
  //    ReleaseAllResources();
  //    *ThreadQuit = true;
  //    *ThreadWorkToDo = true;
  //    WakeUpThread->notify_all();
  //  }

  //  void ResourceManager::LoadAudio(const std::string &FilePath, const std::string &ID, bool PlayAfterLoading)
  //  {
  //    std::cerr << "----------------------------Loading audio file: " << ID << std::endl;
  //    DoubleStringPair pair(FilePath, ID);
  //    PushQueueLock->lock();
  //    SoundQueue->push(pair);
  //    PushQueueLock->unlock();
  //    *ThreadWorkToDo = true;
  //    WakeUpThread->notify_all();
  //    if (PlayAfterLoading)
  //      AudioPlayQueue->push(ID);
  //  }

  //  void ResourceManager::PlayAudio(const std::string &ID, bool loop)
  //  {
  //    StorageAccessLock->lock();

  //    auto it = Sounds->find(ID);
  //    auto buff = SoundBuffers->find(ID);
  //    //If the audio buffer and audio instance exist in memory (already loaded), then play it
  //    if (it != Sounds->end() && buff != SoundBuffers->end()) {
  //      if (!it->second->getBuffer())
  //        it->second->setBuffer(*(buff->second)); //Bind the buffer if it hasn't already been bound
  //      it->second->setLoop(loop);
  //      it->second->play();
  //    }

  //    StorageAccessLock->unlock();
  //  }

  //  void ResourceManager::PauseAudio(const std::string &ID)
  //  {
  //    StorageAccessLock->lock();

  //    auto it = Sounds->find(ID);
  //    if (it != Sounds->end()) {
  //      if (it->second->getBuffer())
  //        it->second->pause();
  //    }

  //    StorageAccessLock->unlock();
  //  }

  //  void ResourceManager::StopAudio(const std::string &ID)
  //  {
  //    StorageAccessLock->lock();

  //    auto it = Sounds->find(ID);
  //    if (it != Sounds->end()) {
  //      if (it->second->getBuffer())
  //        it->second->stop();
  //    }

  //    StorageAccessLock->unlock();
  //  }

  //  void ResourceManager::GiveTexture(const std::string &ID, std::shared_ptr<sf::Texture> tex)
  //  {
  //    StorageAccessLock->lock();
  //    Textures->emplace(
  //      std::piecewise_construct,
  //      std::make_tuple(ID),
  //      std::make_tuple(tex)
  //    );
  //    StorageAccessLock->unlock();
  //  }

  //  void ResourceManager::RequestTexture(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> callback)
  //  {
  //    DoubleStringPair pair(Filepath, ID);
  //    PushQueueLock->lock();
  //    TextureQueue->push(std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>(pair, callback));
  //    PushQueueLock->unlock();
  //    *ThreadWorkToDo = true;
  //    WakeUpThread->notify_all();
  //  }

  //  void ResourceManager::RequestVertexShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback)
  //  {
  //    DoubleStringPair pair(Filepath, ID);
  //    PushQueueLock->lock();
  //    VertexShaderQueue->push(std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>(pair, callback));
  //    PushQueueLock->unlock();
  //    *ThreadWorkToDo = true;
  //    WakeUpThread->notify_all();
  //  }

  //  void ResourceManager::RequestFragmentShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback)
  //  {
  //    DoubleStringPair pair(Filepath, ID);
  //    PushQueueLock->lock();
  //    FragmentShaderQueue->push(std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>(pair, callback));
  //    PushQueueLock->unlock();
  //    *ThreadWorkToDo = true;
  //    WakeUpThread->notify_all();
  //  }

  //  void ResourceManager::RequestFont(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> callback)
  //  {
  //    DoubleStringPair pair(Filepath, ID);
  //    PushQueueLock->lock();
  //    FontQueue->push(std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>(pair, callback));
  //    PushQueueLock->unlock();
  //    *ThreadWorkToDo = true;
  //    WakeUpThread->notify_all();
  //  }

  //  void ResourceManager::RequestTextureChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> callback)
  //  {
  //    PushQueueLock->lock();

  //    for (auto it = Info.begin(); it != Info.end(); it++) {
  //      TextureQueue->push(
  //        std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>(DoubleStringPair(it->first, it->second), callback));
  //    }

  //    PushQueueLock->unlock();
  //  }

  //  void ResourceManager::RequestVertexShaderChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback)
  //  {
  //    PushQueueLock->lock();

  //    for (auto it = Info.begin(); it != Info.end(); it++) {
  //      VertexShaderQueue->push(
  //        std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>(DoubleStringPair(it->first, it->second), callback));
  //    }

  //    PushQueueLock->unlock();
  //  }

  //  void ResourceManager::RequestFragmentShaderChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback)
  //  {
  //    PushQueueLock->lock();

  //    for (auto it = Info.begin(); it != Info.end(); it++) {
  //      FragmentShaderQueue->push(
  //        std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>(DoubleStringPair(it->first, it->second), callback));
  //    }

  //    PushQueueLock->unlock();
  //  }

  //  void ResourceManager::RequestFontChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> callback)
  //  {
  //    PushQueueLock->lock();

  //    for (auto it = Info.begin(); it != Info.end(); it++) {
  //      FontQueue->push(
  //        std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>(DoubleStringPair(it->first, it->second), callback));
  //    }

  //    PushQueueLock->unlock();
  //  }

  //  std::size_t ResourceManager::GetSizeOfTexturePool() const
  //  {
  //    std::size_t size(0);

  //    for (auto item : *Textures) {
  //      size += sizeof(item);
  //    }
  //    return size;
  //  }

  //  std::size_t ResourceManager::GetSizeOfVertexShaderPool() const
  //  {
  //    std::size_t size(0);

  //    for (auto item : *VertexShaders) {
  //      size += sizeof(item);
  //    }
  //    return size;
  //  }

  //  std::size_t ResourceManager::GetSizeOfFragmentShaderPool() const
  //  {
  //    std::size_t size(0);

  //    for (auto item : *FragmentShaders) {
  //      size += sizeof(item);
  //    }
  //    return size;
  //  }

  //  std::size_t ResourceManager::GetSizeOfFontPool() const
  //  {
  //    std::size_t size(0);

  //    for (auto item : *Fonts) {
  //      size += sizeof(item);
  //    }
  //    return size;
  //  }

//}
}
