#include "XyzEmployeeManager.h"
#include "XyzEmployeeBase.h"
#include "EmployeeIDGenerator.h"
#include "HelperFunctions.h"
#include "TablePrinter.h"
#include "EmployeeFactory.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>
#include <cctype>

/**
 * @brief Constructor: Initializes counters and seeds RNG.
 * @return void
 */
XyzEmployeeManager::XyzEmployeeManager() : mEmployeeCounter(0)
{
    // seed the random number generator to get different random values on every program run
    std::srand(static_cast<unsigned int>(std::time(0)));
}

/**
 * @brief Destructor: Releases all employee objects.
 * @return void
 */
XyzEmployeeManager::~XyzEmployeeManager()
{
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
    {
        delete mActiveInactiveEmployees[sI];
    }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
    {
        delete mResignedEmployees[sI];
    }
}

/**
 * @brief Starts the main menu loop.
 * @return void
 */
void XyzEmployeeManager::start()
{
    pShowMainMenu();
}

/**
 * @brief Displays the main menu and handles user choices.
 * @return void
 */
void XyzEmployeeManager::pShowMainMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {"Add an Employee", "Remove an Employee", "Get Employee Details", "Others"};
        HelperFunctions::printMenu("Employee Management System", sOptions, MaxMainMenuOptions, ExitMainMenu, RootMenuContext);
        std::cout << "Your Choice: ";
        sChoice = HelperFunctions::getMenuChoice(1, MaxMainMenuOptions, ExitMainMenu);

        switch (sChoice)
        {
        case AddEmployee:          pShowAddEmployeeMenu(); break;
        case RemoveEmployee:       pShowRemoveEmployeeMenu(); break;
        case GetEmployeeDetails:   pShowEmployeeDetailsMenu(); break;
        case DoSomethingElse:      pShowOtherOperationsMenu(); break;
        case ExitMainMenu:         std::cout << "Exiting system. Goodbye!\n"; break;
        default:                   std::cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (sChoice != ExitMainMenu);
}

/**
 * @brief Displays the add employee menu.
 * @return void
 */
void XyzEmployeeManager::pShowAddEmployeeMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {"Add an Employee at Random", "Add an Employee (F/C/I)"};
        HelperFunctions::printMenu("Add an Employee:", sOptions, MaxAddMenuOptions, BackToMainMenu, SubMenuContext);
        std::cout << "Your Choice: ";
        sChoice = HelperFunctions::getMenuChoice(1, MaxAddMenuOptions, BackToMainMenu);

        switch (sChoice)
        {
        case AddRandomEmployee:    addEmployee(HelperFunctions::getRandomType(), true); break;
        case AddSpecificEmployee:  pShowSpecificEmployeeMenu(); break;
        case BackToMainMenu:       break;
        default:                   std::cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (sChoice != BackToMainMenu);
}

/**
 * @brief Displays the specific-employee (F/C/I) menu.
 * @return void
 */
void XyzEmployeeManager::pShowSpecificEmployeeMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {"Add Full-Time Employee", "Add Contractor Employee", "Add Intern Employee"};
        HelperFunctions::printMenu("Add an Employee (F/C/I):", sOptions, SpecificEmployeeMenuCount, BackToAddMenu, SubMenuContext);
        std::cout << "Your Choice: ";
        sChoice = HelperFunctions::getMenuChoice(1, SpecificEmployeeMenuCount, BackToAddMenu);

        switch (sChoice)
        {
        case AddFullTimeEmployee:     addEmployee(FullTime, false); break;
        case AddContractorEmployee:   addEmployee(Contractor, false); break;
        case AddInternEmployee:       addEmployee(Intern, false); break;
        case BackToAddMenu:           break;
        default:                      std::cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (sChoice != BackToAddMenu);
}

/**
 * @brief Displays the search menu (by ID/Name).
 * @return void
 */
