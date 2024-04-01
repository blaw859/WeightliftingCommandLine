#pragma once
#include <string>
#include <iostream>
#include "Question.h"

template <typename T>
class InputQuestion : public Question<T> {
public:
	const std::string question;
	std::string answer_string;
	bool (*validator)(const std::string&);
	T(*converter)(const std::string&);

	void AskQuestionStoreAnswer() {
		Question<T>::answer = AskQuestion();
	}

	T AskQuestion() {
		std::string user_input;
		std::cout << question;
		std::getline(std::cin, user_input);
		T conversion_result;
	
		while (!validator(user_input)) {
			std::getline(std::cin, user_input);
		}

		return converter(user_input);
	}

	InputQuestion(std::string question, bool (*v)(const std::string&), T(*c)(const std::string&)) 
		: question(question), validator(v), converter(c) {} }; 