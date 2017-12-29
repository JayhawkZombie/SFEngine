#ifndef THOR_ANIMATION_WRAPPER
#define THOR_ANIMATION_WRAPPER

#include "../BasicIncludes.h"
#include "../Engine/BaseEngineInterface.h"
#include <Thor/Animations.hpp>

namespace Engine
{
	void registerAnimation(std::string filename, std::string id, float frametime, int number_of_frames);
}
#endif //THOR_ANIMATION_WRAPPER