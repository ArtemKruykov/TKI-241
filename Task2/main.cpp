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
 * @brief Перечисление пунктов главного меню
 */
enum class MenuChoice {
    EXIT = 0,
    VEHICLE_INFO_BY_PLATE = 1,
    OWNER_INFO_BY_PLATE = 2,
    VEHICLE_INFO_BY_ENGINE = 3,
    STOLEN_VEHICLES_LIST = 4,
    ACCIDENT_VEHICLES_IN_PERIOD = 5,
    MOST_STOLEN_BRANDS = 6,
    DATABASE_STATISTICS = 7,
    ADD_NEW_VEHICLE = 8,
    MARK_VEHICLE_STOLEN = 9
};

/**
 * @brief Отображает главное меню системы ГАИ
 */
void showMainMenu();

/**
 * @brief Обрабатывает выбор пользователя из главного меню
 * @param choice Выбранный пункт меню
 * @param database Ссылка на базу данных ГАИ
 * @return true если программа должна продолжить работу, false если нужно выйти
 */
bool handleUserChoice(MenuChoice choice, PoliceDatabase& database);

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

    string systemTitle = " СИСТЕМА БАЗЫ ДАННЫХ ГАИ ";
    cout << systemTitle << "\n\n";

    showMainMenu();

    string choicePrompt = "Выберите операцию: ";
    cout << choicePrompt;

    int choice;
    cin >> choice;
    cin.ignore();

    if (cin.fail()) {
        string errorMessage = "Ошибка ввода. Программа завершена.";
        cout << errorMessage << endl;
        return 1;
    }

    bool shouldContinue = handleUserChoice(static_cast<MenuChoice>(choice), database);

    if (!shouldContinue) {
        string exitMessage = "Программа завершена.";
        cout << exitMessage << endl;
        return 0;
    }

    return 0;
}

void addNewVehicle(PoliceDatabase& database) {
    string addVehicleTitle = " ДОБАВЛЕНИЕ НОВОГО АВТОМОБИЛЯ ";
    cout << "\n" << addVehicleTitle << "\n";

    string licensePlatePrompt = "Гос. номер: ";
    string brandPrompt = "Марка: ";
    string modelPrompt = "Модель: ";
    string colorPrompt = "Цвет: ";
    string yearPrompt = "Год выпуска: ";
    string enginePrompt = "Номер двигателя: ";

    string licensePlate = getInput(licensePlatePrompt);
    string brand = getInput(brandPrompt);
    string model = getInput(modelPrompt);
    string color = getInput(colorPrompt);

    cout << yearPrompt;
    int year;
    cin >> year;

    if (cin.fail()) {
        string errorMessage = "Ошибка ввода года. Программа завершена.";
        cout << errorMessage << endl;
        exit(1);
    }
    cin.ignore();

    string engineNumber = getInput(enginePrompt);

    auto vehicle = make_shared<Vehicle>(licensePlate, brand, model, color, year, engineNumber);

    string addOwnerTitle = "ДОБАВЛЕНИЕ ВЛАДЕЛЬЦА ДЛЯ АВТОМОБИЛЯ:";
    cout << "\n" << addOwnerTitle << "\n";

    string passportPrompt = "Номер паспорта владельца: ";
    string namePrompt = "ФИО владельца: ";
    string addressPrompt = "Адрес владельца: ";
    string successMessage = "Автомобиль и владелец успешно добавлены!";

    string passport = getInput(passportPrompt);
    string name = getInput(namePrompt);
    string address = getInput(addressPrompt);

    auto owner = make_shared<Owner>(passport, name, address);
    vehicle->setCurrentOwner(owner);
    owner->addVehicle(vehicle);

    database.addVehicle(vehicle);

    cout << successMessage << endl;
}

