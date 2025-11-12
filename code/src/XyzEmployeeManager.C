#include "XyzEmployeeManager.h"
#include "XyzEmployeeBase.h"
#include "EmployeeIDGenerator.h"
#include "HelperFunctions.h"
#include "EmployeeFactory.h"
#include "PrintService.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>
#include <cctype>

/**
 * @brief Initializes manager state and RNG seed.
 */
XyzEmployeeManager::XyzEmployeeManager() : mEmployeeCounter(0) 
{
    // seed the random number generator to get different random values on every program run
    std::srand(static_cast<unsigned int>(std::time(0)));
}

/**
 * @brief Releases all allocated employee objects.
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
 * @brief Starts interactive main menu loop.
 */
void XyzEmployeeManager::start() 
{
    pShowMainMenu();
}

/**
 * @brief Displays main menu and dispatches user choices.
 */
void XyzEmployeeManager::pShowMainMenu() 
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = 
        {
            "Add an Employee",
            "Add 'n' Random Employees",
            "Remove an Employee",
            "Get Employee Details",
            "Others"
        };
        PrintService::printMenu("Employee Management System", sOptions, MaxMainMenuOptions, ExitMainMenu, RootMenuContext);
        std::cout << "Your Choice: ";
        sChoice = HelperFunctions::getMenuChoice(1, MaxMainMenuOptions, ExitMainMenu);
        switch (sChoice)
        {
        case AddEmployee:           pShowAddEmployeeMenu(); break;
        case AddMultipleEmployees:  {
                                        std::cout << "\nEnter how many random employees to create: ";
                                        int sInput;
                                        std::cin >> sInput;
                                        if (std::cin.fail()) {
                                            std::cin.clear();
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                            PrintService::printError("Invalid number.");
                                        } else {
                                            addMultipleRandomEmployees(sInput);
                                        }
                                        break;
                                    }
        case RemoveEmployee:        pShowRemoveEmployeeMenu(); break;
        case GetEmployeeDetails:    pShowEmployeeDetailsMenu(); break;
        case DoSomethingElse:       pShowOtherOperationsMenu(); break;
        case ExitMainMenu:          PrintService::printInfo("Exiting system. Goodbye!"); break;
        default:                    PrintService::printError("Invalid choice. Please try again."); break;
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
        PrintService::printMenu("Add an Employee:", sOptions, MaxAddMenuOptions, BackToMainMenu, SubMenuContext);
        std::cout << "Your Choice: ";
        sChoice = HelperFunctions::getMenuChoice(1, MaxAddMenuOptions, BackToMainMenu);
        switch (sChoice)
        {
        case AddRandomEmployee:    addEmployee(HelperFunctions::getRandomType(), true); break;
        case AddSpecificEmployee:  pShowSpecificEmployeeMenu(); break;
        case BackToMainMenu:       break;
        default:                   PrintService::printError("Invalid choice. Please try again."); break;
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
        PrintService::printMenu("Add an Employee (F/C/I):", sOptions, SpecificEmployeeMenuCount, BackToAddMenu, SubMenuContext);
        std::cout << "Your Choice: ";
        sChoice = HelperFunctions::getMenuChoice(1, SpecificEmployeeMenuCount, BackToAddMenu);

        switch (sChoice)
        {
        case AddFullTimeEmployee:     addEmployee(FullTime, false); break;
        case AddContractorEmployee:   addEmployee(Contractor, false); break;
        case AddInternEmployee:       addEmployee(Intern, false); break;
        case BackToAddMenu:           break;
        default:                      PrintService::printError("Invalid choice. Please try again."); break;
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
        PrintService::printMenu("Search Employee", sOptions, MaxSearchMenuOptions, BackToMainMenuFromSearch, SubMenuContext);
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
            PrintService::printError("Invalid choice. Please try again.");
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
        PrintService::printMenu("Get Employee Details:", sOptions, MaxDetailsMenuOptions, BackToMainMenuFromDetails, SubMenuContext);
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
                PrintService::printMenu("Select Employee Type:", sSubOptions, TypeSubmenuCount, BackToMainMenuFromDetails, SubMenuContext);
                std::cout << "Your Choice: ";
                sSubChoice = HelperFunctions::getMenuChoice(1, TypeSubmenuCount, BackToMainMenuFromDetails);
                if (sSubChoice == BackToMainMenuFromDetails) break;

                switch (static_cast<TypeSubmenu>(sSubChoice))
                {
                    case TypeFT:          printSummaryByType(FullTime); break;
                    case TypeContractor:  printSummaryByType(Contractor); break;
                    case TypeIntern:      printSummaryByType(Intern); break;
                    default:              PrintService::printError("Invalid choice. Please try again."); continue;
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
                PrintService::printMenu("Select Gender:", sSubOptions, GenderSubmenuCount, BackToMainMenuFromDetails, SubMenuContext);
                std::cout << "Your Choice: ";
                sSubChoice = HelperFunctions::getMenuChoice(1, GenderSubmenuCount, BackToMainMenuFromDetails);
                if (sSubChoice == BackToMainMenuFromDetails) break;

                switch (static_cast<GenderSubmenu>(sSubChoice))
                {
                    case GenderMale:    printSummaryByGender("Male"); break;
                    case GenderFemale:  printSummaryByGender("Female"); break;
                    default:            PrintService::printError("Invalid choice. Please try again."); continue;
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
                PrintService::printMenu("Select Employment Status:", sSubOptions, StatusSubmenuCount, BackToMainMenuFromDetails, SubMenuContext);
                std::cout << "Your Choice: ";
                sSubChoice = HelperFunctions::getMenuChoice(1, StatusSubmenuCount, BackToMainMenuFromDetails);
                if (sSubChoice == BackToMainMenuFromDetails) break;

                switch (static_cast<StatusSubmenu>(sSubChoice))
                {
                    case StatusActive:    printSummaryByStatus(Active); break;
                    case StatusInactive:  printSummaryByStatus(Inactive); break;
                    case StatusResigned:  printSummaryByStatus(Resigned); break;
                    default:              PrintService::printError("Invalid choice. Please try again."); continue;
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
            PrintService::printError("Invalid choice. Please try again.");
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
            "Convert a Contractor to Full-Time employee.",
            "Search an Employee by ID",
            "Search an Employee by Name"
        };
        PrintService::printMenu("Do something else:", sOptions, MaxOperationsMenuOptions, BackToMainMenuFromOperations, SubMenuContext);
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
                PrintService::printError("Invalid number.");
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
        case ConvertContractorToFullTime:
            std::cout << "\nEnter Contractor's Employee ID to convert: ";
            std::cin >> sId;
            convertContractorToFullTime(sId);
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
            PrintService::printError("Invalid choice. Please try again.");
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
        PrintService::printMenu("Remove Employee:", sOptions, RemoveMenuCount, BackToMainMenu, SubMenuContext);
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
            PrintService::printError("Invalid choice. Please try again.");
            break;
        }
    } while (sChoice != BackToMainMenu);
}

/**
 * @brief Adds employee either random or via validated manual input.
 * @param typeParm Target employee type.
 * @param isRandomParm If true randomizes fields.
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
        PrintService::printInfo("\nAdded new " + HelperFunctions::convertTypeToString(typeParm) +
                            ": " + sName + " (" + sId + ") with status: " +
                            HelperFunctions::convertStatusToString(sStatus) + ".");
    }
}

/**
 * @brief Bulk creation of random employees.
 * @param countParm Number to create (1..10000).
 */
void XyzEmployeeManager::addMultipleRandomEmployees(int countParm)
{
    if (countParm <= 0) {
        PrintService::printError("Count must be > 0.");
        return;
    }
    if (countParm > 10000) {
        PrintService::printError("Count too large (max 10000).");
        return;
    }
    for (int i = 0; i < countParm; ++i) {
        addEmployee(HelperFunctions::getRandomType(), true);
    }
    PrintService::printInfo("Created " + std::to_string(countParm) + " random employees.");
}

/**
 * @brief Moves active/inactive employee to resigned deque.
 * @param idParm Employee ID.
 * @param typeParm Original type (for logging).
 */
void XyzEmployeeManager::moveEmployeeToResigned(const std::string& idParm, EmployeeType typeParm)
{
    for (size_t i = 0; i < mActiveInactiveEmployees.size(); ++i)
    {
        if (mActiveInactiveEmployees[i]->getId() == idParm)
        {
            mResignedEmployees.push_back(mActiveInactiveEmployees[i]);
            PrintService::printInfo("Employee " + mActiveInactiveEmployees[i]->getName() + " (" + idParm + ") has been resigned.");
            mActiveInactiveEmployees.removeFrom(i);
            return;
        }
    }
    PrintService::printError("Employee ID " + idParm + " not found in active/inactive employees.");
}

/**
 * @brief Converts an intern employee to full-time status.
 * @param idParm Employee ID of the intern.
 * @return void
 */
void XyzEmployeeManager::convertInternToFullTime(const std::string& idParm)
{
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
    {
        if (mActiveInactiveEmployees[sI]->getId() == idParm &&
            mActiveInactiveEmployees[sI]->getType() == Intern)
        {
            EmployeeStatus sStatus = mActiveInactiveEmployees[sI]->getStatus();
            EmployeeType sType = FullTime;

            // create new full-time employee data
            NewEmployeeArgs sArgs;
            sArgs.mName = mActiveInactiveEmployees[sI]->getName();
            sArgs.mId = idParm;
            sArgs.mGender = mActiveInactiveEmployees[sI]->getGender();
            sArgs.mDob = mActiveInactiveEmployees[sI]->getDob();
            sArgs.mDoj = HelperFunctions::getCurrentDate();
            sArgs.mDol = HelperFunctions::computeDateOfLeaving(sType, sArgs.mDoj);
            sArgs.mType = sType;
            sArgs.mStatus = sStatus;
            sArgs.mLeaves = std::rand() % (MaxLeavesPerYear + 1);

            // remove from intern and add as full-time
            delete mActiveInactiveEmployees[sI];
            mActiveInactiveEmployees[sI] = EmployeeFactory::create(sArgs);
            PrintService::printInfo("Intern " + sArgs.mName + " (" + idParm + ") has been converted to Full-Time.");
            return;
        }
    }
    PrintService::printError("Intern ID " + idParm + " not found.");
}

/**
 * @brief Converts a contractor employee to full-time status.
 * @param idParm Employee ID of the contractor.
 * @return void
 */
void XyzEmployeeManager::convertContractorToFullTime(const std::string& idParm)
{
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
    {
        if (mActiveInactiveEmployees[sI]->getId() == idParm &&
            mActiveInactiveEmployees[sI]->getType() == Contractor)
        {
            if (mActiveInactiveEmployees[sI]->getStatus() == Resigned) {
                PrintService::printError("Contractor ID " + idParm + " is resigned; cannot convert.");
                return;
            }

            EmployeeStatus sStatus = mActiveInactiveEmployees[sI]->getStatus();
            NewEmployeeArgs sArgs;
            sArgs.mName   = mActiveInactiveEmployees[sI]->getName();
            sArgs.mId     = idParm;
            sArgs.mGender = mActiveInactiveEmployees[sI]->getGender();
            sArgs.mDob    = mActiveInactiveEmployees[sI]->getDob();
            sArgs.mDoj    = HelperFunctions::getCurrentDate();
            sArgs.mDol    = HelperFunctions::computeDateOfLeaving(FullTime, sArgs.mDoj);
            sArgs.mType   = FullTime;
            sArgs.mStatus = sStatus;
            sArgs.mLeaves = std::rand() % (MaxLeavesPerYear + 1);

            delete mActiveInactiveEmployees[sI];
            mActiveInactiveEmployees[sI] = EmployeeFactory::create(sArgs);

            PrintService::printInfo("Contractor " + sArgs.mName + " (" + idParm + ") has been converted to Full-Time.");
            return;
        }
    }
    PrintService::printError("Contractor ID " + idParm + " not found.");
}

/**
 * @brief Searches employee(s) by ID and prints details.
 * @param idParm Employee ID to locate.
 */
void XyzEmployeeManager::searchById(const std::string& idParm)
{
    bool sFound = false;
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
        if (mActiveInactiveEmployees[sI]->getId() == idParm) { mActiveInactiveEmployees[sI]->printFullDetails(); sFound = true; }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
        if (mResignedEmployees[sI]->getId() == idParm) { mResignedEmployees[sI]->printFullDetails(); sFound = true; }
    if (!sFound) PrintService::printError("Employee ID " + idParm + " not found.");
}

/**
 * @brief Searches employee(s) by exact name and prints details.
 * @param nameParm Name to match (case-sensitive).
 */
void XyzEmployeeManager::searchByName(const std::string& nameParm)
{
    bool sFound = false;
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
        if (mActiveInactiveEmployees[sI]->getName() == nameParm) { mActiveInactiveEmployees[sI]->printFullDetails(); sFound = true; }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
        if (mResignedEmployees[sI]->getName() == nameParm) { mResignedEmployees[sI]->printFullDetails(); sFound = true; }
    if (!sFound) PrintService::printError("Employee Name \"" + nameParm + "\" not found.");
}

/**
 * @brief Prints full details for a specific employee ID.
 * @param idParm Employee ID.
 */
void XyzEmployeeManager::printDetailsById(const std::string& idParm)
{
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
        if (mActiveInactiveEmployees[sI]->getId() == idParm) { mActiveInactiveEmployees[sI]->printFullDetails(); return; }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
        if (mResignedEmployees[sI]->getId() == idParm) { mResignedEmployees[sI]->printFullDetails(); return; }
    PrintService::printError("Employee ID " + idParm + " not found.");
}

/**
 * @brief Prints summary table of all employees.
 */
void XyzEmployeeManager::printSummaryAll()
{
    std::vector<EmployeeSummary> sRows;
    sRows.reserve(mActiveInactiveEmployees.size() + mResignedEmployees.size());
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
        sRows.push_back(mActiveInactiveEmployees[sI]->toSummary());
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
        sRows.push_back(mResignedEmployees[sI]->toSummary());
    PrintService::printEmployeeSummaryTable(sRows, "All Employees Summary");
}

/**
 * @brief Prints summary filtered by employee type.
 * @param typeParm Type to match.
 */
void XyzEmployeeManager::printSummaryByType(EmployeeType typeParm)
{
    std::vector<EmployeeSummary> sRows;
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
        if (mActiveInactiveEmployees[sI]->getType() == typeParm)
            sRows.push_back(mActiveInactiveEmployees[sI]->toSummary());
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
        if (mResignedEmployees[sI]->getType() == typeParm)
            sRows.push_back(mResignedEmployees[sI]->toSummary());
    PrintService::printEmployeeSummaryTable(sRows, "Summary for Type: " + HelperFunctions::convertTypeToString(typeParm));
}

/**
 * @brief Prints summary filtered by status (Active/Inactive/Resigned).
 * @param statusParm Status to match.
 */
void XyzEmployeeManager::printSummaryByStatus(EmployeeStatus statusParm)
{
    std::vector<EmployeeSummary> sRows;
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
        if (mActiveInactiveEmployees[sI]->getStatus() == statusParm)
            sRows.push_back(mActiveInactiveEmployees[sI]->toSummary());
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
        if (mResignedEmployees[sI]->getStatus() == statusParm)
            sRows.push_back(mResignedEmployees[sI]->toSummary());
    PrintService::printEmployeeSummaryTable(sRows, "Summary for Status: " + HelperFunctions::convertStatusToString(statusParm));
}

/**
 * @brief Prints summary filtered by gender.
 * @param genderParm "Male"/"Female".
 */
void XyzEmployeeManager::printSummaryByGender(const std::string& genderParm)
{
    std::vector<EmployeeSummary> sRows;
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
        if (mActiveInactiveEmployees[sI]->getGender() == genderParm)
            sRows.push_back(mActiveInactiveEmployees[sI]->toSummary());
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
        if (mResignedEmployees[sI]->getGender() == genderParm)
            sRows.push_back(mResignedEmployees[sI]->toSummary());
    PrintService::printEmployeeSummaryTable(sRows, "Summary for Gender: " + genderParm);
}

/**
 * @brief Reads and validates gender input (M/F).
 * @return Canonical gender string.
 */
std::string XyzEmployeeManager::pReadGender() const
{
    while (true)
    {
        std::cout << "Enter Gender (M/F): ";
        std::string sInput;
        std::cin >> sInput;
        if (sInput.size() == 1)
        {
            char c = std::toupper(sInput[0]);
            if (c == 'M') return "Male";
            if (c == 'F') return "Female";
        }
        PrintService::printError("Invalid gender. Please enter M or F.");
    }
}

/**
 * @brief Reads and validates non-empty name line.
 * @return Name string.
 */
std::string XyzEmployeeManager::pReadName() const
{
    std::cout << "Enter Name: ";
    std::string sName;
    std::getline(std::cin >> std::ws, sName);
    if (sName.empty()) {
        PrintService::printError("Name cannot be empty.");
        return pReadName();
    }
    return sName;
}

/**
 * @brief Reads a date (DOB/DOJ) ensuring valid format.
 * @param isDOB True if reading DOB, false for DOJ.
 * @return Date string DD-MM-YYYY.
 */
std::string XyzEmployeeManager::pReadDate(bool isDOB) const
{
    while (true)
    {
        std::cout << "Enter " << (isDOB ? "Date of Birth" : "Date of Joining") << " (DD-MM-YYYY): ";
        std::string sDate;
        std::cin >> sDate;
        if (HelperFunctions::isValidDateString(sDate)) return sDate;
        PrintService::printError("Invalid date format. Please use DD-MM-YYYY.");
    }
}

/**
 * @brief Gathers manual employee inputs enforcing age rule (DOJ >= DOB + 18y).
 * @return ManualInputs Collected values.
 */
XyzEmployeeManager::ManualInputs XyzEmployeeManager::pReadManualInputs()
{
    XyzEmployeeManager::ManualInputs sIn;
    sIn.mGender = pReadGender();
    sIn.mName   = pReadName();
    sIn.mDob    = pReadDate(true);

    // Enforce DOJ >= DOB + 18 years
    while (true) {
        sIn.mDoj = pReadDate(false);
        if (HelperFunctions::isAtLeastYearsApart(sIn.mDob, sIn.mDoj, 18)) {
            break;
        }
        PrintService::printError("Date of Joining must be at least 18 years after Date of Birth. Please re-enter DOJ.");
    }
    return sIn;
}

/**
 * @brief Adds specified leaves to all full-time employees.
 * @param leavesParm Number of leaves to add.
 */
void XyzEmployeeManager::addLeavesToAllFullTime(int leavesParm)
{
    if (leavesParm <= 0) {
        PrintService::printError("Leaves to add must be > 0.");
        return;
    }

    int sUpdated = 0;
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
    {
        if (mActiveInactiveEmployees[sI]->getType() == FullTime) {
            mActiveInactiveEmployees[sI]->addLeaves(leavesParm);
            ++sUpdated;
        }
    }

    if (sUpdated == 0) {
        PrintService::printInfo("No full-time employees to update.");
    } else {
        PrintService::printInfo("Added " + std::to_string(leavesParm) +
                                " leaves to " + std::to_string(sUpdated) +
                                " full-time employee(s).");
    }
}