void XyzEmployeeManager::pShowSearchMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {"Search by Employee ID", "Search by Employee Name"};
        HelperFunctions::printMenu("Search Employee", sOptions, MaxSearchMenuOptions, BackToMainMenuFromSearch, SubMenuContext);
        std::cout << "Your Choice: ";
        sChoice = HelperFunctions::getMenuChoice(1, MaxSearchMenuOptions, BackToMainMenuFromSearch);

        std::string sId, sName;
        switch (sChoice)
        {
        case SearchById:
            std::cout << "\nEnter Employee ID to search: ";
            std::cin >> sId;
            searchById(sId);
            break;
        case SearchByName:
            std::cout << "\nEnter Employee Name to search (case-sensitive): ";
            std::getline(std::cin >> std::ws, sName);
            searchByName(sName);
            break;
        case BackToMainMenuFromSearch:
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (sChoice != BackToMainMenuFromSearch);
}

/**
 * @brief Displays the details menu and summary submenus.
 * @return void
 */
void XyzEmployeeManager::pShowEmployeeDetailsMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {
            "All Employees Summary", "Employee Summary (F/C/I)",
            "Employee Summary (M/F)", "Employee Summary (A/I/R)",
            "Display Employee Details"};
        HelperFunctions::printMenu("Get Employee Details:", sOptions, MaxDetailsMenuOptions, BackToMainMenuFromDetails, SubMenuContext);
        std::cout << "Your Choice: ";
        sChoice = HelperFunctions::getMenuChoice(1, MaxDetailsMenuOptions, BackToMainMenuFromDetails);

        switch (sChoice)
        {
        case AllEmployeesSummary:
            printSummaryAll();
            break;
        case SummaryByType:
        {
            int sSubChoice = 0;
            do {
                const char *sSubOptions[] = {"Full-Time", "Contractor", "Intern"};
                HelperFunctions::printMenu("Select Employee Type:", sSubOptions, TypeSubmenuCount, BackToMainMenuFromDetails, SubMenuContext);
                std::cout << "Your Choice: ";
                sSubChoice = HelperFunctions::getMenuChoice(1, TypeSubmenuCount, BackToMainMenuFromDetails);
                if (sSubChoice == BackToMainMenuFromDetails) break;

                switch (static_cast<TypeSubmenu>(sSubChoice))
                {
                    case TypeFT:          printSummaryByType(FullTime); break;
                    case TypeContractor:  printSummaryByType(Contractor); break;
                    case TypeIntern:      printSummaryByType(Intern); break;
                    default:              std::cout << "Invalid choice. Please try again.\n"; continue;
                }
                break;
            } while (true);
            break;
        }
        case SummaryByGender:
        {
            int sSubChoice = 0;
            do {
                const char *sSubOptions[] = {"Male", "Female"};
                HelperFunctions::printMenu("Select Gender:", sSubOptions, GenderSubmenuCount, BackToMainMenuFromDetails, SubMenuContext);
                std::cout << "Your Choice: ";
                sSubChoice = HelperFunctions::getMenuChoice(1, GenderSubmenuCount, BackToMainMenuFromDetails);
                if (sSubChoice == BackToMainMenuFromDetails) break;

                switch (static_cast<GenderSubmenu>(sSubChoice))
                {
                    case GenderMale:    printSummaryByGender("Male"); break;
                    case GenderFemale:  printSummaryByGender("Female"); break;
                    default:            std::cout << "Invalid choice. Please try again.\n"; continue;
                }
                break;
            } while (true);
            break;
        }
        case SummaryByStatus:
        {
            int sSubChoice = 0;
            do {
                const char *sSubOptions[] = {"Active", "Inactive", "Resigned"};
                HelperFunctions::printMenu("Select Employment Status:", sSubOptions, StatusSubmenuCount, BackToMainMenuFromDetails, SubMenuContext);
                std::cout << "Your Choice: ";
                sSubChoice = HelperFunctions::getMenuChoice(1, StatusSubmenuCount, BackToMainMenuFromDetails);
                if (sSubChoice == BackToMainMenuFromDetails) break;

                switch (static_cast<StatusSubmenu>(sSubChoice))
                {
                    case StatusActive:    printSummaryByStatus(Active); break;
                    case StatusInactive:  printSummaryByStatus(Inactive); break;
                    case StatusResigned:  printSummaryByStatus(Resigned); break;
                    default:              std::cout << "Invalid choice. Please try again.\n"; continue;
                }
                break;
            } while (true);
            break;
        }
        case DisplayDetailsById:
        {
            std::cout << "\nEnter Employee ID to display details: ";
            std::string sId;
            std::cin >> sId;
            printDetailsById(sId);
            break;
        }
        case BackToMainMenuFromDetails:
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (sChoice != BackToMainMenuFromDetails);
}

