#ifndef SFEngine_Messager_H
#define SFEngine_Messager_H

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// Copyright(c) 2017 Austin Bailey
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
#include "BasicIncludes.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <vector>
#include <unordered_map>

/************************************************************************/
/*                           Messager                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

  enum class SystemMessageType : std::uint32_t
  {
    // An incoming notification
    Notification = 0,

    // Some type of incoming engine request
    Request,

    // Some type of critical message
    Critical,

    //Activity log
    ActivityLog
  };

  enum class MessageLogLevel : std::uint32_t
  {
    //Just a message - for testing / monitoring - assume a valid state
    Normal = 0,

    // Elevated - for debugging - assume a valid state, but be prepared for unexpected behavior
    Elevated,

    // High - For reporting errors - do not assume a valid state
    High,

    //Critical - for failures - be prepared for a potential crash
    Critical,

    //Unrecoverable - we're going down
    Unrecoverable
  };

  class SystemMessage
  {
  public:
    friend class Engine;

    SystemMessage() = delete;
    SystemMessage(const SystemMessage &);
    SystemMessage(const SystemMessage &&);
    SystemMessage& operator=(const SystemMessage &) = delete;

    SystemMessage(SystemMessageType MessageType, UINT32 Source, UINT32 Destination, const SString &Post);

    SystemMessageType m_MessageType;
    SString           m_PostText;
    UINT32            m_Destination;
    UINT32            m_Source;
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
    static void FlushMessageCache();
    static void PushMessageNotifcations();

    /************************************************************************/
    /* Post / Upload messages                                               */
    /************************************************************************/
    static bool PostToActivityLog(const SystemMessage &Message);
    static bool PostLogMessage(UINT32 Source, const SystemMessage &Message, MessageLogLevel Level);
    static bool PostMessageForInstance(UINT32 Source, UINT32 Destination, const SystemMessage &Message);
    static bool PostMessageForClass(UINT32 Source, const SString &ReceivingClass, const SystemMessage &Message);

    /************************************************************************/
    /* Purge log files                                                      */
    /************************************************************************/
    static void PurgeLogs();
    static void PurgeLogsAtLevel(MessageLogLevel Level);
    static void PurgeLogsToFile(const SString &CachePath, const SString &ActivityPath, const SString &LogPath);

  private:
    //This does not need to be exposed
    //Only the communication interface will be exposed
    static Messager* Get();
    static void InitPriv();
    static void WriteToFile(UINT32 KeyVal, const SystemMessage &Message, SOFStream &File);
    ~Messager();

    UINT32                         m_MaxMessageCountPerCache = 100u;
    static Messager*               m_MessagerInstance;
    STDVector<SystemMessage>       m_NormalLogMessages;
    STDVector<SystemMessage>       m_ElevatedLogMessages;
    STDVector<SystemMessage>       m_HighLogMessages;
    STDVector<SystemMessage>       m_CriticalLogMessages;
    STDVector<SystemMessage>       m_UnrecoverableMessages;

    STDVector<SystemMessage>       m_ActivityLog;
    STDUnorderedMap<UINT32,  STDVector<SystemMessage>>   m_MessageCache;
    STDUnorderedMap<SString, STDVector<SystemMessage>>   m_ClassesMessageCache;
  };

}

#endif // SFEngine_Messager_H
