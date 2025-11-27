#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <algorithm>
#include <string>
#include <iomanip>
#include "../decision2/Accident.h"
#include "../decision2/Owner.h"
#include "../decision2/PoliceDatabase.h"
#include "../decision2/Vehicle.h"

using namespace std;

/**
 * @brief Отображает главное меню системы ГАИ
 */
void showMainMenu();

/**
 * @brief Обрабатывает выбор пользователя из главного меню
 * @param choice Выбранный пункт меню
 * @param database Ссылка на базу данных ГАИ
 */
void handleUserChoice(int choice, PoliceDatabase& database);

/**
 * @brief Демонстрирует поиск автомобиля по государственному номеру
 * @param database Ссылка на базу данных ГАИ
 */
void demonstrateVehicleSearch(PoliceDatabase& database);

/**
 * @brief Демонстрирует поиск владельца по государственному номеру автомобиля
 * @param database Ссылка на базу данных ГАИ
 */
void demonstrateOwnerSearch(PoliceDatabase& database);

/**
 * @brief Демонстрирует поиск автомобиля по номеру двигателя
 * @param database Ссылка на базу данных ГАИ
 */
void demonstrateEngineNumberSearch(PoliceDatabase& database);

/**
 * @brief Демонстрирует список угнанных автомобилей
 * @param database Ссылка на базу данных ГАИ
 */
void demonstrateStolenVehicles(PoliceDatabase& database);

/**
 * @brief Демонстрирует автомобили, попавшие в ДТП за указанный период
 * @param database Ссылка на базу данных ГАИ
 */
void demonstrateAccidentVehicles(PoliceDatabase& database);

/**
 * @brief Демонстрирует наиболее часто угоняемые марки автомобилей
 * @param database Ссылка на базу данных ГАИ
 */
void demonstrateMostStolenBrands(PoliceDatabase& database);

/**
 * @brief Отображает статистику базы данных
 * @param database Ссылка на базу данных ГАИ
 */
void showDatabaseStatistics(PoliceDatabase& database);

/**
 * @brief Создает тестовые данные для демонстрации работы системы
 * @param database Ссылка на базу данных ГАИ
 */
void createTestData(PoliceDatabase& database);

/**
 * @brief Получает ввод от пользователя с заданным приглашением
 * @param prompt Текст приглашения для ввода
 * @return Введенная пользователем строка
 */
string getInput(const string& prompt);

/**
 * @brief Точка входа в программу системы ГАИ
 * @return Код завершения программы
 */
int main() {
    setlocale(LC_ALL, "Russian");

    PoliceDatabase database;

    createTestData(database);

    cout << " СИСТЕМА БАЗЫ ДАННЫХ ГАИ \n\n";

    while (true) {
        showMainMenu();

        int choice;
        cout << "Выберите операцию: ";
        cin >> choice;
        cin.ignore(); 

        if (choice == 0) {
            cout << "Выход из программы...\n";
            break;
        }

        handleUserChoice(choice, database);
    }

    return 0;
}

void addNewVehicle(PoliceDatabase& database) {
    cout << "\n ДОБАВЛЕНИЕ НОВОГО АВТОМОБИЛЯ \n";

    string licensePlate = getInput("Гос. номер: ");
    string brand = getInput("Марка: ");
    string model = getInput("Модель: ");
    string color = getInput("Цвет: ");

    int year;
    cout << "Год выпуска: ";
    cin >> year;
    cin.ignore();

    string engineNumber = getInput("Номер двигателя: ");

    auto vehicle = make_shared<Vehicle>(licensePlate, brand, model, color, year, engineNumber);
    database.addVehicle(vehicle);

    cout << "Автомобиль успешно добавлен!\n";
}

void addNewOwner(PoliceDatabase& database) {
    cout << "\n ДОБАВЛЕНИЕ НОВОГО ВЛАДЕЛЬЦА \n";

    string passport = getInput("Номер паспорта: ");
    string name = getInput("ФИО: ");
    string address = getInput("Адрес: ");

    auto owner = make_shared<Owner>(passport, name, address);
    database.addOwner(owner);

    cout << "Владелец успешно добавлен!\n";
}