/**
 * @brief Displays the other operations menu.
 * @return void
 */
void XyzEmployeeManager::pShowOtherOperationsMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {
            "Add 'n' number of leaves to all the Full-Time employees",
            "Convert an Intern to Full-Time employee.",
            "Search an Employee by ID",
            "Search an Employee by Name"};
        HelperFunctions::printMenu("Do something else:", sOptions, MaxOperationsMenuOptions, BackToMainMenuFromOperations, SubMenuContext);
        std::cout << "Your Choice: ";
        sChoice = HelperFunctions::getMenuChoice(1, MaxOperationsMenuOptions, BackToMainMenuFromOperations);

        std::string sId, sName;
        int sLeaves;
        switch (sChoice)
        {
        case AddLeavesToFullTime:
            std::cout << "\nEnter number of leaves to add to all Full-Time employees: ";
            std::cin >> sLeaves;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                sLeaves = 0;
            }
            if (sLeaves < 0) sLeaves = 0;
            if (sLeaves > MaxLeavesPerYear) sLeaves = MaxLeavesPerYear;
            addLeavesToAllFullTime(sLeaves);
            break;
        case ConvertInternToFullTime:
            std::cout << "\nEnter Intern's Employee ID to convert: ";
            std::cin >> sId;
            convertInternToFullTime(sId);
            break;
        case SearchEmployeeById:
            std::cout << "\nEnter Employee ID to search: ";
            std::cin >> sId;
            searchById(sId);
            break;
        case SearchEmployeeByName:
            std::cout << "\nEnter Employee Name to search (case-sensitive): ";
            std::getline(std::cin >> std::ws, sName);
            searchByName(sName);
            break;
        case BackToMainMenuFromOperations:
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (sChoice != BackToMainMenuFromOperations);
}

/**
 * @brief Displays the remove employee menu and handles resignation flow.
 * @return void
 */
void XyzEmployeeManager::pShowRemoveEmployeeMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {"Remove Full-Time Employee", "Remove Contractor Employee", "Remove Intern Employee"};
        HelperFunctions::printMenu("Remove Employee:", sOptions, RemoveMenuCount, BackToMainMenu, SubMenuContext);
        std::cout << "Your Choice: ";
        sChoice = HelperFunctions::getMenuChoice(1, RemoveMenuCount, BackToMainMenu);

        std::string sId;
        switch (sChoice)
        {
        case TypeFT:
            std::cout << "\nEnter Full-Time Employee ID to remove: ";
            std::cin >> sId;
            moveEmployeeToResigned(sId, FullTime);
            break;
        case TypeContractor:
            std::cout << "\nEnter Contractor Employee ID to remove: ";
            std::cin >> sId;
            moveEmployeeToResigned(sId, Contractor);
            break;
        case TypeIntern:
            std::cout << "\nEnter Intern Employee ID to remove: ";
            std::cin >> sId;
            moveEmployeeToResigned(sId, Intern);
            break;
        case BackToMainMenu:
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (sChoice != BackToMainMenu);
}

