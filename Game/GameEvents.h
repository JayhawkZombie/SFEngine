#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include "../SFEngine/Source/Headers/Events/Events.h"
#include "../SFEngine/Source/Headers/Level/Level.h"

enum BasicActions {
	Left,
	Right,
	Up,
	Down,
};

class GameEvents {

	void onLeft(thor::ActionContext<BasicActions> context);
	void onRight(thor::ActionContext<BasicActions> context);
	void onUp(thor::ActionContext<BasicActions> context);
	void onDown(thor::ActionContext<BasicActions> context);

};

#endif //GAMEEVENTS_H