void markVehicleAsStolen(PoliceDatabase& database) {
    cout << "\n ОТМЕТКА АВТОМОБИЛЯ КАК УГНАННОГО \n";

    string licensePlate = getInput("Введите гос. номер угнанного автомобиля: ");
    auto vehicle = database.findVehicleByLicensePlate(licensePlate);

    if (vehicle) {
        vehicle->setStolen(true);
        cout << "Автомобиль '" << licensePlate << "' отмечен как угнанный!\n";
    }
    else {
        cout << "Автомобиль с номером '" << licensePlate << "' не найден!\n";
    }
}

void showMainMenu() {
    cout << "\n ГЛАВНОЕ МЕНЮ СИСТЕМЫ ГАИ \n";
    cout << "1 - Информация об автомобиле по гос. номеру\n";
    cout << "2 - Информация о владельце по гос. номеру\n";
    cout << "3 - Информация об автомобиле по номеру двигателя\n";
    cout << "4 - Список угнанных автомобилей\n";
    cout << "5 - Автомобили в ДТП за период\n";
    cout << "6 - Наиболее угоняемые марки\n";
    cout << "7 - Статистика базы данных\n";
    cout << "8 - Добавить новый автомобиль\n";
    cout << "9 - Добавить нового владельца\n";
    cout << "10 - Отметить автомобиль как угнанный\n";
    cout << "0 - Выход\n";
    cout << "\n";
}

void handleUserChoice(int choice, PoliceDatabase& database) {
    switch (choice) {
    case 1:
        demonstrateVehicleSearch(database);
        break;
    case 2:
        demonstrateOwnerSearch(database);
        break;
    case 3:
        demonstrateEngineNumberSearch(database);
        break;
    case 4:
        demonstrateStolenVehicles(database);
        break;
    case 5:
        demonstrateAccidentVehicles(database);
        break;
    case 6:
        demonstrateMostStolenBrands(database);
        break;
    case 7:
        showDatabaseStatistics(database);
        break;
    case 8:
        addNewVehicle(database);
        break;
    case 9:
        addNewOwner(database);
        break;
    case 10:
        markVehicleAsStolen(database);
        break;
    default:
        cout << "Неверный выбор! Попробуйте снова.\n";
        break;
    }
}

string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

void demonstrateVehicleSearch(PoliceDatabase& database) {
    cout << "\n=== ПОИСК АВТОМОБИЛЯ ПО ГОСУДАРСТВЕННОМУ НОМЕРУ ===\n";

    string licensePlate = getInput("Введите гос. номер автомобиля: ");
    auto foundVehicle = database.findVehicleByLicensePlate(licensePlate);

    if (foundVehicle) {
        cout << "\n=== НАЙДЕНА ИНФОРМАЦИЯ ===\n";
        cout << foundVehicle->getInfo() << "\n";

        auto owner = foundVehicle->getCurrentOwner();
        if (owner) {
            cout << "Текущий владелец: " << owner->getInfo() << "\n";
        }

        auto accidents = foundVehicle->getAccidents();
        if (!accidents.empty()) {
            cout << "Участвовал в ДТП: " << accidents.size() << " раз(а)\n";
            for (const auto& accident : accidents) {
                cout << "  - " << accident->getInfo() << "\n";
            }
        }
    }
    else {
        cout << "Автомобиль с номером '" << licensePlate << "' не найден!\n";
    }
}

void demonstrateOwnerSearch(PoliceDatabase& database) {
    cout << "\n ПОИСК ВЛАДЕЛЬЦА ПО ГОСУДАРСТВЕННОМУ НОМЕРУ \n";

    string licensePlate = getInput("Введите гос. номер автомобиля: ");
    auto foundOwner = database.findOwnerByLicensePlate(licensePlate);

    if (foundOwner) {
        cout << "\n НАЙДЕНА ИНФОРМАЦИЯ \n";
        cout << "Владелец: " << foundOwner->getInfo() << "\n";

        auto ownedVehicles = foundOwner->getOwnedVehicles();
        if (!ownedVehicles.empty()) {
            cout << "Принадлежащие автомобили:\n";
            for (size_t i = 0; i < ownedVehicles.size(); ++i) {
                cout << i + 1 << ". " << ownedVehicles[i]->getInfo() << "\n";
            }
        }
        else {
            cout << "У владельца нет зарегистрированных автомобилей\n";
        }
    }
    else {
        cout << "Владелец автомобиля с номером '" << licensePlate << "' не найден!\n";
    }
}

