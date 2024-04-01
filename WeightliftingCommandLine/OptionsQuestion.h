#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "Question.h"

class OptionsQuestion : public Question<int> {
public:
	std::vector<std::string> question_strings;
	
	OptionsQuestion(std::vector<std::string> qs) : question_strings(qs) {}

	void AskQuestionStoreAnswer() {
		answer = AskQuestion();
	}

	int AskQuestion() {
		for (int i = 0; i < question_strings.size(); i++) {
			std::cout << i + 1 << ". " << question_strings[i] << "\n";
		}
		std::string user_input;

		std::getline(std::cin, user_input);

		if (user_input.size() > static_cast<int>(log10(question_strings.size()))+1) {
			return AskQuestion();
		}

		int result = stoi(user_input);

		if (result <= 0 || result > question_strings.size()) {
			return AskQuestion();
		}
		return result;
	}
};
