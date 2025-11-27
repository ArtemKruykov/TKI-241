#pragma once
#include <string>
#include <memory>
#include <vector>

class Vehicle;

/**
 * @brief Класс представляющий владельца транспортного средства
 *
 * Класс Owner хранит персональные данные владельца и список
 * принадлежащих ему транспортных средств.
 */
class Owner {
private:
    std::string passportNumber;     ///< @brief Номер паспорта владельца
    std::string fullName;           ///< @brief Полное имя владельца
    std::string address;            ///< @brief Адрес регистрации
    std::vector<std::shared_ptr<Vehicle>> ownedVehicles; ///< @brief Список транспортных средств

public:
    /**
     * @brief Конструктор владельца
     * @param passport Номер паспорта
     * @param name Полное имя
     * @param addr Адрес регистрации
     */
    Owner(const std::string& passport, const std::string& name, const std::string& addr);

    /**
     * @brief Получить номер паспорта
     * @return Номер паспорта владельца
     */
    std::string getPassportNumber() const;

    /**
     * @brief Получить полное имя
     * @return Полное имя владельца
     */
    std::string getFullName() const;

    /**
     * @brief Получить адрес регистрации
     * @return Адрес регистрации владельца
     */
    std::string getAddress() const;

    /**
     * @brief Добавить транспортное средство в список владений
     * @param vehicle Умный указатель на транспортное средство
     */
    void addVehicle(std::shared_ptr<Vehicle> vehicle);

    /**
     * @brief Получить список транспортных средств владельца
     * @return Вектор умных указателей на транспортные средства
     */
    std::vector<std::shared_ptr<Vehicle>> getOwnedVehicles() const;

    /**
     * @brief Получить форматированную информацию о владельце
     * @return Строка с информацией о владельце
     */
    std::string getInfo() const;
};