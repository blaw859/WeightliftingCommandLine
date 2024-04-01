#include "Lift.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

Movement::Movement() : 
	name_(""),
	description_("")
{
	boost::uuids::random_generator gen;
	id_ = gen();
}

Movement::Movement(std::string name) : 
	name_(name), 
	description_("")
{
	boost::uuids::random_generator gen;
	id_ = gen();
}

Movement::Movement(std::string name, std::string description) : 
	name_(name), 
	description_(description)
{
	boost::uuids::random_generator gen;
	id_ = gen();
}

Movement::Movement(boost::uuids::uuid id, std::string name, std::string description) : 
	name_(name), 
	description_(description),
	id_(id)
{}

Movement::Movement(std::string uuid_string, std::string name, std::string description) :
	name_(name),
	description_(description),
	id_(boost::uuids::string_generator()(uuid_string))
{}

nlohmann::json Movement::toJson() const
{
	nlohmann::json j;
	j["uuid"] = boost::uuids::to_string(id_);
	j["name"] = name_;
	j["description"] = description_;
	return j;
}


//boost::property_tree::ptree Movement::toPtree() const {
//	boost::property_tree::ptree tree;
//	tree.put("uuid", boost::uuids::to_string(id_));
//	tree.put("name", name_);
//	tree.put("description", description_);
//	return tree;
//}

//boost::property_tree::ptree Complex::toPtree() const
//{
//	boost::property_tree::ptree tree;
//	tree.put("uuid", boost::uuids::to_string(id_));
//	tree.put("name", name_);
//	tree.put("description", description_);
//
//	boost::property_tree::ptree sub_movements;
//	for (std::pair<Movement, int> movement : movements_) {
//		boost::property_tree::ptree movtree;
//		movtree.put("reps", movement.second);
//		movtree.add_child("movement", movement.first.toPtree());
//		sub_movements.push_back(std::make_pair("", movtree));
//	}
//	tree.add_child("movements", sub_movements);
//
//	return tree;
//}

nlohmann::json Complex::toJson() const
{
	nlohmann::json j;
	j["uuid"] = boost::uuids::to_string(id_);
	j["name"] = name_;
	j["description"] = description_;

	nlohmann::json sub_movements;
	for (const auto& movement : movements_) {
		nlohmann::json movtree;
		movtree["reps"] = movement.second;
		movtree["movement"] = movement.first->toJson();
		sub_movements.push_back(movtree);
	}
	j["movements"] = sub_movements;

	return j;
}
