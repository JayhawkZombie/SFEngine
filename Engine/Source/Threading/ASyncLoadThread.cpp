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

#include "Threading\ASyncLoader.h"
#include "Level\BasicLevel.h"

namespace Engine
{

  SPtrShared<ASyncThreadStatus> ASyncLevelStreamThread::Launch()
  {
    auto Streamer = Get();
    Streamer->m_LoadingQueue = std::make_shared<std::queue<std::pair<std::string, std::function<SPtrShared<BasicLevel>(void)>>>>();
    Streamer->m_QueueLock = std::make_shared<std::mutex>();
    Streamer->m_StreamerStatus = std::make_shared<ASyncThreadStatus>();

    Messager::PostToActivityLog(SystemMessage(SystemMessageType::ActivityLog, 0, 0, "ASyncLevelStreamThread launching"));
    
    Streamer->m_Thread = std::thread([]() {
      auto Loader = ASyncLevelStreamThread::Get();
      try
      {
        Loader->ThreadLoop();
      }
      catch (std::exception& e)
      {
        std::cerr << "Exception in level streamer" << e.what() << std::endl;
      }
    });

    return Streamer->m_StreamerStatus;
  }

  void ASyncLevelStreamThread::Shutdown()
  {
    auto Streamer = Get();
    Streamer->m_StreamerStatus->StatusLock.lock();
    Streamer->m_StreamerStatus->bHasWork = true;
    Streamer->m_StreamerStatus->bNeedShutdown = true;
    Streamer->m_StreamerStatus->StatusLock.unlock();

    Streamer->m_StreamerStatus->ThreadCond.notify_all();
    if (Streamer->m_Thread.joinable())
      Streamer->m_Thread.join();

    Messager::PostToActivityLog(SystemMessage(SystemMessageType::ActivityLog, 0, 0, "ASyncLevelStreamThread::Shutdown()"));
    delete Streamer;
  }

  bool ASyncLevelStreamThread::Load(std::function<SPtrShared<BasicLevel>(void)> LoadFtn, std::string LevelName)
  {
    auto Streamer = Get();
    if (!Streamer)
      return false;

    Streamer->m_QueueLock->lock();
    Streamer->m_LoadingQueue->push(std::pair<std::string, std::function<SPtrShared<BasicLevel>(void)>>(LevelName, LoadFtn));
    Streamer->m_QueueLock->unlock();

    Streamer->m_StreamerStatus->StatusLock.lock();
    Streamer->m_StreamerStatus->bHasWork = true;
    Streamer->m_StreamerStatus->StatusLock.unlock();

    Streamer->m_StreamerStatus->ThreadCond.notify_all();
    return true;
  }

  std::thread::id ASyncLevelStreamThread::GetThreadID()
  {
    auto Streamer = Get();
    Streamer->m_StreamerStatus->StatusLock.lock();

    std::thread::id id = Streamer->m_StreamerStatus->ThreadID;
    Streamer->m_StreamerStatus->StatusLock.unlock();

    return id;
  }

  SPtrShared<ASyncThreadStatus> ASyncLevelStreamThread::GetThreadStatus()
  {
    auto Streamer = Get();
    if (!Streamer) {
      return nullptr;
    }

    return Streamer->m_StreamerStatus;
  }

  ASyncLevelStreamThread::ASyncLevelStreamThread()
  {
  }

  ASyncLevelStreamThread::~ASyncLevelStreamThread()
  {
  }

  void ASyncLevelStreamThread::ThreadLoop()
  {
    Messager::PostToActivityLog(SystemMessage(SystemMessageType::ActivityLog, 0, 0, "ASyncLevelStreamThread::ThreadLoop()"));
    m_StreamerStatus->StatusLock.lock();
    m_StreamerStatus->ThreadID = std::this_thread::get_id();
    m_StreamerStatus->StatusLock.unlock();

    while (!m_StreamerStatus->bNeedShutdown) {

      //If no work, sleep until we are woken up
      while (!m_StreamerStatus->bHasWork) {
        std::unique_lock<std::mutex> _ulock(m_StreamerStatus->StatusLock);
        m_StreamerStatus->ThreadCond.wait(_ulock);
      }

      //If we need to shutdown, return and quit
      m_StreamerStatus->StatusLock.lock();
      if (m_StreamerStatus->bNeedShutdown) {
        m_StreamerStatus->StatusLock.unlock();
        return;
      }

      m_StreamerStatus->StatusLock.unlock();

      //If the queue is not empty, pop of the queue and attempt to load the level
      std::function<SPtrShared<BasicLevel>(void)> LoadFunction;
      std::string LevelName{ "" };

      if (!m_LoadingQueue->empty()) {
        //Load the level
        m_QueueLock->lock();

        LevelName = m_LoadingQueue->front().first;
        LoadFunction = m_LoadingQueue->front().second;

        m_LoadingQueue->pop();
        m_QueueLock->unlock();

        if (LoadFunction) {
          m_StreamerStatus->StatusLock.lock();
          m_StreamerStatus->bIsLoading = true;
          m_StreamerStatus->StatusLock.unlock();

          SPtrShared<BasicLevel> LoadedLevel;
          try
          {
            LoadedLevel = LoadFunction();
            LevelsLock->lock();
            Levels[LevelName] = LoadedLevel;
            LevelsLock->unlock();
          }
          catch (EngineRuntimeError& e)
          {
            std::cerr << "Exception loading level" << std::endl;
            LoadedLevel = nullptr;
          }
        } // if (LoadFunction)
      } // if (!m_LoadingQueue->empty())
    } // while (!m_StreamStatus->bNeedsShutdown)
  }

  ASyncLevelStreamThread* ASyncLevelStreamThread::Get()
  {
    static ASyncLevelStreamThread* SingleLoadingThread;
    if (!SingleLoadingThread) {
      SingleLoadingThread = new ASyncLevelStreamThread;
    }

    return SingleLoadingThread;
  }

}
