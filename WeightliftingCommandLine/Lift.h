#pragma once
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "json.hpp"

class Movement {
public:
	boost::uuids::uuid id_;
	std::string name_;	
	std::string description_;

	Movement();
	Movement(std::string name);
	Movement(std::string name, std::string description);
	Movement(boost::uuids::uuid id, std::string name, std::string description);
	Movement(std::string uuid_string, std::string name, std::string description);

	virtual nlohmann::json toJson() const;
};

class Complex : public Movement {
public:
	// Each pair is a movement and the reps of that movement
	std::vector<std::pair<Movement*, int>> movements_;

	template<typename... Args>
	Complex(boost::uuids::uuid id, std::string name, std::string description, Args... args) : 
		Movement(id, name, description),
		movements_{args...}
	{}

	template<typename... Args>
	Complex(std::string uuid_string, std::string name, std::string description, Args... args) : 
		Movement(uuid_string , name, description),
		movements_{args...}
	{}

	Complex(std::string uuid_string, std::string name, std::string description, std::vector<std::pair<Movement*, int>> sub_movements) : 
		Movement(uuid_string , name, description),
		movements_(sub_movements)
	{}

	template<typename... Args>
	Complex(std::string name, std::string description, Args... args) : 
		Movement(name, description),
		movements_{args...}
	{}

	template<typename... Args>
	Complex(std::string name, Args... args) : 
		Movement(name),
		movements_{args...}
	{}

	void AddSubMovement(boost::uuids::uuid id, int reps) {
		pre_movements_.push_back(std::make_pair(id, reps));
	}

	nlohmann::json toJson() const;
private:
	std::vector<std::pair<boost::uuids::uuid, int>> pre_movements_;
};

