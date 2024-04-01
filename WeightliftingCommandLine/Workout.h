#pragma once
#include <boost/date_time.hpp>
#include "Exercise.h"
#include "WLCommandUtils.h"

/*
* @class Workout
*/
class Workout
{
public:
	boost::gregorian::date date_;
	std::string session_note_;
	int sleep_;
	int nutrition_;
	int fatigue_;
	std::vector<Exercise> exercises_;
	RoughTime start_time_;
	RoughTime end_time_;

	Workout();
	Workout(boost::gregorian::date date, std::string note, int sleep, int nutrition, int fatigue, RoughTime st, RoughTime et);
	Workout(boost::gregorian::date date, int sleep, int nutrition, int fatigue, RoughTime st, RoughTime et);
	static Workout CreateWorkoutFromUser();
};