/**
 * @brief Adds an employee either randomly or via validated manual inputs.
 * @param typeParm EmployeeType to add.
 * @param isRandomParm If true, randomize all fields.
 * @return void
 */
void XyzEmployeeManager::addEmployee(EmployeeType typeParm, bool isRandomParm)
{
    std::string sGender, sName, sDob, sDoj;

    if (isRandomParm) {
        sGender = HelperFunctions::getRandomGender();
        sName   = HelperFunctions::getRandomName(sGender);
        sDob    = HelperFunctions::getRandomDOB();
        sDoj    = HelperFunctions::getRandomDOJFromDOB(sDob);
    } else {
        ManualInputs sIn = pReadManualInputs();
        sGender = sIn.mGender;
        sName   = sIn.mName;
        sDob    = sIn.mDob;
        sDoj    = sIn.mDoj;
    }

    EmployeeStatus sStatus = isRandomParm ? HelperFunctions::getRandomStatus() : Active;
    std::string sId  = EmployeeIDGenerator::generateID(typeParm, ++mEmployeeCounter);
    std::string sDol = (sStatus == Resigned)
                         ? HelperFunctions::computeDateOfLeaving(typeParm, sDoj)
                         : std::string("-");

    NewEmployeeArgs sArgs;
    sArgs.mName = sName;
    sArgs.mId = sId;
    sArgs.mGender = sGender;
    sArgs.mDob = sDob;
    sArgs.mDoj = sDoj;
    sArgs.mDol = sDol;
    sArgs.mType = typeParm;
    sArgs.mStatus = sStatus;

    if (sStatus != Resigned) {
        switch (typeParm) {
            case FullTime:
                sArgs.mLeaves = std::rand() % (MaxLeavesPerYear + 1);
                break;
            case Contractor:
                sArgs.mAgency = static_cast<Agency>(std::rand() % MaxAgencies);
                break;
            case Intern:
                sArgs.mCollege = static_cast<College>(std::rand() % MaxColleges);
                sArgs.mBranch  = static_cast<Branch>(std::rand() % MaxBranches);
                break;
        }
    }

    XyzEmployeeIF* sNewEmployee = EmployeeFactory::create(sArgs);

    if (sStatus == Resigned) {
        mResignedEmployees.push_back(sNewEmployee);
        std::cout << "\nCreated and archived a Resigned " << HelperFunctions::convertTypeToString(typeParm)
                  << ": " << sName << " (" << sId << ").\n";
    } else {
        mActiveInactiveEmployees.push_back(sNewEmployee);
        std::cout << "\nAdded new " << HelperFunctions::convertTypeToString(typeParm)
                  << ": " << sName << " (" << sId << ") with status: "
                  << HelperFunctions::convertStatusToString(sStatus) << ".\n";
    }
}

/**
 * @brief Removes an employee by ID.
 * @param idParm Employee ID to remove.
 * @return bool True if removed; otherwise false.
 */
bool XyzEmployeeManager::removeEmployee(const std::string& idParm)
{
    size_t sIndex = 0;
    XyzEmployeeBase* sEmp = pFindEmployeeAndIndex(idParm, mActiveInactiveEmployees, sIndex);
    if (!sEmp) return false;
    delete sEmp;
    mActiveInactiveEmployees.removeFrom(sIndex);
    return true;
}

/**
 * @brief Marks an employee as resigned and moves to archive.
 * @param idParm Employee ID to mark resigned.
 * @return void
 */
