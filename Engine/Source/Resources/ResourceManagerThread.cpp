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

namespace Engine
{

  //namespace Resource
  //{

  //  void ResourceManager::ThreadMethod()
  //  {
  //    //std::cerr << "Beginning ThreadMethod()" << std::endl;

  //    while (!*ThreadQuit)
  //    {
  //      //std::cerr << "Beginning thread loop" << std::endl;

  //      std::unique_lock<std::mutex> __lock(*LoadLock);

  //      while (!*ThreadWorkToDo) {
  //        WakeUpThread->wait(__lock);
  //      }
  //      *ThreadWorkToDo = false;
  //      if (*ThreadQuit)
  //        break;

  //      //std::cerr << "Thread woken up, not time to quit" << std::endl;

  //      while (!FontQueue->empty() || !VertexShaderQueue->empty() || !FragmentShaderQueue->empty() || !TextureQueue->empty() || !SoundQueue->empty())
  //      {
  //        //std::cerr << "Copying from push queue" << std::endl;
  //        PushQueueLock->lock();
  //        CopyFromPushQueue();
  //        PushQueueLock->unlock();

  //        //Now we've copied everything from the push queue, 
  //        //Now we can load using the values in the Active queues without stalling the main thread
  //        //and still allowing the main thread to submit requests
  //        //std::cerr << "Loading from active queue" << std::endl;
  //        LoadShadersFromActiveQueues();
  //        LoadFontsFromActiveQueue();
  //        LoadTexturesFromActiveQueue();
  //        LoadAudioFromActiveQueue();
  //      }

  //    }
  //    //std::cerr << "ThreadQuit set, returning from thread" << std::endl;

  //  } //ThreadMethod

  //  void ResourceManager::CopyFromPushQueue()
  //  {
  //    while (!TextureQueue->empty()) {
  //      auto TOP = TextureQueue->front();

  //      ActiveTextureQueue->push(TOP);
  //      TextureQueue->pop();
  //    }

  //    while (!FontQueue->empty()) {
  //      auto TOP = FontQueue->front();

  //      ActiveFontQueue->push(TOP);
  //      FontQueue->pop();
  //    }

  //    while (!VertexShaderQueue->empty()) {
  //      auto TOP = VertexShaderQueue->front();

  //      ActiveVertexShaderQueue->push(TOP);
  //      VertexShaderQueue->pop();
  //    }

  //    while (!FragmentShaderQueue->empty()) {
  //      auto TOP = FragmentShaderQueue->front();

  //      ActiveFragmentShaderQueue->push(TOP);
  //      FragmentShaderQueue->pop();
  //    }

  //    while (!SoundQueue->empty()) {
  //      auto TOP = SoundQueue->front();

  //      ActiveSoundQueue->push(TOP);
  //      SoundQueue->pop();
  //    }
  //  }

  //  void ResourceManager::LoadAudioFromActiveQueue()
  //  {
  //    ActiveQueueLock->lock();

  //    //SFML has a limit of 255 sound clips that can be loaded at one time
  //    while (!ActiveSoundQueue->empty() && Sounds->size() < 255) {
  //      auto TOP = ActiveSoundQueue->front();
  //      LoadAudioFile(TOP.first, TOP.second);
  //      ActiveSoundQueue->pop();
  //    }

  //    ActiveQueueLock->unlock();
  //  }

  //  void ResourceManager::LoadShadersFromActiveQueues()
  //  {
  //    ActiveQueueLock->lock();

  //    while (!ActiveVertexShaderQueue->empty()) {
  //      auto TOP = ActiveFragmentShaderQueue->front();
  //      LoadFragmentShader(TOP.first.first, TOP.first.second, TOP.second);
  //      ActiveFragmentShaderQueue->pop();
  //    }

  //    while (!ActiveFragmentShaderQueue->empty()) {
  //      auto TOP = ActiveVertexShaderQueue->front();
  //      LoadVertexShader(TOP.first.first, TOP.first.second, TOP.second);
  //      ActiveVertexShaderQueue->pop();
  //    }

  //    ActiveQueueLock->unlock();
  //  }

  //  void ResourceManager::LoadTexturesFromActiveQueue()
  //  {
  //    ActiveQueueLock->lock();

  //    while (!ActiveTextureQueue->empty()) {
  //      auto TOP = ActiveTextureQueue->front();
  //      LoadTexture(TOP.first.first, TOP.first.second, TOP.second);
  //      ActiveTextureQueue->pop();
  //    }

  //    ActiveQueueLock->unlock();
  //  }

  //  void ResourceManager::LoadFontsFromActiveQueue()
  //  {
  //    ActiveQueueLock->lock();

  //    while (!ActiveFontQueue->empty()) {
  //      auto TOP = ActiveFontQueue->front();
  //      LoadFont(TOP.first.first, TOP.first.second, TOP.second);
  //      ActiveFontQueue->pop();
  //    }

