#include "Menu.h"


enum MenuState MenuState = None;


int StartMenu(MenuSession* session) {
	OptionsQuestion q({ "Add workout", "Add exercise", "View sessions", "View exercises", "Exit"});
	int response = q.AskQuestion();

	switch (response)
	{
	case 1:
		AddWorkout();
		break;
	case 2:
		AddAndProcessMovement(session->lift_store);
		break;
	case 3:
		std::cout << "Option not yet implemented" << "\n";
		exit(1);
		break;
	case 4:
		std::cout << "Option not yet implemented" << "\n";
		exit(1);
		break;
	case 5:
		return 1;
	default:
		break;
	}
}

void AddAndProcessMovement(LiftStore* lift_store) {
	Movement* mvmt = AddMovement(lift_store);
	if (auto complex = dynamic_cast<Complex*>(mvmt)) {
		for (auto sub_mvmt : complex->movements_) {
			lift_store->AddLift(sub_mvmt.first);
		}
	}
	lift_store->AddLift(mvmt);
}


bool ValidateDate(const std::string& date_string) {
	std::regex date_regex("\\d{4}-\\d{2}-\\d{2}");
	return std::regex_match(date_string, date_regex);
}

boost::gregorian::date ParseDate(const std::string& date_string) {
	    try {
        // Parse the date string into Boost Gregorian date
        return boost::gregorian::from_string(date_string);
    } catch (const std::exception& e) {
        // Catch any parsing errors
        std::cerr << "Error parsing date: " << e.what() << std::endl;
        return boost::gregorian::date(boost::gregorian::not_a_date_time);
    }
}

bool ValidateYN(const std::string& yn_string) {
	std::regex pattern("[YyNn]");
	return std::regex_match(yn_string, pattern);
}

bool ConvertYN(const std::string& yn_string) {
	if (yn_string == "y" || yn_string == "Y") {
		return true;
	}
	return false;
}

bool ValidateYes(const std::string& input_string) {
	return true;
}

std::string NoConvert(const std::string& input_string) {
	return input_string;
}

bool OneToTenValid(const std::string& in_string) {
	if (in_string.size() == 0 || in_string.size() > 2) {
		return false;
	}
	int input = stoi(in_string);
	if (input < 0 || input > 10) {
		return false;
	}
	return true;
}

int StringConvert(const std::string& in_string) {
	return stoi(in_string);
}

bool ValidateTime(const std::string& in_string) {
	std::regex pattern("^([01]?[0-9]|2[0-3]):[0-5][0-9]$");
	return std::regex_match(in_string, pattern);
}

struct RoughTime StringToTime(const std::string& time_string) {
	size_t pos = time_string.find(':');
	struct RoughTime rt(std::stoi(time_string.substr(0, pos)), std::stoi(time_string.substr(pos + 1)));
	return rt;
}


std::ostream& operator<<(std::ostream& os, RoughTime time) {
	os << time.hours << ":" << time.minutes;
	return os;
}

Workout* AddWorkout() {
	InputQuestion date_q("On what date did the workout take place? (YYYY-MM-DD)\n", ValidateDate, ParseDate);
	InputQuestion has_goal_note_q("Would you like to add your goals for this session?\n", ValidateYN, ConvertYN);
	InputQuestion goal_note_input("Please input your session goals\n", ValidateYes, NoConvert);
	InputQuestion sleep_q("How good was your sleep the night before this session\n", OneToTenValid, StringConvert);
	InputQuestion nutrition_q("How good was your nutrition in the 24 hours leading up to this session\n", OneToTenValid, StringConvert);
	InputQuestion fatigue_q("How fatigued were you in this session\n", OneToTenValid, StringConvert);
	InputQuestion start_time_q("What time did your session start\n", ValidateTime, StringToTime);
	InputQuestion finish_time_q("What time did your session finish\n", ValidateTime, StringToTime);

	std::string session_note = "";
	boost::gregorian::date sesh_date = date_q.AskQuestion();
	bool has_note = has_goal_note_q.AskQuestion();
	if (has_note) {
		session_note = goal_note_input.AskQuestion();
	}
	int sleep = sleep_q.AskQuestion();
	int nutrition = nutrition_q.AskQuestion();
	int fatigue = fatigue_q.AskQuestion();
	struct RoughTime start_time = start_time_q.AskQuestion();
	struct RoughTime end_time = finish_time_q.AskQuestion();

	Workout* wo = new Workout(sesh_date, session_note, sleep, nutrition, fatigue, start_time, end_time);
	return wo;
}

Movement* AddMovement(LiftStore* lift_store) {
	InputQuestion movement_type_q("Is this a complex (Y/N)", ValidateYN, ConvertYN);
	if (!movement_type_q.AskQuestion()) {
		return AddBaseMovement();
	}
	else {
		return AddComplex(lift_store);
	}
}

Movement* AddBaseMovementName(std::string name) {
	InputQuestion has_desc_q("Would you like to add a description of the movement?\n", ValidateYN, ConvertYN);
	InputQuestion desc_q("Please give a description.\n", ValidateYes, NoConvert);
	if (has_desc_q.AskQuestion()) {
		std::string desc = desc_q.AskQuestion();
		return new Movement(name, desc);
	}
	else {
		return new Movement(name);
	}
}

Movement* AddBaseMovement() {
	InputQuestion name_q("What is the name of the movement?\n", ValidateYes, NoConvert);
	std::string name = name_q.AskQuestion();

	return AddBaseMovementName(name);
}

Complex* AddComplex(LiftStore* lift_store) {
	InputQuestion name_q("What is the name of the movement?\n", ValidateYes, NoConvert);
	InputQuestion has_desc_q("Would you like to add a description of the movement?\n", ValidateYN, ConvertYN);
	InputQuestion desc_q("Please give a description.\n", ValidateYes, NoConvert);
	InputQuestion another_movement_q("Is there another movement to add?\n", ValidateYN, ConvertYN);
	InputQuestion sub_movement_q("Give the name of a sub movement.\n", ValidateYes, NoConvert);
	InputQuestion reps_q("How many reps of the movement.\n", ValidateYes, StringConvert);

	std::string name = name_q.AskQuestion();
	std::string desc;
	bool has_desc = has_desc_q.AskQuestion();
	if (has_desc) {
		desc = desc_q.AskQuestion();
	}
	bool another_movement = false;
	std::string movement_name;
	std::vector<std::pair<Movement*, int>> sub_movements;
	do {
		movement_name = sub_movement_q.AskQuestion();
		Movement* sub_mv;
		if (!lift_store->Contains(movement_name)) {
			std::cout << "This lift hasn't been added to the store yet. ";
			sub_mv = AddBaseMovementName(movement_name);
		}
		else {
			sub_mv = lift_store->movement_names_[movement_name];
		}
		int reps = reps_q.AskQuestion();
		sub_movements.push_back(std::make_pair(sub_mv, reps));
		another_movement = another_movement_q.AskQuestion();
	} while (another_movement);

	return new Complex(name, desc, sub_movements);
}