void markVehicleAsStolen(PoliceDatabase& database) {
    string markStolenTitle = " ОТМЕТКА АВТОМОБИЛЯ КАК УГНАННОГО ";
    cout << "\n" << markStolenTitle << "\n";

    string licensePlatePrompt = "Введите гос. номер угнанного автомобиля: ";
    string successMessage = " отмечен как угнанный!";
    string notFoundMessage = " не найден!";

    string licensePlate = getInput(licensePlatePrompt);
    auto vehicle = database.findVehicleByLicensePlate(licensePlate);

    if (vehicle) {
        vehicle->setStolen(true);
        cout << "Автомобиль '" << licensePlate << "'" << successMessage << endl;
    }
    else {
        cout << "Автомобиль с номером '" << licensePlate << "'" << notFoundMessage << endl;
    }
}

void showMainMenu() {
    string menuTitle = " ГЛАВНОЕ МЕНЮ СИСТЕМЫ ГАИ ";
    string option1 = "1 - Информация об автомобиле по гос. номеру";
    string option2 = "2 - Информация о владельце по гос. номеру";
    string option3 = "3 - Информация об автомобиле по номеру двигателя";
    string option4 = "4 - Список угнанных автомобилей";
    string option5 = "5 - Автомобили в ДТП за период";
    string option6 = "6 - Наиболее угоняемые марки";
    string option7 = "7 - Статистика базы данных";
    string option8 = "8 - Добавить новый автомобиль";
    string option9 = "9 - Отметить автомобиль как угнанный";
    string option0 = "0 - Выход";

    cout << "\n" << menuTitle << "\n";
    cout << option1 << "\n";
    cout << option2 << "\n";
    cout << option3 << "\n";
    cout << option4 << "\n";
    cout << option5 << "\n";
    cout << option6 << "\n";
    cout << option7 << "\n";
    cout << option8 << "\n";
    cout << option9 << "\n";
    cout << option0 << "\n";
    cout << "\n";
}

bool handleUserChoice(MenuChoice choice, PoliceDatabase& database) {
    try {
        switch (choice) {
        case MenuChoice::VEHICLE_INFO_BY_PLATE:
            demonstrateVehicleSearch(database);
            break;
        case MenuChoice::OWNER_INFO_BY_PLATE:
            demonstrateOwnerSearch(database);
            break;
        case MenuChoice::VEHICLE_INFO_BY_ENGINE:
            demonstrateEngineNumberSearch(database);
            break;
        case MenuChoice::STOLEN_VEHICLES_LIST:
            demonstrateStolenVehicles(database);
            break;
        case MenuChoice::ACCIDENT_VEHICLES_IN_PERIOD:
            demonstrateAccidentVehicles(database);
            break;
        case MenuChoice::MOST_STOLEN_BRANDS:
            demonstrateMostStolenBrands(database);
            break;
        case MenuChoice::DATABASE_STATISTICS:
            showDatabaseStatistics(database);
            break;
        case MenuChoice::ADD_NEW_VEHICLE:
            addNewVehicle(database);
            break;
        case MenuChoice::MARK_VEHICLE_STOLEN:
            markVehicleAsStolen(database);
            break;
        case MenuChoice::EXIT:
            return false;
        default:
            string invalidChoiceMessage = "Неверный выбор! Программа завершена.";
            cout << invalidChoiceMessage << endl;
            return false;
        }
    }
    catch (const exception& e) {
        string errorMessage = "Произошла ошибка: ";
        string exitMessage = "Программа завершена.";
        cout << errorMessage << e.what() << "\n" << exitMessage << endl;
        return false;
    }
    catch (...) {
        string unknownErrorMessage = "Неизвестная ошибка. Программа завершена.";
        cout << unknownErrorMessage << endl;
        return false;
    }

    return true;
}

string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);

    if (cin.fail()) {
        string errorMessage = "Ошибка ввода. Программа завершена.";
        cout << errorMessage << endl;
        exit(1);
    }

    return input;
}

