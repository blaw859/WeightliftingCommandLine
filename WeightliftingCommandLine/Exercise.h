#pragma once
#include "Lift.h"

class Exercise
{
public:
	int reps_;

	Exercise(int r) : reps_(r) {}
};

class SingleExercise : public Exercise{
public:
	Movement* movement_;

	SingleExercise(Movement* m, int r) : 
		Exercise(r), 
		movement_(m) {}
};

class ComplexExercise : public Exercise {
public:
	std::vector<std::pair<Movement*, int>> movements_;

	template <typename... Args>
	ComplexExercise(int r, Args... args) :
		Exercise(r),
		movements_{ args... }
	{}
};


	//template<typename... Args>
	//Complex(std::string uuid_string, std::string name, std::string description, Args... args) : 
	//	Movement(uuid_string , name, description),
	//	movements_{args...}
	//{}

