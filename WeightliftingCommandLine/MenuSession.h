#pragma once
#include "Storage.h"

class MenuSession {
public:
	LiftStore* lift_store;

	MenuSession();
	void Initialise();
	void CleanUp();
};