void demonstrateVehicleSearch(PoliceDatabase& database) {
    string searchTitle = "=== ПОИСК АВТОМОБИЛЯ ПО ГОСУДАРСТВЕННОМУ НОМЕРУ ===";
    string foundInfoTitle = "=== НАЙДЕНА ИНФОРМАЦИЯ ===";
    string ownerLabel = "Текущий владелец: ";
    string accidentsLabel = "Участвовал в ДТП: ";
    string timesLabel = " раз(а)";
    string notFoundMessage = " не найден!";

    cout << "\n" << searchTitle << "\n";

    string licensePlatePrompt = "Введите гос. номер автомобиля: ";
    string licensePlate = getInput(licensePlatePrompt);
    auto foundVehicle = database.findVehicleByLicensePlate(licensePlate);

    if (foundVehicle) {
        cout << "\n" << foundInfoTitle << "\n";
        cout << foundVehicle->getInfo() << "\n";

        auto owner = foundVehicle->getCurrentOwner();
        if (owner) {
            cout << ownerLabel << owner->getInfo() << "\n";
        }

        auto accidents = foundVehicle->getAccidents();
        if (!accidents.empty()) {
            cout << accidentsLabel << accidents.size() << timesLabel << "\n";
            for (const auto& accident : accidents) {
                cout << "  - " << accident->getInfo() << "\n";
            }
        }
    }
    else {
        cout << "Автомобиль с номером '" << licensePlate << "'" << notFoundMessage << endl;
    }
}

void demonstrateOwnerSearch(PoliceDatabase& database) {
    string searchTitle = " ПОИСК ВЛАДЕЛЬЦА ПО ГОСУДАРСТВЕННОМУ НОМЕРУ ";
    string foundInfoTitle = " НАЙДЕНА ИНФОРМАЦИЯ ";
    string ownerLabel = "Владелец: ";
    string vehiclesLabel = "Принадлежащие автомобили:";
    string noVehiclesMessage = "У владельца нет зарегистрированных автомобилей";
    string notFoundMessage = " не найден!";

    cout << "\n" << searchTitle << "\n";

    string licensePlatePrompt = "Введите гос. номер автомобиля: ";
    string licensePlate = getInput(licensePlatePrompt);
    auto foundOwner = database.findOwnerByLicensePlate(licensePlate);

    if (foundOwner) {
        cout << "\n" << foundInfoTitle << "\n";
        cout << ownerLabel << foundOwner->getInfo() << "\n";

        auto ownedVehicles = foundOwner->getOwnedVehicles();
        if (!ownedVehicles.empty()) {
            cout << vehiclesLabel << "\n";
            for (size_t i = 0; i < ownedVehicles.size(); ++i) {
                cout << i + 1 << ". " << ownedVehicles[i]->getInfo() << "\n";
            }
        }
        else {
            cout << noVehiclesMessage << "\n";
        }
    }
    else {
        cout << "Владелец автомобиля с номером '" << licensePlate << "'" << notFoundMessage << endl;
    }
}

