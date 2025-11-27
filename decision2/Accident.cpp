#include "Accident.h"
#include "Vehicle.h"
#include <sstream>
#include <iomanip>

Accident::Accident(const std::string& accidentId, const std::tm& accidentDate,
    const std::string& desc, const std::string& loc)
    : id(accidentId), date(accidentDate), description(desc), location(loc) {}

std::string Accident::getId() const { return id; }
std::tm Accident::getDate() const { return date; }
std::string Accident::getDescription() const { return description; }
std::string Accident::getLocation() const { return location; }

void Accident::addInvolvedVehicle(std::shared_ptr<Vehicle> vehicle) {
    involvedVehicles.push_back(vehicle);
}

std::vector<std::shared_ptr<Vehicle>> Accident::getInvolvedVehicles() const {
    return involvedVehicles;
}

std::string Accident::getInfo() const {
    std::stringstream ss;
    ss << "ДТП №" << id << " от " << std::put_time(&date, "%d.%m.%Y")
        << " (" << location << "): " << description;
    return ss.str();
}