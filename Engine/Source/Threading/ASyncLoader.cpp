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

#include "Threading/ASyncLoader.h"

namespace Engine
{



  void ASyncLoadManager::Init()
  {
  }

  void ASyncLoadManager::Shutdown()
  {
  }

  ASyncLoadManager & ASyncLoadManager::Get()
  {
    static ASyncLoadManager LoaderSingleton;

    return LoaderSingleton;
  }

  void ASyncLoadManager::Launch(std::function<void(void)> LoadingFtn, std::function<void(void)> CompletedFtn)
  {
    auto &Loader = Get();
    Loader.m_ThreadStatusLock->lock();
    Loader.m_ThreadCompleted->NotifyCompleted = CompletedFtn;
    Loader.m_LoaderThread = std::thread(LoadingFtn);
    Loader.m_ThreadStatusLock->unlock();
  }

  bool ASyncLoadManager::QueryFinished()
  {
    bool Done = false;

    auto &Loader = Get();
    Loader.m_ThreadStatusLock->lock();
    Done = Loader.m_ThreadCompleted->bThreadComplete;
    Loader.m_ThreadStatusLock->unlock();

    return Done;
  }

  void ASyncLoadManager::Halt()
  {
  }

  ASyncLoadManager::ASyncLoadManager()
    : m_ThreadCompleted(std::make_shared<ASyncThreadStatus>()),
    m_ThreadMutex(std::make_shared<std::mutex>()),
    m_ThreadStatusLock(std::make_shared<std::mutex>())
  {
  }

  ASyncLoadManager::~ASyncLoadManager()
  {
    if (m_LoaderThread.joinable())
      m_LoaderThread.join();

    m_ThreadCompleted.reset();
    m_ThreadMutex.reset();
    m_ThreadStatusLock.reset();
  }

}
