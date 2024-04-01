#pragma once
#include <string>
#include <iostream>

template<typename T>
struct QuestionResult {
	T value;
	bool isValid;
};

template<typename T>
T AskQuestion(const std::string QuestionString, T (*ConversionFunction)(std::string));


struct RoughTime {
	int hours;
	int minutes;
};

//std::ostream& operator<<(std::ostream& os, struct RoughTime& time) {
//	os << time.hours << ":" << time.minutes;
//	return os;
//}

