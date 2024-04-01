#include "MenuSession.h"


MenuSession::MenuSession()
{
	lift_store = new LiftStore();
}

void MenuSession::Initialise()
{
	lift_store->LoadLifts();
}

void MenuSession::CleanUp()
{
	lift_store->SaveLifts();
}
