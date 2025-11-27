#include "PoliceDatabase.h"
#include <algorithm>
#include <map>
#include <iomanip>

void PoliceDatabase::addVehicle(std::shared_ptr<Vehicle> vehicle) {
    vehicles.push_back(vehicle);

    // Автоматически добавляем владельца автомобиля в базу данных
    auto owner = vehicle->getCurrentOwner();
    if (owner) {
        // Проверяем, нет ли уже такого владельца в базе
        auto it = std::find_if(owners.begin(), owners.end(),
            [&](const std::shared_ptr<Owner>& existingOwner) {
                return existingOwner->getPassportNumber() == owner->getPassportNumber();
            });

        if (it == owners.end()) {
            owners.push_back(owner);
        }
    }
}

void PoliceDatabase::addAccident(std::shared_ptr<Accident> accident) {
    accidents.push_back(accident);
}

std::shared_ptr<Vehicle> PoliceDatabase::findVehicleByLicensePlate(const std::string& licensePlate) const {
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
        [&](const std::shared_ptr<Vehicle>& vehicle) {
            return vehicle->getLicensePlate() == licensePlate;
        });
    return it != vehicles.end() ? *it : nullptr;
}

std::shared_ptr<Owner> PoliceDatabase::findOwnerByLicensePlate(const std::string& licensePlate) const {
    auto vehicle = findVehicleByLicensePlate(licensePlate);
    return vehicle ? vehicle->getCurrentOwner() : nullptr;
}

std::shared_ptr<Vehicle> PoliceDatabase::findVehicleByEngineNumber(const std::string& engineNumber) const {
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
        [&](const std::shared_ptr<Vehicle>& vehicle) {
            return vehicle->getEngineNumber() == engineNumber;
        });
    return it != vehicles.end() ? *it : nullptr;
}

std::vector<std::shared_ptr<Vehicle>> PoliceDatabase::getStolenVehicles() const {
    std::vector<std::shared_ptr<Vehicle>> stolen;
    std::copy_if(vehicles.begin(), vehicles.end(), std::back_inserter(stolen),
        [](const std::shared_ptr<Vehicle>& vehicle) {
            return vehicle->getIsStolen();
        });
    return stolen;
}

std::vector<std::shared_ptr<Vehicle>> PoliceDatabase::getAccidentVehiclesInPeriod(const std::tm& start, const std::tm& end) const {
    std::vector<std::shared_ptr<Vehicle>> result;

    for (const auto& accident : accidents) {
        std::tm accidentDate = accident->getDate();

        // Проверка даты ДТП
        if (std::difftime(std::mktime(const_cast<std::tm*>(&accidentDate)), std::mktime(const_cast<std::tm*>(&start))) >= 0 &&
            std::difftime(std::mktime(const_cast<std::tm*>(&accidentDate)), std::mktime(const_cast<std::tm*>(&end))) <= 0) {

            auto involvedVehicles = accident->getInvolvedVehicles();
            for (const auto& vehicle : involvedVehicles) {
                // Добавляем только уникальные транспортные средства
                if (std::find(result.begin(), result.end(), vehicle) == result.end()) {
                    result.push_back(vehicle);
                }
            }
        }
    }

    return result;
}

std::vector<std::pair<std::string, int>> PoliceDatabase::getMostStolenBrands() const {
    std::map<std::string, int> brandCount;

    // Подсчет угонов по маркам
    for (const auto& vehicle : vehicles) {
        if (vehicle->getIsStolen()) {
            brandCount[vehicle->getBrand()]++;
        }
    }

    std::vector<std::pair<std::string, int>> result(brandCount.begin(), brandCount.end());
    std::sort(result.begin(), result.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });

    return result;
}

std::vector<std::shared_ptr<Vehicle>> PoliceDatabase::getAllVehicles() const {
    return vehicles;
}

std::vector<std::shared_ptr<Owner>> PoliceDatabase::getAllOwners() const {
    return owners;
}

std::vector<std::shared_ptr<Accident>> PoliceDatabase::getAllAccidents() const {
    return accidents;
}