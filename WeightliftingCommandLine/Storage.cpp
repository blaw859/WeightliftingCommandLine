#include <fstream>
#include <exception>
#include "Storage.h"
#include "Lift.h"

struct PreComplex {
    std::string id;
    std::string name;
    std::string description;
    std::vector<std::pair<boost::uuids::uuid, int>> sub_movements;
};

void LiftStore::SaveLifts() {
    nlohmann::json movements_json;

    // Convert each movement to JSON and add it to the array
    for (const auto& movement_pair : movement_names_) {
        const Movement* m = movement_pair.second;
        if (auto complex = dynamic_cast<const Complex*>(m)) {
            movements_json.push_back(complex->toJson());
        }
        else {
            movements_json.push_back(m->toJson());
        }
    }

    // Write JSON to file
    std::ofstream out_file("canned_movements.json");
    if (out_file.is_open()) {
        out_file << std::setw(4) << movements_json << std::endl; // Pretty print with indentation
        out_file.close();
        std::cout << "Movements saved to movements.json" << std::endl;
    }
    else {
        std::cerr << "Error opening file for writing" << std::endl;
    }
}

void LiftStore::LoadLifts()
{
    std::ifstream file("canned_movements.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    nlohmann::json jsonData;

    try {
        file >> jsonData;
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }

    std::map<boost::uuids::uuid, Movement*> movements_map;
    std::vector<PreComplex> pre_complexes;
    for (const auto& element : jsonData) {
        if (element.contains("movements")) {
            std::vector<std::pair<boost::uuids::uuid, int>> movement_reps;
            for (const auto& sub_movement : element.at("movements")) {
                nlohmann::json movement_json = sub_movement.at("movement");
                int reps = sub_movement.at("reps").get<int>();
                std::string uuid_string = movement_json.at("uuid").get<std::string>();
                std::pair<boost::uuids::uuid, int> pair = std::make_pair(boost::uuids::string_generator()(uuid_string), reps);
                movement_reps.push_back(pair);
            }
            PreComplex pc = {
                element.at("uuid").get<std::string>(),
                element.at("name").get<std::string>(),
                element.at("description").get<std::string>(),
                movement_reps
            };
            pre_complexes.push_back(pc);
        } else {
            Movement* mvmt = new Movement(element.at("uuid").get<std::string>(), element.at("name").get<std::string>(), element.at("description").get<std::string>());
            //movements_map[mvmt->id_] = mvmt;
            AddLift(mvmt);
        }
    }

    for (const auto& pre_complex : pre_complexes) {
        std::vector <std::pair<Movement*, int>> sub_movements_real;
        for (const auto& sub_movement : pre_complex.sub_movements) {
            Movement* mvmt = movement_ids_.at(sub_movement.first);
            if (mvmt) {
                sub_movements_real.push_back(std::make_pair(mvmt, sub_movement.second));
            }
        }
        Complex* cmp = new Complex(pre_complex.id, pre_complex.name, pre_complex.description, sub_movements_real);
        AddLift(cmp);
        //movements_map[cmp->id_] = cmp;
    }
}

void LiftStore::AddLift(Movement* movement) {
    if (movement_names_.contains(movement->name_)) {
        std::ostringstream oss;
        oss << "Trying to add a movement with a name that already exists. Received: " << movement->name_;
        throw std::invalid_argument(oss.str());
    }
    if (movement_ids_.contains(movement->id_)) {
        std::ostringstream oss;
        oss << "Trying to add a movement with an id that already eixsts . Received: " << boost::uuids::to_string(movement->id_);
        throw std::invalid_argument(oss.str());
    }
	movement_names_[movement->name_] = movement;
    movement_ids_[movement->id_] = movement;
}

bool LiftStore::Contains(std::string movement_name)
{
    auto it = movement_names_.find(movement_name);
    if (it != movement_names_.end()) {
        return true;
    }
    else {
        return false;
    }
}

bool LiftStore::Contains(boost::uuids::uuid uuid)
{
    auto it = movement_ids_.find(uuid);
    if (it != movement_ids_.end()) {
        return true;
    }
    else {
        return false;
    }
}
