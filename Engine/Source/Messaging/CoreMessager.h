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
#include <cinttypes>

enum class SystemMessageType : std::uint32_t
{
  // An incoming notification
  Notification = 0                    ,

  // Some type of incoming engine request
  Request                             ,

  // Some type of critical message
  Critical                            ,

  //Activity log
  ActivityLog
};

enum class MessageLogLevel : std::uint32_t
{
  //Just a message - for testing / monitoring - assume a valid state
  Normal = 0                          ,

  // Elevated - for debugging - assume a valid state, but be prepared for unexpected behavior
  Elevated                            ,

  // High - For reporting errors - do not assume a valid state
  High                                ,

  //Critical - for failures - be prepared for a potential crash
  Critical                            ,

  //Unrecoverable - we're going down
  Unrecoverable
};

class SystemMessage
{
public:
  friend class SFEngine;

  SystemMessage() = delete;
  SystemMessage(const SystemMessage &);
  SystemMessage(const SystemMessage &&);
  SystemMessage& operator=(const SystemMessage &) = delete;

  SystemMessage(SystemMessageType MessageType, std::uint32_t Source, std::uint32_t Destination, const std::string &Post);

  SystemMessageType m_MessageType;
  std::string       m_PostText;
  std::uint32_t     m_Destination;
  std::uint32_t     m_Source;
};

/*!
  * \class Messager
  *
  * \brief Core internal messaging system
  *
  * \author Kurt
  * \date April 2017
  */
class Messager
{
public:
  static void Init();
  static void Shutdown();


  //************************************
  // Method:    FlushMessageCache
  // FullName:  Engine::Messager::FlushMessageCache
  // Access:    public 
  // Returns:   void
  // Qualifier:
  // Purpose:   Flush the entire message cache (without) triggering notifications
  //            Effectively a silent cleanup of messages that piled up
  //************************************
  static void FlushMessageCache();


  //************************************
  // Method:    PostMessageForInstance
  // FullName:  Engine::Messager::PostMessageForInstance
  // Access:    public 
  // Returns:   bool
  // Qualifier:
  // Parameter: std::uint32_t Source - The InternalID of the sending object
  // Parameter: std::uint32_t Destination - The InternalID of the receiving object
  // Purpose:   Post a message to be delivered directly to an instantiated object
  //************************************
  static bool PostMessageForInstance(std::uint32_t Source, std::uint32_t Destination, const SystemMessage &Message);


  //************************************
  // Method:    PostMessageForClass
  // FullName:  Engine::Messager::PostMessageForClass
  // Access:    public 
  // Returns:   bool
  // Qualifier:
  // Parameter: std::uint32_t Source
  // Parameter: const std::string ReceivingClass
  // Purpose:   Post a message to be seen by instances of said class
  //************************************
  static bool PostMessageForClass(std::uint32_t Source, const std::string ReceivingClass, const SystemMessage &Message);


  //************************************
  // Method:    PushMessageNotifcations
  // FullName:  Engine::Messager::PushMessageNotifcations
  // Access:    public 
  // Returns:   void
  // Qualifier:
  // Purpose:   Force the delivery of all possible notifications
  //************************************
  static void PushMessageNotifcations();


  //************************************
  // Method:    PostLogMessage
  // FullName:  Engine::Messager::PostLogMessage
  // Access:    public static 
  // Returns:   bool
  // Qualifier:
  // Parameter: std::uint32_t Source
  // Parameter: const SystemMessage & Message
  // Purpose:   Post a message to be logged
  //************************************
  static bool PostLogMessage(std::uint32_t Source, const SystemMessage &Message, MessageLogLevel Level);


  //************************************
  // Method:    PurgeLogs
  // FullName:  Engine::Messager::PurgeLogs
  // Access:    public static 
  // Returns:   void
  // Qualifier:
  // Purpose:   Purge all log messages
  //************************************
  static void PurgeLogs();


  //************************************
  // Method:    PurgeLogsToFile
  // FullName:  Engine::Messager::PurgeLogsToFile
  // Access:    public static 
  // Returns:   void
  // Qualifier:
  // Parameter: const std::string & Path
  // Purpose:   Purge all messages, but record them in a file for later viewing
  //************************************
  static void PurgeLogsToFile(const std::string &CachePath, const std::string &ActivityPath, const std::string &LogPath);


  //************************************
  // Method:    PurgeLogsAtLevel
  // FullName:  Engine::Messager::PurgeLogsAtLevel
  // Access:    public static 
  // Returns:   void
  // Qualifier:
  // Parameter: MessageLogLevel Level
  // Purpose:   Purge all the messages at the specified message level
  //************************************
  static void PurgeLogsAtLevel(MessageLogLevel Level);


  static bool PostToActivityLog(const SystemMessage &Message);
private:
  //This does not need to be exposed
  //Only the communication interface will be exposed
  static Messager* Get();
  static void InitPriv();
  static void WriteToFile(std::uint32_t KeyVal, const SystemMessage &Message, std::ofstream &File);
  ~Messager();

  std::uint32_t                    m_MaxMessageCountPerCache = 100u;
  static Messager*                 m_MessagerInstance;
  std::vector<SystemMessage>       m_NormalLogMessages;
  std::vector<SystemMessage>       m_ElevatedLogMessages;
  std::vector<SystemMessage>       m_HighLogMessages;
  std::vector<SystemMessage>       m_CriticalLogMessages;
  std::vector<SystemMessage>       m_UnrecoverableMessages;

  std::vector<SystemMessage>       m_ActivityLog;

  std::unordered_map<std::uint32_t, std::vector<SystemMessage>> m_MessageCache;
  std::unordered_map<std::string, std::vector<SystemMessage>>   m_ClassesMessageCache;
};