  //    ActiveQueueLock->unlock();
  //  }

  //  void ResourceManager::LoadAudioFile(const std::string &FilePath, const std::string &ID)
  //  {
  //    std::cerr << "----------------------Performing audio loading" << std::endl;
  //    StorageAccessLock->lock();

  //    auto it = Sounds->find(ID);
  //    if (it != Sounds->end()) {
  //      std::cerr << "----------------------------Audio file: " << ID << " already loaded" << std::endl;
  //    }
  //    else {
  //      auto sound = std::shared_ptr<sf::Sound>(new sf::Sound);
  //      auto buffer = std::shared_ptr<sf::SoundBuffer>(new sf::SoundBuffer);

  //      std::cerr << "----------------------------Emplacing audio and buffer" << std::endl;
  //      Sounds->emplace(std::piecewise_construct,
  //                      std::make_tuple(ID),
  //                      std::make_tuple(sound));
  //      SoundBuffers->emplace(std::piecewise_construct,
  //                            std::make_tuple(ID),
  //                            std::make_tuple(buffer));

  //      buffer->loadFromFile(FilePath);
  //      sound->setBuffer(*buffer);
  //    }

  //    StorageAccessLock->unlock();
  //    while (!AudioPlayQueue->empty()) {
  //      StorageAccessLock->lock();
  //      std::string TOP = AudioPlayQueue->front();
  //      std::cerr << "Playing audio file: " << TOP << std::endl;
  //      AudioPlayQueue->pop();
  //      auto audio = Sounds->find(TOP);
  //      if (audio != Sounds->end())
  //        audio->second->play();
  //      StorageAccessLock->unlock();
  //    }
  //  }

  //  void ResourceManager::LoadTexture(const std::string &Filepath, 
  //                                    const std::string &ID, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> cb)
  //  {
  //    StorageAccessLock->lock();
  //    
  //    auto it = Textures->find(ID);
  //    if (it != Textures->end()) {
  //      //std::cerr << "Texture already loaded into memory (Address: " << it->second.get() << std::endl;
  //      cb(it->second, ID);
  //    }
  //    else {
  //      auto tex = std::shared_ptr<sf::Texture>(new sf::Texture);
  //      tex->loadFromFile(Filepath);
  //      Textures->emplace(std::piecewise_construct
  //                     , std::make_tuple(ID)
  //                     , std::make_tuple(tex));
  //      if (cb)
  //        cb(tex, ID);
  //    }

  //    StorageAccessLock->unlock();
  //  }

  //  void ResourceManager::LoadFont(const std::string &Filepath, 
  //                                 const std::string &ID, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> cb)
  //  {
  //    StorageAccessLock->lock();

  //    auto it = Fonts->find(ID);
  //    if (it != Fonts->end()) {
  //      cb(it->second, ID);
  //    }
  //    else {
  //      auto fnt = std::shared_ptr<sf::Font>(new sf::Font);
  //      fnt->loadFromFile(Filepath);
  //      Fonts->emplace(std::piecewise_construct
  //                  , std::make_tuple(ID)
  //                  , std::make_tuple(fnt));
  //      if (cb)
  //        cb(fnt, ID);
  //    }

  //    StorageAccessLock->unlock();
  //  }

  //  void ResourceManager::LoadVertexShader(const std::string &Filepath, 
  //                                         const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> cb)
  //  {
  //    StorageAccessLock->lock();

  //    auto it = VertexShaders->find(ID);
  //    if (it != VertexShaders->end()) {
  //      cb(it->second, ID);
  //    }
  //    else {
  //      auto shader = std::shared_ptr<sf::Shader>(new sf::Shader);
  //      shader->loadFromFile(Filepath, sf::Shader::Vertex);
  //      VertexShaders->emplace(std::piecewise_construct
  //                           , std::make_tuple(ID)
  //                           , std::make_tuple(shader));
  //      if (cb)
  //        cb(shader, ID);
  //    }

  //    StorageAccessLock->unlock();
  //  }

  //  void ResourceManager::LoadFragmentShader(const std::string &Filepath, 
  //                                           const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> cb)
  //  {
  //    StorageAccessLock->lock();

  //    auto it = FragmentShaders->find(ID);
  //    if (it != FragmentShaders->end()) {
  //      cb(it->second, ID);
  //    }
  //    else {
  //      auto shader = std::shared_ptr<sf::Shader>(new sf::Shader);
  //      shader->loadFromFile(Filepath, sf::Shader::Fragment);
  //      FragmentShaders->emplace(std::piecewise_construct
  //                             , std::make_tuple(ID)
  //                             , std::make_tuple(shader));
  //      if (cb)
  //        cb(shader, ID);
  //    }

  //    StorageAccessLock->unlock();
  //  }

  //}

}
