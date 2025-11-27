#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <algorithm>
#include "Vehicle.h"
#include "Owner.h"
#include "Accident.h"

/**
 * @brief Основной класс базы данных ГАИ
 * Класс PoliceDatabase представляет централизованную базу данных
 * для хранения и управления информацией о транспортных средствах,
 * владельцах и дорожно-транспортных происшествиях.
 * Реализует все основные функции требуемые системой ГАИ.
 */
class PoliceDatabase {
private:
    std::vector<std::shared_ptr<Vehicle>> vehicles;    ///< @brief Реестр транспортных средств
    std::vector<std::shared_ptr<Owner>> owners;        ///< @brief Реестр владельцев
    std::vector<std::shared_ptr<Accident>> accidents;  ///< @brief Реестр ДТП

public:
    /**
     * @brief Добавить транспортное средство в базу данных
     * @param vehicle Умный указатель на транспортное средство
     */
    void addVehicle(std::shared_ptr<Vehicle> vehicle);

    /**
     * @brief Добавить запись о ДТП в базу данных
     * @param accident Умный указатель на запись о ДТП
     */
    void addAccident(std::shared_ptr<Accident> accident);

    /**
     * @brief Найти транспортное средство по государственному номеру
     * @param licensePlate Государственный регистрационный номер
     * @return Умный указатель на транспортное средство или nullptr если не найдено
     */
    std::shared_ptr<Vehicle> findVehicleByLicensePlate(const std::string& licensePlate) const;

    /**
     * @brief Найти владельца по государственному номеру транспортного средства
     * @param licensePlate Государственный регистрационный номер
     * @return Умный указатель на владельца или nullptr если не найдено
     */
    std::shared_ptr<Owner> findOwnerByLicensePlate(const std::string& licensePlate) const;

    /**
     * @brief Найти транспортное средство по номеру двигателя
     * @param engineNumber Номер двигателя
     * @return Умный указатель на транспортное средство или nullptr если не найдено
     */
    std::shared_ptr<Vehicle> findVehicleByEngineNumber(const std::string& engineNumber) const;

    /**
     * @brief Получить список угнанных транспортных средств
     * @return Вектор умных указателей на угнанные транспортные средства
     */
    std::vector<std::shared_ptr<Vehicle>> getStolenVehicles() const;

    /**
     * @brief Получить транспортные средства попавшие в ДТП за указанный период
     * @param start Начальная дата периода
     * @param end Конечная дата периода
     * @return Вектор умных указателей на транспортные средства
     */
    std::vector<std::shared_ptr<Vehicle>> getAccidentVehiclesInPeriod(const std::tm& start, const std::tm& end) const;

    /**
     * @brief Получить список наиболее часто угоняемых марок
     * @return Вектор пар (марка, количество угонов)
     */
    std::vector<std::pair<std::string, int>> getMostStolenBrands() const;

    /**
     * @brief Получить все транспортные средства из базы данных
     * @return Вектор умных указателей на все транспортные средства
     */
    std::vector<std::shared_ptr<Vehicle>> getAllVehicles() const;

    /**
     * @brief Получить всех владельцев из базы данных
     * @return Вектор умных указателей на всех владельцев
     */
    std::vector<std::shared_ptr<Owner>> getAllOwners() const;

    /**
     * @brief Получить все записи о ДТП из базы данных
     * @return Вектор умных указателей на все записи о ДТП
     */
    std::vector<std::shared_ptr<Accident>> getAllAccidents() const;
};

/**
 * @brief Добавить новое транспортное средство в базу данных через пользовательский ввод
 * @param database Ссылка на базу данных ГАИ
 */
void addNewVehicle(PoliceDatabase& database);

/**
 * @brief Отметить транспортное средство как угнанное по государственному номеру
 * @param database Ссылка на базу данных ГАИ
 */
void markVehicleAsStolen(PoliceDatabase& database);