void XyzEmployeeManager::markEmployeeResigned(const std::string &idParm)
{
    size_t sIndex = 0;
    XyzEmployeeBase *sEmp = pFindEmployeeAndIndex(idParm, mActiveInactiveEmployees, sIndex);
    if (!sEmp)
    {
        std::cout << "\nError: Employee with ID " << idParm << " not found for resignation.\n";
        return;
    }

    NewEmployeeArgs sArgs;
    sArgs.mName   = sEmp->getName();
    sArgs.mId     = sEmp->getId();
    sArgs.mType   = sEmp->getType();
    sArgs.mGender = sEmp->getGender();
    sArgs.mDob    = sEmp->getDob();
    sArgs.mDoj    = sEmp->getDoj();
    sArgs.mDol    = HelperFunctions::computeDateOfLeaving(sEmp->getType(), sEmp->getDoj());
    sArgs.mStatus = Resigned;

    XyzEmployeeIF* sResigned = EmployeeFactory::create(sArgs);

    mActiveInactiveEmployees.removeFrom(sIndex);
    delete sEmp;
    mResignedEmployees.push_back(sResigned);

    std::cout << "\nSuccess: Employee " << idParm << " has been marked as RESIGNED.\n";
}

/**
 * @brief Converts an intern to a full-time employee.
 * @param idParm Intern's Employee ID.
 * @return void
 */
void XyzEmployeeManager::convertInternToFullTime(const std::string& idParm)
{
    size_t sIndex = 0;
    XyzEmployeeBase* sEmp = pFindEmployeeAndIndex(idParm, mActiveInactiveEmployees, sIndex);
    if (!sEmp || sEmp->getType() != Intern || sEmp->getStatus() == Resigned) {
        std::cout << "\nError: Employee ID " << idParm << " is not a valid, active Intern.\n";
        return;
    }

    NewEmployeeArgs sArgs;
    sArgs.mName = sEmp->getName();
    sArgs.mId = sEmp->getId();
    sArgs.mGender = sEmp->getGender();
    sArgs.mDob = sEmp->getDob();
    sArgs.mDoj = sEmp->getDoj();
    sArgs.mDol = "-";
    sArgs.mType = FullTime;
    sArgs.mStatus = Active;
    sArgs.mLeaves = 0;

    XyzEmployeeIF* sFullTime = EmployeeFactory::create(sArgs);
    mActiveInactiveEmployees[sIndex] = sFullTime;
    delete sEmp;

    std::cout << "\nSuccess: Intern " << sArgs.mId << " has been converted to a Full-Time employee.\n";
}

/**
 * @brief Adds leaves to all full-time employees.
 * @param leavesParm Number of leaves to add.
 * @return void
 */
void XyzEmployeeManager::addLeavesToAllFullTime(int leavesParm)
{
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
    {
        mActiveInactiveEmployees[sI]->addLeaves(leavesParm);
    }
    std::cout << "\nLeaves updated for all Full-Time employees.\n";
}

/**
 * @brief Searches for an employee by ID.
 * @param idParm Employee ID to search.
 * @return void
 */
void XyzEmployeeManager::searchById(const std::string &idParm)
{
    size_t sIndex = 0;
    XyzEmployeeBase *sEmp = pFindEmployeeAndIndex(idParm, mActiveInactiveEmployees, sIndex);
    if (sEmp)
    {
        std::cout << "\nFound employee in Active/Inactive list:\n";
        sEmp->printFullDetails();
        return;
    }

    sEmp = pFindEmployeeAndIndex(idParm, mResignedEmployees, sIndex);
    if (sEmp)
    {
        std::cout << "\nFound employee in Resigned archives:\n";
        sEmp->printFullDetails();
        return;
    }
    std::cout << "\nNo employee found with ID " << idParm << ".\n";
}

/**
 * @brief Searches for employees by name.
 * @param nameParm Name to search (case-sensitive).
 * @return void
 */
void XyzEmployeeManager::searchByName(const std::string &nameParm)
{
    int sFoundCount = 0;
    std::cout << "\n--- Searching for employees named: " << nameParm << " ---\n";

    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
    {
        if (mActiveInactiveEmployees[sI]->getName() == nameParm)
        {
            mActiveInactiveEmployees[sI]->printFullDetails();
            sFoundCount++;
        }
    }

    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
    {
        if (mResignedEmployees[sI]->getName() == nameParm)
        {
            mResignedEmployees[sI]->printFullDetails();
            sFoundCount++;
        }
    }

    if (sFoundCount == 0)
    {
        std::cout << "No employees found with that name.\n";
    }
}