void demonstrateEngineNumberSearch(PoliceDatabase& database) {
    cout << "\n ПОИСК АВТОМОБИЛЯ ПО НОМЕРУ ДВИГАТЕЛЯ \n";

    string engineNumber = getInput("Введите номер двигателя: ");
    auto foundVehicle = database.findVehicleByEngineNumber(engineNumber);

    if (foundVehicle) {
        cout << "\n НАЙДЕНА ИНФОРМАЦИЯ \n";
        cout << "Основная информация: " << foundVehicle->getInfo() << "\n\n";

        cout << "ИСТОРИЯ ВЛАДЕЛЬЦЕВ:\n";
        auto previousOwners = foundVehicle->getPreviousOwners();
        if (previousOwners.empty()) {
            cout << "  Нет предыдущих владельцев\n";
        }
        else {
            for (const auto& owner : previousOwners) {
                cout << "  - " << owner->getInfo() << "\n";
            }
        }

        cout << "\nИСТОРИЯ ДТП:\n";
        auto accidents = foundVehicle->getAccidents();
        if (accidents.empty()) {
            cout << "  Не участвовал в ДТП\n";
        }
        else {
            for (const auto& accident : accidents) {
                cout << "  - " << accident->getInfo() << "\n";
            }
        }

        cout << "\nТЕКУЩИЙ ВЛАДЕЛЕЦ: ";
        auto currentOwner = foundVehicle->getCurrentOwner();
        if (currentOwner) {
            cout << currentOwner->getInfo() << "\n";
        }
        else {
            cout << "Не указан\n";
        }

        cout << "СТАТУС УГОНА: " << (foundVehicle->getIsStolen() ? "УГНАН" : "Не угнан") << "\n";
    }
    else {
        cout << "Автомобиль с номером двигателя '" << engineNumber << "' не найден!\n";
    }
}

void demonstrateStolenVehicles(PoliceDatabase& database) {
    cout << "\n СПИСОК УГНАННЫХ АВТОМОБИЛЕЙ \n";

    auto stolenVehicles = database.getStolenVehicles();
    if (stolenVehicles.empty()) {
        cout << "Угнанных автомобилей нет.\n";
    }
    else {
        cout << "Найдено угнанных автомобилей: " << stolenVehicles.size() << "\n\n";
        for (size_t i = 0; i < stolenVehicles.size(); ++i) {
            cout << i + 1 << ". " << stolenVehicles[i]->getInfo() << "\n";
            auto owner = stolenVehicles[i]->getCurrentOwner();
            if (owner) {
                cout << "   Владелец: " << owner->getInfo() << "\n";
            }
            cout << "---\n";
        }
    }
}

void demonstrateAccidentVehicles(PoliceDatabase& database) {
    cout << "\n АВТОМОБИЛИ В ДТП ЗА ПЕРИОД \n";

    int startDay, startMonth, startYear, endDay, endMonth, endYear;
    cout << "Введите начальную дату:\n";
    cout << "День: "; cin >> startDay;
    cout << "Месяц: "; cin >> startMonth;
    cout << "Год: "; cin >> startYear;

    cout << "Введите конечную дату:\n";
    cout << "День: "; cin >> endDay;
    cout << "Месяц: "; cin >> endMonth;
    cout << "Год: "; cin >> endYear;
    cin.ignore();

    tm startDate = {};
    startDate.tm_mday = startDay;
    startDate.tm_mon = startMonth - 1;
    startDate.tm_year = startYear - 1900;

    tm endDate = {};
    endDate.tm_mday = endDay;
    endDate.tm_mon = endMonth - 1;
    endDate.tm_year = endYear - 1900;

    auto accidentVehicles = database.getAccidentVehiclesInPeriod(startDate, endDate);

    if (accidentVehicles.empty()) {
        cout << "В указанный период ДТП не зарегистрировано.\n";
    }
    else {
        cout << "Автомобили, попавшие в ДТП: " << accidentVehicles.size() << "\n\n";
        for (size_t i = 0; i < accidentVehicles.size(); ++i) {
            cout << i + 1 << ". " << accidentVehicles[i]->getInfo() << "\n";
        }
    }
}

