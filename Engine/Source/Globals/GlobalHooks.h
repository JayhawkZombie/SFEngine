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

#pragma warning( disable : 4503 ) //Disable "decorated name length exceeded, name was truncated"
#pragma warning( disable : 4996 ) //Disable "strcpy may be unsafe"
//Disable "unreferenced local variable" because we catch an exception 
//  & assoc a var name with it, but don't use that name when rethrowing it
#pragma warning( disable : 4101 )
#pragma warning( disable : 4100 ) //Unreferenced formal parameter

#ifdef MessageBoxW
#undef MessageBoxW
#endif

//#include <TGUI\Widgets\MessageBox.hpp>
//typedef tgui::MessageBox tguiMessageBox;

#include <SFML\Graphics.hpp>

#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <unordered_map>

#include "EngineTypes.h"
#include "Resources\ResourceManager.h"
#include "Streams\DataStream.h"
#include "Render\Render.h"
#include "State\DeviceState.h"
#include "UI\UIMacros.h"
#include "Messaging\CoreMessager.h"

#include "ThirdParty/IMGUI\imgui.h"
#include "ThirdParty/IMGUI\imgui-SFML.h"
#include "ThirdParty/cereal\cereal.hpp"
#include "ThirdParty/cereal\archives\json.hpp"
#include <TGUI\TGUI.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>

/* FUCK OFF MICROSOFT! */
#ifdef _WINUSER_
#pragma push_macro("MessageBox")
#undef MessageBox
#undef _WINUSER_
#endif

const std::string EngineVersionString{ "0.0.1" };
const std::string EditorVersionString{ "0.0.1.B-fIncomplete" };
const std::string CORE_PATH{ "./SFEngine/Source/CoreFiles/" };

//Change this to redirect all error output
#define ERR_STREAM std::cerr

//define away some of the longest C++ paths
typedef std::chrono::high_resolution_clock hres_clock;
typedef std::chrono::high_resolution_clock::time_point hres_time_point;

//forward declaration of BasicLevel class for the global Levels object
class BasicLevel;

extern std::shared_ptr<std::mutex> LevelsLock;
extern std::unordered_map<std::string, std::shared_ptr<BasicLevel>> Levels;
extern std::string EntryLevelName;
extern BasicLevel *CurrentLevel;

#ifdef WITH_EDITOR
class Editor;

#define EDITOR_FRIEND \
friend class Editor; 

#define EDITOR_VISIBLE

#define EDITOR_VISIBLE_TYPE(Type,Name) \
EDITOR_VISIBLE \
Type Name;
#else
#define EDITOR_FRIEND
#define EDITOR_VISIBLE
#define EDITOR_VISIBLE_TYPE(Type,Name)\
Type Name;
#endif

#ifdef WITH_EDITOR

#define EDITORONLY_VAR(VarType, VarName)\
VarType VarName;


#else
#define EDITORONLY(VarType, VarName)
#endif //WITH_EDITOR -> EDITORONLY DEFINITION

#define __PREPROC_ID_CONCAT(__X, __Y) __X ## __Y
#define __STRINGIFY_PREPROC_STR(__X) #__X

#define ___INTERNAL__SLASH(S)\
/##S

#define ___INTERNAL__COMMENT \
___INTERNAL__SLASH(/)


#ifdef WITH_EDITOR

#define EDITOR_ONLY

#define EDITOR_ONLY_CODE_BEGIN \
if (true)\
{

#define EDITOR_ONLY_CODE_END \
} \


#else //#ifdef WITH_EDITOR

#define EDITOR_ONLY ___INTERNAL__COMMENT

#define EDITORONLY_CODE_BEGIN \
if(false){

#define EDITORONLY_CODE_END \
}

#endif //#ifdef WITH_EDITOR

//remove this to build the engine without debugging output
#define ENGINE_DEBUG


//Remove this to build the engine without the widget construction debugging output
#define WIDGET_CONSTRUCT_DEBUG_OUT

#ifdef WIDGET_CONSTRUCT_DEBUG_OUT
#define WIDGET_DEBUG_ONLY
#else
#define WIDGET_DEBUG_ONLY ___INTERNAL__COMMENT
#endif //ifdef WIDGET_CONSTRUCT_DEBUG_OUT



#ifdef ENGINE_DEBUG
#define DEBUG_ONLY
#define DEBUG_ONLY_CODE_BEGIN \
if (true)\
{

#define DEBUG_ONLY_CODE_END \
} \

#else //#ifdef ENGINE_DEBUG
#define DEBUG_ONLY ___INTERNAL__COMMENT

#define DEBUG_ONLY_CODE_BEGIN \
if (false)\
{

#define DEBUG_ONLY_CODE_END \
} \


