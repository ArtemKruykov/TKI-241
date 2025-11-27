#include "Owner.h"
#include "Vehicle.h"

Owner::Owner(const std::string& passport, const std::string& name, const std::string& addr)
    : passportNumber(passport), fullName(name), address(addr) {}

std::string Owner::getPassportNumber() const { return passportNumber; }
std::string Owner::getFullName() const { return fullName; }
std::string Owner::getAddress() const { return address; }

void Owner::addVehicle(std::shared_ptr<Vehicle> vehicle) {
    ownedVehicles.push_back(vehicle);
}

std::vector<std::shared_ptr<Vehicle>> Owner::getOwnedVehicles() const {
    return ownedVehicles;
}

std::string Owner::getInfo() const {
    return fullName + ", паспорт " + passportNumber + ", адрес " + address;
}