void demonstrateEngineNumberSearch(PoliceDatabase& database) {
    const string searchTitle = " ПОИСК АВТОМОБИЛЯ ПО НОМЕРУ ДВИГАТЕЛЯ ";
    const string foundInfoTitle = " НАЙДЕНА ИНФОРМАЦИЯ ";
    const string mainInfoLabel = "Основная информация: ";
    const string ownerHistoryLabel = "ИСТОРИЯ ВЛАДЕЛЬЦЕВ:";
    const string noPreviousOwnersMessage = "  Нет предыдущих владельцев";
    const string accidentHistoryLabel = "ИСТОРИЯ ДТП:";
    const string noAccidentsMessage = "  Не участвовал в ДТП";
    const string currentOwnerLabel = "ТЕКУЩИЙ ВЛАДЕЛЕЦ: ";
    const string ownerNotSpecifiedMessage = "Не указан";
    const string stolenStatusLabel = "СТАТУС УГОНА: ";
    const string stolenMessage = "УГНАН";
    const string notStolenMessage = "Не угнан";
    const string notFoundMessage = " не найден!";

    cout << "\n" << searchTitle << "\n";

    string engineNumberPrompt = "Введите номер двигателя: ";
    string engineNumber = getInput(engineNumberPrompt);
    auto foundVehicle = database.findVehicleByEngineNumber(engineNumber);

    if (foundVehicle) {
        cout << "\n" << foundInfoTitle << "\n";
        cout << mainInfoLabel << foundVehicle->getInfo() << "\n\n";

        cout << ownerHistoryLabel << "\n";
        auto previousOwners = foundVehicle->getPreviousOwners();
        if (previousOwners.empty()) {
            cout << noPreviousOwnersMessage << "\n";
        }
        else {
            for (const auto& owner : previousOwners) {
                cout << "  - " << owner->getInfo() << "\n";
            }
        }

        cout << "\n" << accidentHistoryLabel << "\n";
        auto accidents = foundVehicle->getAccidents();
        if (accidents.empty()) {
            cout << noAccidentsMessage << "\n";
        }
        else {
            for (const auto& accident : accidents) {
                cout << "  - " << accident->getInfo() << "\n";
            }
        }

        cout << "\n" << currentOwnerLabel;
        auto currentOwner = foundVehicle->getCurrentOwner();
        if (currentOwner) {
            cout << currentOwner->getInfo() << "\n";
        }
        else {
            cout << ownerNotSpecifiedMessage << "\n";
        }

        cout << stolenStatusLabel;
        if (foundVehicle->getIsStolen()) {
            cout << stolenMessage << "\n";
        }
        else {
            cout << notStolenMessage << "\n";
        }
    }
    else {
        cout << "Автомобиль с номером двигателя '" << engineNumber << "'" << notFoundMessage << endl;
    }
}

void demonstrateStolenVehicles(PoliceDatabase& database) {
    string listTitle = " СПИСОК УГНАННЫХ АВТОМОБИЛЕЙ ";
    string noStolenMessage = "Угнанных автомобилей нет.";
    string foundMessage = "Найдено угнанных автомобилей: ";
    string ownerLabel = "   Владелец: ";

    cout << "\n" << listTitle << "\n";

    auto stolenVehicles = database.getStolenVehicles();
    if (stolenVehicles.empty()) {
        cout << noStolenMessage << "\n";
    }
    else {
        cout << foundMessage << stolenVehicles.size() << "\n\n";
        for (size_t i = 0; i < stolenVehicles.size(); ++i) {
            cout << i + 1 << ". " << stolenVehicles[i]->getInfo() << "\n";
            auto owner = stolenVehicles[i]->getCurrentOwner();
            if (owner) {
                cout << ownerLabel << owner->getInfo() << "\n";
            }
            cout << "---\n";
        }
    }
}

void demonstrateAccidentVehicles(PoliceDatabase& database) {
    string listTitle = " АВТОМОБИЛИ В ДТП ЗА ПЕРИОД ";
    string noAccidentsMessage = "В указанный период ДТП не зарегистрировано.";
    string foundMessage = "Автомобили, попавшие в ДТП: ";
    string startDateMessage = "Введите начальную дату:";
    string endDateMessage = "Введите конечную дату:";
    string dayPrompt = "День: ";
    string monthPrompt = "Месяц: ";
    string yearPrompt = "Год: ";

    cout << "\n" << listTitle << "\n";

    int startDay, startMonth, startYear, endDay, endMonth, endYear;
    cout << startDateMessage << "\n";
    cout << dayPrompt; cin >> startDay;
    cout << monthPrompt; cin >> startMonth;
    cout << yearPrompt; cin >> startYear;

    cout << endDateMessage << "\n";
    cout << dayPrompt; cin >> endDay;
    cout << monthPrompt; cin >> endMonth;
    cout << yearPrompt; cin >> endYear;
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
        cout << noAccidentsMessage << "\n";
    }
    else {
        cout << foundMessage << accidentVehicles.size() << "\n\n";
        for (size_t i = 0; i < accidentVehicles.size(); ++i) {
            cout << i + 1 << ". " << accidentVehicles[i]->getInfo() << "\n";
        }
    }
}

