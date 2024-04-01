#pragma once
#include <map>
#include <string>
#include <filesystem>
#include <boost/uuid/uuid_generators.hpp>
#include "Lift.h"

//enum AddError {
//	SUCCESS = 0,
//	DUPLICATE_NAME,
//	DUPLICATE_ID
//};

class LiftStore {
public:
	std::map<std::string, Movement*>  movement_names_;
	std::map<boost::uuids::uuid, Movement*> movement_ids_;
	std::filesystem::path store_directory_;

	void SaveLifts();
	void LoadLifts();
	void AddLift(Movement* movement);
	bool Contains(std::string movement_name);
	bool Contains(boost::uuids::uuid uuid);
};