#endif //#ifdef ENGINE_DEBUG



//Testing for microsoft extensions, there are some nice extensions we can use
#ifdef _MSC_EXTENSIONS

#define INLINE _inline
#define MSINLINE __inline
#define FORCEINLINE __forceinline
#define NOINLINE __declspec(noinline)
#define ABSTRACT abstract
#define SEALED sealed

#else

#define INLINE inline
#define MSINLINE inline
#define FORCEINLINE inline
#define NOINLINE
#define ABSTRACT
#define SEALED

#endif



#define MAKE_PARENT(ParentClass) \
typedef ParentClass Super

#ifndef ____PI
#define ____PI 3.141592653f
#endif

//EXTERN DECLARATIONS
extern sf::RenderWindow *currentRenderWindow;
extern std::shared_ptr<sf::Texture> DefaultTexture;
extern sf::Vector2f WindowSize;
extern std::string WindowTitle;
extern sf::Uint32 WindowStyle;
extern std::unordered_set<std::uint32_t> UsedIDs; //IDs that have been used. Can search this to verify an ID has not been used already
extern bool IsIDUsed(const std::uint32_t &ID);
extern void FreeID(const std::uint32_t &ID); //Make an ID available for use again
extern std::uint32_t GenerateID(); //Use to try to generate a unique ID. This will throw an IDException if it cannot generate one after a set number of attempts
extern volatile double TimeScaleFactor;
extern volatile unsigned int FramerateLimit;
extern std::uint32_t MaxIDGenerationAttempts; //max # of times we will try to generate an ID for an item before giving up - defined in Widget.cpp

//ENGINE GLOBAL API EXTERNS
extern sf::Vector2u GetCurrentWindowSize();
  
extern decltype(auto) GetCurrentOpenGLVersionMajor();
extern decltype(auto) GetCurrentOpenGLVersionMinor();
extern decltype(auto) GetCurrentAASetting();
extern decltype(auto) GetCurrentContextSettings();
extern decltype(auto) GetCurrentContext();
extern decltype(auto) GetCurrentTexturePoolSize();
extern decltype(auto) GetCurrentShaderPoolSize();
extern decltype(auto) GetCurrentFramerateSetting();

extern void SetFramerateLimit(unsigned int Limit);
extern void SetVSyncEnabled(bool Enabled);
extern void SetAALevel(unsigned int Level);

extern decltype(auto) GetIsGlobalShadingEnabled();
extern decltype(auto) GetIsStaticShadingEnabled();
extern decltype(auto) GetIsDynamicShadingEnabled();
extern decltype(auto) GetIsStaticShadowingEnabled();
extern decltype(auto) GetIsDynamicShadowingEnabled();
extern decltype(auto) GetIsMultiThreadedLightingEnabled();
extern decltype(auto) GetIsUsingPreComputedLightMaps();
extern decltype(auto) GetCanPhysicsApproxCollision();

extern void AddKeyboardShortcut(const std::vector<sf::Keyboard::Key> &keys, std::function<void(void)> callback);

extern void AddScriptGlobal();

struct RenderSettings;
extern RenderSettings EngineRenderSettings;

void MessageAlert(const std::string &message);
void ConfirmAlert(const std::string &message, std::string OKText = "OK", std::string CancelText = "Cancel", std::function<void(void)> OKcb = []() {}, std::function<void(void)> Cancelcb = []() {});
void Confirm(const std::string &message);
extern void Shutdown();
extern void LoadLevel(const std::string &jsonPath);
extern void SwitchLevel(std::shared_ptr<BasicLevel> Level);
extern void SwitchLevel_RawPtr(BasicLevel *Level);
extern void LoadMainLevel();
extern void LoadLevelByName(const std::string &Name);
extern void ScaleTimeUpdate(const double &factor);

class UserEvent;
class InputDeviceState;

extern DataStream<UserEvent> EngineEventStream;
extern InputDeviceState InputState;

class TimerManager;
extern TimerManager* GetGlobalTimerManager();

#ifdef WITH_EDITOR
class SFEngine;
extern SFEngine *CurrentEngine;
extern volatile bool FlagForClose;
namespace UI {
  class BaseUIElement;
};

extern void AddUI(std::shared_ptr<UI::BaseUIElement> element);
#endif

extern void SetKeyRepeatEnabled(bool);

extern std::shared_ptr<tgui::Gui> GUI;

#define __TO_FLOAT__(VAR)\
static_cast<float>(VAR)
#define __TO_INT__(VAR)\
static_cast<int>(VAR)
#define __INT_FROM_FLOAT__(VAR)\
static_cast<int>(std::round(VAR))
#define __UINT_FROM_FLOAT__(VAR)\
static_cast<std::uint32_t>(std::round(VAR))
