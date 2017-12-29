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

#include "Logging\Logger.h"

namespace Engine
{

  Logger::Logger()
    : Lock(std::shared_ptr<std::mutex>(new std::mutex)),
    QueueLock(std::shared_ptr<std::mutex>(new std::mutex)),
    MessageQueue(std::shared_ptr<std::queue<std::string>>(new std::queue<std::string>)),
    WaitVar(std::shared_ptr<std::condition_variable>(new std::condition_variable)),
    QuitAlert(std::shared_ptr<bool>(new bool{ false })),
    MessageAlert(std::shared_ptr<bool>(new bool{ false })),
    Stopped(std::shared_ptr<bool>(new bool{ false })),
    FileFailure(std::shared_ptr<bool>(new bool{ false })),
    OutStream(std::shared_ptr<std::ofstream>(new std::ofstream))
  {

  }

  Logger::~Logger()
  {

  }

  void Logger::Start()
  {
      LOGGER_THREAD = std::thread(
        [this]() 
      {
        std::unique_lock<std::mutex> _lock(*(this->Lock));
        std::stringstream message;
        std::time_t t;

        while (!*(this->QuitAlert)) {

          while (!*(this->MessageAlert)) {
            this->WaitVar->wait(_lock);
          }

          if (!*(this->FileFailure)) {

            //while (!(this->MessageQueue->empty())) {
            //  t = std::time(nullptr);
            //  message.clear();
            //  message << std::put_time(std::localtime(&t), "%c %Z");
            //  message << " : " << this->MessageQueue->front();

            //  this->MessageQueue->pop();
            //  *OutStream << message.str();
            //  *OutStream << std::endl;
            //}
          }
          
          *(this->MessageAlert) = false;

        }
      
      }
      );

      //std::thread([this]()
      //{
        //std::unique_lock<std::mutex> _lock(*(this->Lock));
        //std::stringstream message;
        //std::time_t t;

        //while (!(this->QuitAlert)) {

        //  while (!(this->MessageAlert)) {
        //    WaitVar->wait(_lock);
        //  }

        //  if (!*(this->FileFailure)) {
        //    this->QueueLock->lock();

        //    while (!this->MessageQueue->empty()) {

        //      t = std::time(nullptr);
        //      message.clear();
        //      message << std::put_time(std::localtime(&t), "%c %Z");
        //      message << " : " << this->MessageQueue->front();
        //      
        //      *OutStream << message.str() << "\n";
        //      std::cerr << "Logger message: " << message.str() << std::endl; 
        //      this->MessageQueue->pop();
        //    }

        //    this->QueueLock->unlock();
        //    *(this->MessageAlert) = false;
        //  } //if !FileFailure

        //}//while !QuitAlert

        //return;
      //});
  }

  void Logger::SetFile(const std::string &filepath)
  {
    OutStream->open(filepath);
    if (OutStream->fail())
      *FileFailure = true;
  }

  void Logger::Stop()
  {
    std::unique_lock<std::mutex> lock(*Lock);
    *QuitAlert = true;
    *MessageAlert = true;
    WaitVar->notify_all();
    LOGGER_THREAD.join();

    OutStream->close();
  }

  void Logger::LogToFile(const std::string &message)
  {
    std::unique_lock<std::mutex> _lock(*Lock);
    *MessageAlert = true;
    *QuitAlert = false;
    MessageQueue->push(message);
    WaitVar->notify_all();
  }

}
