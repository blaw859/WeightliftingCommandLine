#pragma once
#include <string>
#include <boost/date_time.hpp>
#include <regex>
#include "OptionsQuestion.h"
#include "InputQuestion.h"
#include "Workout.h"
#include "WLCommandUtils.h"
#include "Lift.h"
#include "Storage.h"
#include "MenuSession.h"

enum MenuState
{
	None,
	Start
};

int StartMenu(MenuSession* session);
bool ValidateDate(const std::string& date_string);
boost::gregorian::date ParseDate(const std::string& date_string);
bool ValidateYN(const std::string& yn_string);
bool ConvertYN(const std::string& yn_string);
bool ValidateYes(const std::string& input_string);
std::string NoConvert(const std::string& input_string);
bool OneToTenValid(const std::string& in_string);
int StringConvert(const std::string& in_string);
bool ValidateTime(const std::string& in_string);
struct RoughTime StringToTime(const std::string& time_string);
std::ostream& operator<<(std::ostream& os, RoughTime time);
Workout* AddWorkout();
Movement* AddMovement(LiftStore* lift_store);
Movement* AddBaseMovementName(std::string name);
Movement* AddBaseMovement();
Complex* AddComplex(LiftStore* lift_store);
void AddAndProcessMovement(LiftStore* lift_store);
