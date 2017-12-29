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

#include <thread>
#include <mutex>
#include <condition_variable>

namespace Engine
{
  class BasicLevel;

  struct ASyncThreadStatus
  {
    bool  bThreadComplete;
    INT32 ThreadStatus;
    bool  bNeedShutdown;
    bool  bHasWork = false;
    bool  bIsLoading = false;
    std::thread::id ThreadID;
    std::mutex StatusLock;
    std::condition_variable   ThreadCond;
    std::function<void(void)> NotifyCompleted;
    SPtrShared<BasicLevel> LoadingLevel;
  };

  struct ASyncThreadRequest
  {
    std::thread::id m_ThreadId;
    std::function<void(void)> m_LoadingFtn;
    std::function<void(void)> m_LoadingDoneFtn;
  };

  class ASyncLevelStreamThread
  {
  public:
    static SPtrShared<ASyncThreadStatus> Launch();
    static void Shutdown();

    static bool Load(std::function<SPtrShared<BasicLevel>(void)> LoadFtn, std::string LevelName);
    static std::thread::id GetThreadID();
    static SPtrShared<ASyncThreadStatus> GetThreadStatus();

  protected:
    ASyncLevelStreamThread();
    ~ASyncLevelStreamThread();
    void ThreadLoop();
    static ASyncLevelStreamThread* Get();
    
    //Level to stream data into
    SPtrShared<BasicLevel> m_StreamingLevel;

    //Lock to secure the queue
    SPtrSharedMutex m_QueueLock;

    //Request to query
    SPtrShared<ASyncThreadStatus> m_StreamerStatus;

    //The thread
    std::thread m_Thread;

    //ID of the thread
    std::thread::id m_ThreadID;

    //Queue to push requests into
    SPtrShared<
      std::queue<
        std::pair<std::string, std::function<SPtrShared<BasicLevel>(void)>>
      >> m_LoadingQueue;
  };

  class ASyncLoadManager
  {
  public:
    static void Init();
    static void Shutdown();

    static ASyncLoadManager& Get();

    static void Launch(std::function<void(void)> LoadingFtn, std::function<void(void)> CompletedFtn);
    static bool QueryFinished();
    static void Halt();
    

  protected:
    ASyncLoadManager();
    ~ASyncLoadManager();



    std::thread m_LoaderThread;
    SPtrShared<std::mutex> m_ThreadMutex;
    SPtrShared<std::mutex> m_ThreadStatusLock;
    SPtrShared<ASyncThreadStatus> m_ThreadCompleted;
  };

}
