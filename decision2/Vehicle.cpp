#include "Vehicle.h"
#include "Owner.h"
#include "Accident.h"

Vehicle::Vehicle(const std::string& plate, const std::string& brand,
    const std::string& model, const std::string& color,
    int year, const std::string& engineNum)
    : licensePlate(plate), brand(brand), model(model), color(color),
    year(year), engineNumber(engineNum), isStolen(false) {}

std::string Vehicle::getLicensePlate() const { return licensePlate; }
std::string Vehicle::getBrand() const { return brand; }
std::string Vehicle::getModel() const { return model; }
std::string Vehicle::getColor() const { return color; }
int Vehicle::getYear() const { return year; }
std::string Vehicle::getEngineNumber() const { return engineNumber; }
bool Vehicle::getIsStolen() const { return isStolen; }
std::shared_ptr<Owner> Vehicle::getCurrentOwner() const { return currentOwner; }

void Vehicle::setStolen(bool stolen) { isStolen = stolen; }
void Vehicle::setCurrentOwner(std::shared_ptr<Owner> owner) { currentOwner = owner; }

void Vehicle::addPreviousOwner(std::shared_ptr<Owner> owner) {
    previousOwners.push_back(owner);
}

void Vehicle::addAccident(std::shared_ptr<Accident> accident) {
    accidents.push_back(accident);
}

std::vector<std::shared_ptr<Owner>> Vehicle::getPreviousOwners() const {
    return previousOwners;
}

std::vector<std::shared_ptr<Accident>> Vehicle::getAccidents() const {
    return accidents;
}

std::string Vehicle::getInfo() const {
    return brand + " " + model + " (" + color + "), гос.номер: " + licensePlate +
        ", год: " + std::to_string(year) + ", двигатель: " + engineNumber +
        ", статус: " + (isStolen ? "УГНАН" : "не угнан");
}