#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include "Menu.h"
#include "Question.h"
#include "InputQuestion.h"
#include "OptionsQuestion.h"
#include "Lift.h"
#include "Storage.h"

enum Action {kNoAction, kAddWorkout};
Action ParseCommandLineOptions(int argc, char const* argv[]);

int main(int argc, char const* argv[])
{
	MenuSession ms;
	ms.Initialise();

	int keep_going = true;
	while (keep_going) {
		keep_going = StartMenu(&ms);
	}

	ms.CleanUp();

	//Movement* clean = new Movement("Clean");
	//Movement* jerk = new Movement("Jerk");
	//Complex* c = new Complex("Clean & Jerk", std::make_pair(clean, 1), std::make_pair(jerk, 1));
	//lift_store.AddLift(clean);
	//lift_store.AddLift(jerk);
	//lift_store.AddLift(c);
	//lift_store.SaveLifts();
	//Movement* snatch = new Movement("Snatch");
	//Movement* hang_snatch= new Movement("Hang Snatch");
	////std::pair<Movement, int> snatch_pair(snatch, 1);
	////std::pair<Movement, int> hang_snatch_pair(hang_snatch, 2);
	//Complex* c = new Complex("Snatch, Hang Snatch", std::make_pair(snatch, 1), std::make_pair(hang_snatch, 1));

	//lift_store.AddLift(hang_snatch);
	//lift_store.AddLift(snatch);
	//lift_store.AddLift(c);

	//lift_store.SaveLifts();


	//std::ostringstream oss;
	//boost::property_tree::write_json(oss, c.toPtree());




	//StartMenu();
	//std::vector<std::string> options = { "This", "is a very good", "test of the options." };
	//OptionsQuestion q(options);
	//q.AskQuestion();
	//InputQuestion  q2("What is your favourite number 1-10: ", OneToTenValid, OneToTenConvert);
	//q2.AskQuestion();

	//Question<int> q("Pick a number between 1 and 10: ", OneToTenValid, OneToTenConvert);
	//q.AskQuestion();
	//Action action = ParseCommandLineOptions(argc, argv);

	//if (action == kAddWorkout) {
	//	Workout w = Workout::CreateWorkoutFromUser();
	//}

	return 0;
}

Action ParseCommandLineOptions(int argc, char const* argv[]) {
	namespace po = boost::program_options;
	Action outcome_action = kNoAction;

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("add_workout", "add a new workout")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << "\n";
	}
	else if (vm.count("add_workout")) {
		outcome_action = kAddWorkout;
	}
	else {
		std::cout << desc << "\n";
	}
	return outcome_action;
}
