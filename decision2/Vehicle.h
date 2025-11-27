#pragma once
#include <string>
#include <vector>
#include <memory>

class Owner;
class Accident;

/**
 * @brief Базовый класс представляющий транспортное средство
 *
 * Класс Vehicle хранит информацию о транспортном средстве, включая
 * регистрационные данные, технические характеристики и историю.
 * Поддерживает связи с владельцами и записями о ДТП.
 */
class Vehicle {
protected:
    std::string licensePlate;       ///< @brief Государственный регистрационный номер
    std::string brand;              ///< @brief Марка транспортного средства
    std::string model;              ///< @brief Модель транспортного средства
    std::string color;              ///< @brief Цвет транспортного средства
    int year;                       ///< @brief Год выпуска
    std::string engineNumber;       ///< @brief Номер двигателя
    bool isStolen;                  ///< @brief Флаг угона (true - угнано)
    std::shared_ptr<Owner> currentOwner;           ///< @brief Текущий владелец
    std::vector<std::shared_ptr<Owner>> previousOwners; ///< @brief Предыдущие владельцы
    std::vector<std::shared_ptr<Accident>> accidents;   ///< @brief Записи о ДТП

public:
    /**
     * @brief Конструктор транспортного средства
     * @param plate Государственный регистрационный номер
     * @param brand Марка транспортного средства
     * @param model Модель транспортного средства
     * @param color Цвет транспортного средства
     * @param year Год выпуска
     * @param engineNum Номер двигателя
     */
    Vehicle(const std::string& plate, const std::string& brand,
        const std::string& model, const std::string& color,
        int year, const std::string& engineNum);

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Vehicle() = default;

    /**
     * @brief Получить государственный номер
     * @return Государственный регистрационный номер
     */
    std::string getLicensePlate() const;

    /**
     * @brief Получить марку транспортного средства
     * @return Марка транспортного средства
     */
    std::string getBrand() const;

    /**
     * @brief Получить модель транспортного средства
     * @return Модель транспортного средства
     */
    std::string getModel() const;

    /**
     * @brief Получить цвет транспортного средства
     * @return Цвет транспортного средства
     */
    std::string getColor() const;

    /**
     * @brief Получить год выпуска
     * @return Год выпуска
     */
    int getYear() const;

    /**
     * @brief Получить номер двигателя
     * @return Номер двигателя
     */
    std::string getEngineNumber() const;

    /**
     * @brief Проверить статус угона
     * @return true если транспортное средство угнано, иначе false
     */
    bool getIsStolen() const;

    /**
     * @brief Получить текущего владельца
     * @return Умный указатель на текущего владельца
     */
    std::shared_ptr<Owner> getCurrentOwner() const;

    /**
     * @brief Установить статус угона
     * @param stolen true - угнано, false - не угнано
     */
    void setStolen(bool stolen);

    /**
     * @brief Установить текущего владельца
     * @param owner Умный указатель на владельца
     */
    void setCurrentOwner(std::shared_ptr<Owner> owner);

    /**
     * @brief Добавить предыдущего владельца
     * @param owner Умный указатель на предыдущего владельца
     */
    void addPreviousOwner(std::shared_ptr<Owner> owner);

    /**
     * @brief Добавить запись о ДТП
     * @param accident Умный указатель на запись о ДТП
     */
    void addAccident(std::shared_ptr<Accident> accident);

    /**
     * @brief Получить список предыдущих владельцев
     * @return Вектор умных указателей на предыдущих владельцев
     */
    std::vector<std::shared_ptr<Owner>> getPreviousOwners() const;

    /**
     * @brief Получить список ДТП с участием транспортного средства
     * @return Вектор умных указателей на записи о ДТП
     */
    std::vector<std::shared_ptr<Accident>> getAccidents() const;

    /**
     * @brief Получить форматированную информацию о транспортном средстве
     * @return Строка с информацией о транспортном средстве
     */
    virtual std::string getInfo() const;
};