void demonstrateMostStolenBrands(PoliceDatabase& database) {
    cout << "\n НАИБОЛЕЕ УГОНЯЕМЫЕ МАРКИ АВТОМОБИЛЕЙ \n";

    auto mostStolen = database.getMostStolenBrands();
    if (mostStolen.empty()) {
        cout << "Нет данных об угонах.\n";
    }
    else {
        cout << "Рейтинг марок по количеству угонов:\n\n";
        for (size_t i = 0; i < mostStolen.size(); ++i) {
            cout << i + 1 << ". " << mostStolen[i].first << " - " << mostStolen[i].second;
            cout << (mostStolen[i].second == 1 ? " угон" : " угона") << "\n";
        }
    }
}

void showDatabaseStatistics(PoliceDatabase& database) {
    cout << "\n СТАТИСТИКА БАЗЫ ДАННЫХ ГАИ \n";
    cout << "Всего владельцев: " << database.getAllOwners().size() << "\n";
    cout << "Всего автомобилей: " << database.getAllVehicles().size() << "\n";
    cout << "Всего ДТП: " << database.getAllAccidents().size() << "\n";
    cout << "Угнанных автомобилей: " << database.getStolenVehicles().size() << "\n";

    auto mostStolen = database.getMostStolenBrands();
    if (!mostStolen.empty()) {
        cout << "Самая угоняемая марка: " << mostStolen[0].first << " (" << mostStolen[0].second << " угонов)\n";
    }
}

void createTestData(PoliceDatabase& database) {
    auto owner1 = make_shared<Owner>("4500112233", "Иванов Иван Иванович", "г. Москва, ул. Ленина, д. 1");
    auto owner2 = make_shared<Owner>("4500445566", "Петров Петр Петрович", "г. Москва, ул. Пушкина, д. 10");
    auto owner3 = make_shared<Owner>("4500778899", "Сидорова Мария Сергеевна", "г. Москва, пр. Мира, д. 25");
    auto previousOwner = make_shared<Owner>("4500998877", "Кузнецов Алексей", "г. Москва, ул. Садовая, д. 5");

    database.addOwner(owner1);
    database.addOwner(owner2);
    database.addOwner(owner3);
    database.addOwner(previousOwner);

    auto vehicle1 = make_shared<Vehicle>("A123BC777", "Toyota", "Camry", "Черный", 2018, "T123456789");
    auto vehicle2 = make_shared<Vehicle>("B456DE777", "BMW", "X5", "Белый", 2020, "B987654321");
    auto vehicle3 = make_shared<Vehicle>("C789FG777", "Lada", "Granta", "Красный", 2015, "L555555555");
    auto vehicle4 = make_shared<Vehicle>("D111EE777", "BMW", "X6", "Синий", 2021, "B111111111");
    auto vehicle5 = make_shared<Vehicle>("E222FF777", "Toyota", "RAV4", "Серебристый", 2019, "T222222222");

    vehicle1->setCurrentOwner(owner1);
    vehicle1->addPreviousOwner(previousOwner);

    vehicle2->setCurrentOwner(owner2);
    vehicle2->setStolen(true);

    vehicle3->setCurrentOwner(owner3);

    vehicle4->setCurrentOwner(owner1);
    vehicle4->setStolen(true);

    vehicle5->setCurrentOwner(owner2);
    vehicle5->setStolen(true);

    database.addVehicle(vehicle1);
    database.addVehicle(vehicle2);
    database.addVehicle(vehicle3);
    database.addVehicle(vehicle4);
    database.addVehicle(vehicle5);

    tm accidentDate1 = {};
    accidentDate1.tm_year = 124;
    accidentDate1.tm_mon = 5;
    accidentDate1.tm_mday = 15;

    auto accident1 = make_shared<Accident>("DT001", accidentDate1,
        "Столкновение на перекрестке", "ул. Ленина - ул. Пушкина");
    accident1->addInvolvedVehicle(vehicle1);

    tm accidentDate2 = {};
    accidentDate2.tm_year = 124;
    accidentDate2.tm_mon = 4;
    accidentDate2.tm_mday = 10;

    auto accident2 = make_shared<Accident>("DT002", accidentDate2,
        "Наезд на пешехода", "пр. Мира, д. 25");
    accident2->addInvolvedVehicle(vehicle3);

    database.addAccident(accident1);
    database.addAccident(accident2);

    vehicle1->addAccident(accident1);
    vehicle3->addAccident(accident2);
}