#include "WLCommandUtils.h"
#include <string>
#include <iostream>

template<typename T>
T AskQuestion(const std::string QuestionString, T(*ConversionFunction)(std::string)) {
	std::string user_input;
	std::cout << QuestionString;
	std::getline(std::cin, user_input);
	T conversion_result = NULL;

	do {
		conversion_result = ConversionFunction(user_input);
	} while (conversion_result == NULL);

	return conversion_result;
}

int NoughtToTenValidate(std::string input) {
	int result = stoi(input);
	if (result >= 0 && result <= 10) {
		
	}
	return NULL;
}