/**
 * @brief Prints details of an employee by ID.
 * @param idParm Employee ID.
 * @return void
 */
void XyzEmployeeManager::printDetailsById(const std::string &idParm)
{
    searchById(idParm);
}

/**
 * @brief Prints summary of all employees.
 * @return void
 */
void XyzEmployeeManager::printSummaryAll()
{
    std::vector<EmployeeSummary> sRows;
    sRows.reserve(mActiveInactiveEmployees.size() + mResignedEmployees.size());
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI) {
        sRows.push_back(mActiveInactiveEmployees[sI]->toSummary());
    }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI) {
        sRows.push_back(mResignedEmployees[sI]->toSummary());
    }
    TablePrinter::print(sRows, "All Employees Summary");
}

/**
 * @brief Prints summary by employee type.
 * @param typeParm EmployeeType to filter.
 * @return void
 */
void XyzEmployeeManager::printSummaryByType(EmployeeType typeParm)
{
    std::vector<EmployeeSummary> sRows;
    sRows.reserve(mActiveInactiveEmployees.size() + mResignedEmployees.size());

    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI) {
        if (mActiveInactiveEmployees[sI]->getType() == typeParm) {
            sRows.push_back(mActiveInactiveEmployees[sI]->toSummary());
        }
    }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI) {
        if (mResignedEmployees[sI]->getType() == typeParm) {
            sRows.push_back(mResignedEmployees[sI]->toSummary());
        }
    }

    TablePrinter::print(sRows, "Summary for Type: " + HelperFunctions::convertTypeToString(typeParm));
}

void XyzEmployeeManager::printSummaryByStatus(EmployeeStatus statusParm)
{
    std::vector<EmployeeSummary> sRows;
    sRows.reserve(mActiveInactiveEmployees.size() + mResignedEmployees.size());

    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI) {
        if (mActiveInactiveEmployees[sI]->getStatus() == statusParm) {
            sRows.push_back(mActiveInactiveEmployees[sI]->toSummary());
        }
    }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI) {
        if (mResignedEmployees[sI]->getStatus() == statusParm) {
            sRows.push_back(mResignedEmployees[sI]->toSummary());
        }
    }

    TablePrinter::print(sRows, "Summary for Status: " + HelperFunctions::convertStatusToString(statusParm));
}

/**
 * @brief Prints summary by gender.
 * @param genderParm Gender string to filter.
 * @return void
 */
void XyzEmployeeManager::printSummaryByGender(const std::string &genderParm)
{
    std::vector<EmployeeSummary> sRows;
    sRows.reserve(mActiveInactiveEmployees.size() + mResignedEmployees.size());

    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI) {
        if (mActiveInactiveEmployees[sI]->getGender() == genderParm) {
            sRows.push_back(mActiveInactiveEmployees[sI]->toSummary());
        }
    }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI) {
        if (mResignedEmployees[sI]->getGender() == genderParm) {
            sRows.push_back(mResignedEmployees[sI]->toSummary());
        }
    }

    TablePrinter::print(sRows, "Summary for Gender: " + genderParm);
}

/**
 * @brief Finds an employee by ID and returns its index.
 * @param idParm Employee ID to search.
 * @param dequeParm Deque to search.
 * @param indexOutParm Output index if found.
 * @return XyzEmployeeBase* Pointer if found; nullptr otherwise.
 */
