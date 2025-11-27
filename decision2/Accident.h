#pragma once
#include <string>
#include <memory>
#include <vector>
#include <ctime>

class Vehicle;

/**
 * @brief Класс представляющий запись о дорожно-транспортном происшествии
 *
 * Класс Accident хранит информацию о ДТП, включая дату, место,
 * описание и список участвовавших транспортных средств.
 */
class Accident {
private:
    std::string id;                 ///< @brief Уникальный идентификатор ДТП
    std::tm date;                   ///< @brief Дата происшествия
    std::string description;        ///< @brief Описание ДТП
    std::string location;           ///< @brief Место происшествия
    std::vector<std::shared_ptr<Vehicle>> involvedVehicles; ///< @brief Участвовавшие транспортные средства

public:
    /**
     * @brief Конструктор записи о ДТП
     * @param accidentId Уникальный идентификатор ДТП
     * @param accidentDate Дата происшествия
     * @param desc Описание ДТП
     * @param loc Место происшествия
     */
    Accident(const std::string& accidentId, const std::tm& accidentDate,
        const std::string& desc, const std::string& loc);

    /**
     * @brief Получить идентификатор ДТП
     * @return Уникальный идентификатор ДТП
     */
    std::string getId() const;

    /**
     * @brief Получить дату ДТП
     * @return Дата происшествия
     */
    std::tm getDate() const;

    /**
     * @brief Получить описание ДТП
     * @return Описание происшествия
     */
    std::string getDescription() const;

    /**
     * @brief Получить место ДТП
     * @return Место происшествия
     */
    std::string getLocation() const;

    /**
     * @brief Добавить транспортное средство к списку участников ДТП
     * @param vehicle Умный указатель на транспортное средство
     */
    void addInvolvedVehicle(std::shared_ptr<Vehicle> vehicle);

    /**
     * @brief Получить список участвовавших транспортных средств
     * @return Вектор умных указателей на транспортные средства
     */
    std::vector<std::shared_ptr<Vehicle>> getInvolvedVehicles() const;

    /**
     * @brief Получить форматированную информацию о ДТП
     * @return Строка с информацией о ДТП
     */
    std::string getInfo() const;
};