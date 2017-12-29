#ifndef EVENTS_H
#define EVENTS_H

#include <Thor\Input.hpp>

namespace Engine {
	Events();
	Events(const Events &);
	~Events();

	void onLeft(thor::ActionContext<MyAction> context);
	void onRight(thor::ActionContext<MyAction> context);
	void onUp(thor::ActionContext<MyAction> context);
	void onDown(thor::ActionContext<MyAction> context);
}

#endif //EVENTS_H