XyzEmployeeBase *XyzEmployeeManager::pFindEmployeeAndIndex(const std::string &idParm, Deque<XyzEmployeeIF *> &dequeParm, size_t &indexOutParm)
{
    for (size_t sI = 0; sI < dequeParm.size(); ++sI)
    {
        if (dequeParm[sI]->getId() == idParm)
        {
            indexOutParm = sI;
            return static_cast<XyzEmployeeBase *>(dequeParm[sI]);
        }
    }
    return nullptr;
}

/**
 * @brief Moves an employee to the resigned deque based on type and ID.
 * @param idParm Employee ID to move.
 * @param typeParm EmployeeType to match.
 * @return void
 */
void XyzEmployeeManager::moveEmployeeToResigned(const std::string &idParm, EmployeeType typeParm)
{
    size_t sIndex = 0;
    XyzEmployeeBase* sEmp = pFindEmployeeAndIndex(idParm, mActiveInactiveEmployees, sIndex);
    if (!sEmp || sEmp->getType() != typeParm) {
        std::cout << "\nError: Employee ID " << idParm << " not found for the specified type.\n";
        return;
    }

    NewEmployeeArgs sArgs;
    sArgs.mName = sEmp->getName();
    sArgs.mId = sEmp->getId();
    sArgs.mGender = sEmp->getGender();
    sArgs.mDob = sEmp->getDob();
    sArgs.mDoj = sEmp->getDoj();
    sArgs.mDol = HelperFunctions::computeDateOfLeaving(typeParm, sEmp->getDoj());
    sArgs.mType = sEmp->getType();
    sArgs.mStatus = Resigned;

    XyzEmployeeIF* sResigned = EmployeeFactory::create(sArgs);
    mResignedEmployees.push_back(sResigned);
    mActiveInactiveEmployees.removeFrom(sIndex);
    delete sEmp;

    std::cout << "\nEmployee " << idParm << " has been moved to resigned employees.\n";
}


/**
 * @brief Reads and validates manual inputs for a new employee.
 * @return ManualInputs Struct containing validated inputs.
 */
XyzEmployeeManager::ManualInputs XyzEmployeeManager::pReadManualInputs() const
{
    ManualInputs sIn;
    sIn.mGender = pReadGender();
    sIn.mName   = pReadName();
    sIn.mDob    = pReadDate("Enter Date of Birth (DD-MM-YYYY): ");
    while (true) {
        sIn.mDoj = pReadDate("Enter Date of Joining (DD-MM-YYYY): ");
        if (HelperFunctions::isAtLeastYearsApart(sIn.mDob, sIn.mDoj, 18)) break;
        std::cout << "Invalid DOJ. DOJ must be at least 18 years after DOB.\n";
    }
    return sIn;
}

/**
 * @brief Reads a valid gender input.
 * @return std::string Validated gender string.
 */
std::string XyzEmployeeManager::pReadGender() const
{
    while (true) {
        std::string sGender = HelperFunctions::normalizeGender(HelperFunctions::promptLine("Enter Gender (Male/Female): "));
        if (!sGender.empty()) return sGender;
        std::cout << "Invalid input. Please enter Male or Female.\n";
    }
}

/**
 * @brief Reads a non-empty name.
 * @return std::string Non-empty name string.
 */
std::string XyzEmployeeManager::pReadName() const
{
    while (true) {
        std::string sName = HelperFunctions::trim(HelperFunctions::promptLine("Enter Name: "));
        if (!sName.empty()) return sName;
        std::cout << "Name cannot be empty.\n";
    }
}

/**
 * @brief Reads a valid date string in DD-MM-YYYY format.
 * @param promptParm Prompt message for input.
 * @return std::string Validated date string.
 */
std::string XyzEmployeeManager::pReadDate(const std::string& promptParm) const
{
    while (true) {
        std::string sDate = HelperFunctions::trim(HelperFunctions::promptLine(promptParm));
        if (HelperFunctions::isValidDateString(sDate)) return sDate;
        std::cout << "Invalid date. Use DD-MM-YYYY and a valid calendar date.\n";
    }
}
