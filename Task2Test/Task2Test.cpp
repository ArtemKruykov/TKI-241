#include "CppUnitTest.h"
#include "../decision2/PoliceDatabase.h"
#include "../decision2/Vehicle.h"
#include "../decision2/Owner.h"
#include "../decision2/Accident.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PoliceDatabaseTests
{
    TEST_CLASS(PoliceDatabaseTests)
    {
    public:

        TEST_METHOD(TestAddAndFindVehicle)
        {
            PoliceDatabase database;
            auto vehicle = std::make_shared<Vehicle>("A123BC777", "Toyota", "Camry", "Black", 2020, "ENG123456");
            database.addVehicle(vehicle);

            auto foundVehicle = database.findVehicleByLicensePlate("A123BC777");
            Assert::IsNotNull(foundVehicle.get());
            Assert::AreEqual(std::string("A123BC777"), foundVehicle->getLicensePlate());
            Assert::AreEqual(std::string("Toyota"), foundVehicle->getBrand());
        }

        TEST_METHOD(TestFindNonExistentVehicle)
        {
            PoliceDatabase database;
            auto foundVehicle = database.findVehicleByLicensePlate("NONEXISTENT");
            Assert::IsNull(foundVehicle.get());
        }

        TEST_METHOD(TestAddAndFindOwner)
        {
            PoliceDatabase database;
            auto owner = std::make_shared<Owner>("1234567890", "John Doe", "Moscow, Street 1");
            database.addOwner(owner);

            auto owners = database.getAllOwners();
            Assert::AreEqual(size_t(1), owners.size());
            Assert::AreEqual(std::string("John Doe"), owners[0]->getFullName());
        }

        TEST_METHOD(TestVehicleOwnerRelationship)
        {
            PoliceDatabase database;

            auto owner = std::make_shared<Owner>("1234567890", "John Doe", "Moscow, Street 1");
            auto vehicle = std::make_shared<Vehicle>("A123BC777", "Toyota", "Camry", "Black", 2020, "ENG123456");

            vehicle->setCurrentOwner(owner);
            owner->addVehicle(vehicle);

            database.addOwner(owner);
            database.addVehicle(vehicle);

            auto foundOwner = database.findOwnerByLicensePlate("A123BC777");
            Assert::IsNotNull(foundOwner.get());
            Assert::AreEqual(std::string("John Doe"), foundOwner->getFullName());
        }

        TEST_METHOD(TestStolenVehicles)
        {
            PoliceDatabase database;

            auto vehicle1 = std::make_shared<Vehicle>("A111AA777", "BMW", "X5", "White", 2021, "ENG111111");
            auto vehicle2 = std::make_shared<Vehicle>("B222BB777", "Audi", "A4", "Black", 2020, "ENG222222");

            vehicle1->setStolen(true);
            vehicle2->setStolen(false);

            database.addVehicle(vehicle1);
            database.addVehicle(vehicle2);

            auto stolenVehicles = database.getStolenVehicles();
            Assert::AreEqual(size_t(1), stolenVehicles.size());
            Assert::AreEqual(std::string("A111AA777"), stolenVehicles[0]->getLicensePlate());
        }

        TEST_METHOD(TestFindVehicleByEngineNumber)
        {
            PoliceDatabase database;
            auto vehicle = std::make_shared<Vehicle>("A123BC777", "Toyota", "Camry", "Black", 2020, "UNIQUE123");
            database.addVehicle(vehicle);

            auto foundVehicle = database.findVehicleByEngineNumber("UNIQUE123");
            Assert::IsNotNull(foundVehicle.get());
            Assert::AreEqual(std::string("UNIQUE123"), foundVehicle->getEngineNumber());
        }

        TEST_METHOD(TestAccidentCreation)
        {
            PoliceDatabase database;

            std::tm accidentDate = {};
            accidentDate.tm_year = 124;
            accidentDate.tm_mon = 0;
            accidentDate.tm_mday = 15;

            auto accident = std::make_shared<Accident>("ACC001", accidentDate,
                "Collision at intersection", "Main Street - First Avenue");

            database.addAccident(accident);

            auto accidents = database.getAllAccidents();
            Assert::AreEqual(size_t(1), accidents.size());
            Assert::AreEqual(std::string("ACC001"), accidents[0]->getId());
        }

        TEST_METHOD(TestMostStolenBrands)
        {
            PoliceDatabase database;

            auto vehicle1 = std::make_shared<Vehicle>("A111AA777", "BMW", "X5", "White", 2021, "ENG111111");
            auto vehicle2 = std::make_shared<Vehicle>("B222BB777", "BMW", "X3", "Black", 2020, "ENG222222");
            auto vehicle3 = std::make_shared<Vehicle>("C333CC777", "Audi", "A4", "Red", 2019, "ENG333333");

            vehicle1->setStolen(true);
            vehicle2->setStolen(true);
            vehicle3->setStolen(true);

            database.addVehicle(vehicle1);
            database.addVehicle(vehicle2);
            database.addVehicle(vehicle3);

            auto mostStolen = database.getMostStolenBrands();
            Assert::IsTrue(mostStolen.size() >= 1);
            Assert::AreEqual(std::string("BMW"), mostStolen[0].first);
            Assert::AreEqual(2, mostStolen[0].second);
        }

        TEST_METHOD(TestVehicleInfo)
        {
            auto vehicle = std::make_shared<Vehicle>("A123BC777", "Toyota", "Camry", "Black", 2020, "ENG123456");
            std::string info = vehicle->getInfo();

            Assert::IsTrue(info.find("Toyota") != std::string::npos);
            Assert::IsTrue(info.find("A123BC777") != std::string::npos);
            Assert::IsTrue(info.find("2020") != std::string::npos);
        }

        TEST_METHOD(TestOwnerInfo)
        {
            auto owner = std::make_shared<Owner>("1234567890", "John Doe", "Moscow, Street 1");
            std::string info = owner->getInfo();

            Assert::IsTrue(info.find("John Doe") != std::string::npos);
            Assert::IsTrue(info.find("1234567890") != std::string::npos);
        }

        TEST_METHOD(TestGetAllVehicles)
        {
            PoliceDatabase database;

            auto vehicle1 = std::make_shared<Vehicle>("A111AA777", "BMW", "X5", "White", 2021, "ENG111111");
            auto vehicle2 = std::make_shared<Vehicle>("B222BB777", "Audi", "A4", "Black", 2020, "ENG222222");

            database.addVehicle(vehicle1);
            database.addVehicle(vehicle2);

            auto allVehicles = database.getAllVehicles();
            Assert::AreEqual(size_t(2), allVehicles.size());
        }

        TEST_METHOD(TestGetAllOwners)
        {
            PoliceDatabase database;

            auto owner1 = std::make_shared<Owner>("1111111111", "John Doe", "Address 1");
            auto owner2 = std::make_shared<Owner>("2222222222", "Jane Smith", "Address 2");

            database.addOwner(owner1);
            database.addOwner(owner2);

            auto allOwners = database.getAllOwners();
            Assert::AreEqual(size_t(2), allOwners.size());
        }

        TEST_METHOD(TestAccidentVehiclesInPeriod)
        {
            PoliceDatabase database;

            auto vehicle1 = std::make_shared<Vehicle>("A111AA777", "BMW", "X5", "White", 2021, "ENG111111");
            auto vehicle2 = std::make_shared<Vehicle>("B222BB777", "Audi", "A4", "Black", 2020, "ENG222222");

            database.addVehicle(vehicle1);
            database.addVehicle(vehicle2);

            std::tm startDate = {};
            startDate.tm_year = 124;
            startDate.tm_mon = 0;
            startDate.tm_mday = 1;

            std::tm endDate = {};
            endDate.tm_year = 124;
            endDate.tm_mon = 11;
            endDate.tm_mday = 31;

            std::tm accidentDate = {};
            accidentDate.tm_year = 124;
            accidentDate.tm_mon = 5;
            accidentDate.tm_mday = 15;

            auto accident = std::make_shared<Accident>("ACC001", accidentDate, "Test accident", "Test location");
            accident->addInvolvedVehicle(vehicle1);
            database.addAccident(accident);

            vehicle1->addAccident(accident);

            auto accidentVehicles = database.getAccidentVehiclesInPeriod(startDate, endDate);
            Assert::AreEqual(size_t(1), accidentVehicles.size());
            Assert::AreEqual(std::string("A111AA777"), accidentVehicles[0]->getLicensePlate());
        }
    };

    TEST_CLASS(VehicleTests)
    {
    public:

        TEST_METHOD(TestVehicleConstructor)
        {
            Vehicle vehicle("A123BC777", "Toyota", "Camry", "Black", 2020, "ENG123456");

            Assert::AreEqual(std::string("A123BC777"), vehicle.getLicensePlate());
            Assert::AreEqual(std::string("Toyota"), vehicle.getBrand());
            Assert::AreEqual(std::string("Camry"), vehicle.getModel());
            Assert::AreEqual(std::string("Black"), vehicle.getColor());
            Assert::AreEqual(2020, vehicle.getYear());
            Assert::AreEqual(std::string("ENG123456"), vehicle.getEngineNumber());
            Assert::IsFalse(vehicle.getIsStolen());
        }

        TEST_METHOD(TestStolenStatus)
        {
            Vehicle vehicle("A123BC777", "Toyota", "Camry", "Black", 2020, "ENG123456");

            Assert::IsFalse(vehicle.getIsStolen());

            vehicle.setStolen(true);
            Assert::IsTrue(vehicle.getIsStolen());

            vehicle.setStolen(false);
            Assert::IsFalse(vehicle.getIsStolen());
        }

        TEST_METHOD(TestOwnerAssignment)
        {
            auto owner = std::make_shared<Owner>("1234567890", "John Doe", "Moscow, Street 1");
            Vehicle vehicle("A123BC777", "Toyota", "Camry", "Black", 2020, "ENG123456");

            vehicle.setCurrentOwner(owner);
            auto currentOwner = vehicle.getCurrentOwner();

            Assert::IsNotNull(currentOwner.get());
            Assert::AreEqual(std::string("John Doe"), currentOwner->getFullName());
        }

        TEST_METHOD(TestPreviousOwners)
        {
            auto owner1 = std::make_shared<Owner>("1111111111", "Previous Owner", "Address 1");
            auto owner2 = std::make_shared<Owner>("2222222222", "Current Owner", "Address 2");
            Vehicle vehicle("A123BC777", "Toyota", "Camry", "Black", 2020, "ENG123456");

            vehicle.addPreviousOwner(owner1);
            vehicle.setCurrentOwner(owner2);

            auto previousOwners = vehicle.getPreviousOwners();
            Assert::AreEqual(size_t(1), previousOwners.size());
            Assert::AreEqual(std::string("Previous Owner"), previousOwners[0]->getFullName());
        }

        TEST_METHOD(TestAccidents)
        {
            Vehicle vehicle("A123BC777", "Toyota", "Camry", "Black", 2020, "ENG123456");

            std::tm accidentDate = {};
            accidentDate.tm_year = 124;
            accidentDate.tm_mon = 0;
            accidentDate.tm_mday = 15;

            auto accident = std::make_shared<Accident>("ACC001", accidentDate, "Test accident", "Test location");
            vehicle.addAccident(accident);

            auto accidents = vehicle.getAccidents();
            Assert::AreEqual(size_t(1), accidents.size());
            Assert::AreEqual(std::string("ACC001"), accidents[0]->getId());
        }
    };

    TEST_CLASS(OwnerTests)
    {
    public:

        TEST_METHOD(TestOwnerConstructor)
        {
            Owner owner("1234567890", "John Doe", "Moscow, Street 1");

            Assert::AreEqual(std::string("1234567890"), owner.getPassportNumber());
            Assert::AreEqual(std::string("John Doe"), owner.getFullName());
            Assert::AreEqual(std::string("Moscow, Street 1"), owner.getAddress());
        }

        TEST_METHOD(TestAddVehicleToOwner)
        {
            auto owner = std::make_shared<Owner>("1234567890", "John Doe", "Moscow, Street 1");
            auto vehicle = std::make_shared<Vehicle>("A123BC777", "Toyota", "Camry", "Black", 2020, "ENG123456");

            owner->addVehicle(vehicle);
            auto ownedVehicles = owner->getOwnedVehicles();

            Assert::AreEqual(size_t(1), ownedVehicles.size());
            Assert::AreEqual(std::string("A123BC777"), ownedVehicles[0]->getLicensePlate());
        }

        TEST_METHOD(TestMultipleVehiclesForOwner)
        {
            auto owner = std::make_shared<Owner>("1234567890", "John Doe", "Moscow, Street 1");
            auto vehicle1 = std::make_shared<Vehicle>("A111AA777", "BMW", "X5", "White", 2021, "ENG111111");
            auto vehicle2 = std::make_shared<Vehicle>("B222BB777", "Audi", "A4", "Black", 2020, "ENG222222");

            owner->addVehicle(vehicle1);
            owner->addVehicle(vehicle2);

            auto ownedVehicles = owner->getOwnedVehicles();
            Assert::AreEqual(size_t(2), ownedVehicles.size());
        }
    };

    TEST_CLASS(AccidentTests)
    {
    public:

        TEST_METHOD(TestAccidentConstructor)
        {
            std::tm accidentDate = {};
            accidentDate.tm_year = 124;
            accidentDate.tm_mon = 0;
            accidentDate.tm_mday = 15;

            Accident accident("ACC001", accidentDate, "Collision", "Main Street");

            Assert::AreEqual(std::string("ACC001"), accident.getId());
            Assert::AreEqual(std::string("Collision"), accident.getDescription());
            Assert::AreEqual(std::string("Main Street"), accident.getLocation());
        }

        TEST_METHOD(TestAddVehicleToAccident)
        {
            std::tm accidentDate = {};
            accidentDate.tm_year = 124;
            accidentDate.tm_mon = 0;
            accidentDate.tm_mday = 15;

            auto accident = std::make_shared<Accident>("ACC001", accidentDate, "Collision", "Main Street");
            auto vehicle = std::make_shared<Vehicle>("A123BC777", "Toyota", "Camry", "Black", 2020, "ENG123456");

            accident->addInvolvedVehicle(vehicle);
            auto involvedVehicles = accident->getInvolvedVehicles();

            Assert::AreEqual(size_t(1), involvedVehicles.size());
            Assert::AreEqual(std::string("A123BC777"), involvedVehicles[0]->getLicensePlate());
        }

        TEST_METHOD(TestMultipleVehiclesInAccident)
        {
            std::tm accidentDate = {};
            accidentDate.tm_year = 124;
            accidentDate.tm_mon = 0;
            accidentDate.tm_mday = 15;

            auto accident = std::make_shared<Accident>("ACC001", accidentDate, "Multi-car collision", "Highway");
            auto vehicle1 = std::make_shared<Vehicle>("A111AA777", "BMW", "X5", "White", 2021, "ENG111111");
            auto vehicle2 = std::make_shared<Vehicle>("B222BB777", "Audi", "A4", "Black", 2020, "ENG222222");

            accident->addInvolvedVehicle(vehicle1);
            accident->addInvolvedVehicle(vehicle2);

            auto involvedVehicles = accident->getInvolvedVehicles();
            Assert::AreEqual(size_t(2), involvedVehicles.size());
        }

        TEST_METHOD(TestAccidentInfo)
        {
            std::tm accidentDate = {};
            accidentDate.tm_year = 124;
            accidentDate.tm_mon = 0;
            accidentDate.tm_mday = 15;

            auto accident = std::make_shared<Accident>("ACC001", accidentDate, "Test collision", "Main Street");
            std::string info = accident->getInfo();

            Assert::IsTrue(info.find("ACC001") != std::string::npos);
            Assert::IsTrue(info.find("Test collision") != std::string::npos);
        }
    };

    TEST_CLASS(IntegrationTests)
    {
    public:

        TEST_METHOD(TestCompleteScenario)
        {
            PoliceDatabase database;

            auto owner1 = std::make_shared<Owner>("4500112233", "Ivan Ivanov", "Moscow, Lenina 1");
            auto owner2 = std::make_shared<Owner>("4500445566", "Petr Petrov", "Moscow, Pushkina 10");

            database.addOwner(owner1);
            database.addOwner(owner2);

            auto vehicle1 = std::make_shared<Vehicle>("A123BC777", "Toyota", "Camry", "Black", 2018, "T123456789");
            auto vehicle2 = std::make_shared<Vehicle>("B456DE777", "BMW", "X5", "White", 2020, "B987654321");

            vehicle1->setCurrentOwner(owner1);
            vehicle2->setCurrentOwner(owner2);
            vehicle2->setStolen(true);

            owner1->addVehicle(vehicle1);
            owner2->addVehicle(vehicle2);

            database.addVehicle(vehicle1);
            database.addVehicle(vehicle2);

            std::tm accidentDate = {};
            accidentDate.tm_year = 124;
            accidentDate.tm_mon = 5;
            accidentDate.tm_mday = 15;

            auto accident = std::make_shared<Accident>("DT001", accidentDate, "Intersection collision", "Lenina - Pushkina");
            accident->addInvolvedVehicle(vehicle1);
            database.addAccident(accident);

            vehicle1->addAccident(accident);

            auto foundVehicle = database.findVehicleByLicensePlate("A123BC777");
            Assert::IsNotNull(foundVehicle.get());

            auto foundOwner = database.findOwnerByLicensePlate("A123BC777");
            Assert::IsNotNull(foundOwner.get());
            Assert::AreEqual(std::string("Ivan Ivanov"), foundOwner->getFullName());

            auto stolenVehicles = database.getStolenVehicles();
            Assert::AreEqual(size_t(1), stolenVehicles.size());

            auto accidents = foundVehicle->getAccidents();
            Assert::AreEqual(size_t(1), accidents.size());
        }
    };
}