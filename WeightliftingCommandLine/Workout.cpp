#include "Workout.h"

Workout::Workout() : 
	date_(boost::gregorian::not_a_date_time),
	session_note_(""),
	sleep_(0),
	nutrition_(0),
	fatigue_(0),
	exercises_({}),
	start_time_(boost::gregorian::not_a_date_time),
	end_time_(boost::gregorian::not_a_date_time)
{}


Workout::Workout(boost::gregorian::date date, std::string note, int sleep, int nutrition, int fatigue, RoughTime st, RoughTime et) : 
	date_(date),
	session_note_(note),
	sleep_(sleep),
	nutrition_(nutrition),
	fatigue_(fatigue),
	exercises_({}),
	start_time_(st),
	end_time_(et)
{}

Workout::Workout(boost::gregorian::date date, int sleep, int nutrition, int fatigue, RoughTime st, RoughTime et) : 
	date_(date),
	session_note_(""),
	sleep_(sleep),
	nutrition_(nutrition),
	fatigue_(fatigue),
	exercises_({}),
	start_time_(st),
	end_time_(et)
{}

Workout Workout::CreateWorkoutFromUser()
{
	std::string date, session_note, sleep, nutrition, fatigue, start_time, end_time;
	std::vector<std::string> exercises;
	Workout workout;

	std::cout << "What is the date of the workout (DDMMYYYY): ";
	std::getline(std::cin, date);
	std::cout << "\n";

	std::cout << "From 0-10 how good was your sleep the previous night: ";
	std::getline(std::cin, sleep);
	std::cout << "\n";

	std::cout << "From 0-10 how was your nutrition leading up to this workout: ";
	std::getline(std::cin, nutrition);
	std::cout << "\n";

	std::cout << "From 0-10 how fatigued were you while doing this workout: ";
	std::getline(std::cin, fatigue);
	std::cout << "\n";

	std::cout << "What time did the workout start (HHmm): ";
	std::getline(std::cin, start_time);
	std::cout << "\n";

	std::cout << "What time did the workout end (HHmm): ";
	std::getline(std::cin, end_time);
	std::cout << "\n";



	return workout;
}