void demonstrateMostStolenBrands(PoliceDatabase& database) {
    string listTitle = " НАИБОЛЕЕ УГОНЯЕМЫЕ МАРКИ АВТОМОБИЛЕЙ ";
    string noDataMessage = "Нет данных об угонах.";
    string ratingMessage = "Рейтинг марок по количеству угонов:";
    string theftSingular = " угон";
    string theftPlural = " угона";

    cout << "\n" << listTitle << "\n";

    auto mostStolen = database.getMostStolenBrands();
    if (mostStolen.empty()) {
        cout << noDataMessage << "\n";
    }
    else {
        cout << ratingMessage << "\n\n";
        for (size_t i = 0; i < mostStolen.size(); ++i) {
            cout << i + 1 << ". " << mostStolen[i].first << " - " << mostStolen[i].second;
            if (mostStolen[i].second == 1) {
                cout << theftSingular << "\n";
            }
            else {
                cout << theftPlural << "\n";
            }
        }
    }
}

void showDatabaseStatistics(PoliceDatabase& database) {
    string statsTitle = " СТАТИСТИКА БАЗЫ ДАННЫХ ГАИ ";
    string totalOwnersMessage = "Всего владельцев: ";
    string totalVehiclesMessage = "Всего автомобилей: ";
    string totalAccidentsMessage = "Всего ДТП: ";
    string stolenVehiclesMessage = "Угнанных автомобилей: ";
    string mostStolenMessage = "Самая угоняемая марка: ";
    string theftsMessage = " угонов";

    cout << "\n" << statsTitle << "\n";
    cout << totalOwnersMessage << database.getAllOwners().size() << "\n";
    cout << totalVehiclesMessage << database.getAllVehicles().size() << "\n";
    cout << totalAccidentsMessage << database.getAllAccidents().size() << "\n";
    cout << stolenVehiclesMessage << database.getStolenVehicles().size() << "\n";

    auto mostStolen = database.getMostStolenBrands();
    if (!mostStolen.empty()) {
        cout << mostStolenMessage << mostStolen[0].first << " (" << mostStolen[0].second << theftsMessage << ")\n";
    }
}

void createTestData(PoliceDatabase& database) {
    auto owner1 = make_shared<Owner>("4500112233", "Иванов Иван Иванович", "г. Москва, ул. Ленина, д. 1");
    auto owner2 = make_shared<Owner>("4500445566", "Петров Петр Петрович", "г. Москва, ул. Пушкина, д. 10");
    auto owner3 = make_shared<Owner>("4500778899", "Сидорова Мария Сергеевна", "г. Москва, пр. Мира, д. 25");
    auto previousOwner = make_shared<Owner>("4500998877", "Кузнецов Алексей", "г. Москва, ул. Садовая, д. 5");

    auto vehicle1 = make_shared<Vehicle>("A123BC777", "Toyota", "Camry", "Черный", 2018, "T123456789");
    auto vehicle2 = make_shared<Vehicle>("B456DE777", "BMW", "X5", "Белый", 2020, "B987654321");
    auto vehicle3 = make_shared<Vehicle>("C789FG777", "Lada", "Granta", "Красный", 2015, "L555555555");
    auto vehicle4 = make_shared<Vehicle>("D111EE777", "BMW", "X6", "Синий", 2021, "B111111111");
    auto vehicle5 = make_shared<Vehicle>("E222FF777", "Toyota", "RAV4", "Серебристый", 2019, "T222222222");

    vehicle1->setCurrentOwner(owner1);
    vehicle1->addPreviousOwner(previousOwner);
    owner1->addVehicle(vehicle1);

    vehicle2->setCurrentOwner(owner2);
    vehicle2->setStolen(true);
    owner2->addVehicle(vehicle2);

    vehicle3->setCurrentOwner(owner3);
    owner3->addVehicle(vehicle3);

    vehicle4->setCurrentOwner(owner1);
    vehicle4->setStolen(true);
    owner1->addVehicle(vehicle4);

    vehicle5->setCurrentOwner(owner2);
    vehicle5->setStolen(true);
    owner2->addVehicle(vehicle5);

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