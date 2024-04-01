#pragma once

template <typename T>
class Question {
public:
	T answer;

	virtual void AskQuestionStoreAnswer() = 0;
	virtual T AskQuestion() = 0;
};
