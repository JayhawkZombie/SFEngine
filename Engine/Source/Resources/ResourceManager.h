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

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <memory>
#include <iostream>

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>


typedef std::pair<std::string, std::string> DoubleStringPair;

std::shared_ptr<sf::Texture> LoadTexture(const std::string &path, const std::string &ID);
bool ReleaseTexture(const std::string &ID);
void ForceClearTextures();
void ClearTextures();

std::shared_ptr<sf::Font> LoadFont(const std::string &path, const std::string &ID);
bool ReleaseFont(const std::string &path);
void ForceClearFonts();
void ClearFonts();

std::shared_ptr<sf::Shader> LoadShader(const std::string &path, const std::string &ID);
bool ReleaseShader(const std::string &path);
void ForceClearShaders();
void ClearShaders();

std::shared_ptr<sf::SoundBuffer> LoadSoundBuffer(const std::string &path, const std::string &ID);
bool ReleaseSoundBuffer(const std::string &path);
void ForceClearSoundBuffers();
void ClearSoundBuffers();

void StreamMusic(const std::string &path);
void PauseMusic(const std::string &path);
void PlayMusic(const std::string &path);

/*
  Multi-threaded res manager disabled for now. Being redesigned. Placeholder single-threaded one will have to suffice for now
*/

//namespace Resource
//{
//  class ResourceManager
//  {
//  public:
//    ResourceManager();
//    ResourceManager(const ResourceManager &) = delete;
//    ~ResourceManager();

//    void RequestTexture(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> callback);
//    void RequestVertexShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);
//    void RequestFragmentShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);
//    void RequestFont(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> callback);

//    void RequestTextureChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> callback);
//    void RequestVertexShaderChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);
//    void RequestFragmentShaderChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);
//    void RequestFontChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> callback);

//    void GiveTexture(const std::string &ID, std::shared_ptr<sf::Texture> tex);

//    void LoadAudio(const std::string &FilePath, const std::string &ID, bool playAfterLoading);
//    void PlayAudio(const std::string &ID, bool loop);
//    void PauseAudio(const std::string &ID);
//    void StopAudio(const std::string &ID);

//    std::size_t GetSizeOfTexturePool() const;
//    std::size_t GetSizeOfVertexShaderPool() const;
//    std::size_t GetSizeOfFragmentShaderPool() const;
//    std::size_t GetSizeOfFontPool() const;

//    void Shutdown();

//    void Start();

//  private:
//    void ThreadMethod();
//    void LoadTexture(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> callback);
//    void LoadFont(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> callback);
//    void LoadVertexShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);
//    void LoadFragmentShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);

//    void LoadAudioFile(const std::string &FilePath, const std::string &ID);
//    void ReleaseAllResources();

//    void CopyFromPushQueue();
//    void LoadShadersFromActiveQueues();
//    void LoadTexturesFromActiveQueue();
//    void LoadFontsFromActiveQueue();
//    void LoadAudioFromActiveQueue();

//    std::thread LoaderThread;
//    bool *ThreadQuit;
//    bool *ThreadWorkToDo;
//    bool started;

//    std::mutex *PushQueueLock;
//    std::mutex *ActiveQueueLock;
//    std::mutex *LoadLock;
//    std::mutex *StorageAccessLock;

//    std::condition_variable *WakeUpThread;

//    //Oh my, how disgusting
//    std::queue <std::pair<DoubleStringPair
//      , std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>> *TextureQueue;

//    std::queue<std::pair<DoubleStringPair
//      , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>> *VertexShaderQueue;

//    std::queue<std::pair<DoubleStringPair
//      , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>> *FragmentShaderQueue;

//    std::queue<std::pair<DoubleStringPair
//      , std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>> *FontQueue;

//    std::queue<DoubleStringPair> *SoundQueue;

//    std::queue <std::pair<DoubleStringPair
//      , std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>> *ActiveTextureQueue;

//    std::queue<std::pair<DoubleStringPair
//      , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>> *ActiveVertexShaderQueue;

//    std::queue<std::pair<DoubleStringPair
//      , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>> *ActiveFragmentShaderQueue;

//    std::queue<std::pair<DoubleStringPair
//      , std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>> *ActiveFontQueue;

//    std::queue<DoubleStringPair> *ActiveSoundQueue;

//    std::queue<std::string> *AudioPlayQueue;

//    std::map<std::string, std::shared_ptr<sf::Texture>> *Textures;
//    std::map<std::string, std::shared_ptr<sf::Shader>> *VertexShaders;
//    std::map<std::string, std::shared_ptr<sf::Shader>> *FragmentShaders;
//    std::map<std::string, std::shared_ptr<sf::Font>> *Fonts;
//    std::map<std::string, std::shared_ptr<sf::Sound>> *Sounds;
//    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> *SoundBuffers;
//  };

//}
