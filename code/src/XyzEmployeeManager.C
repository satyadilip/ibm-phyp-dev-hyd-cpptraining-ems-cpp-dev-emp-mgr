#include "XyzEmployeeManager.h"
#include "XyzEmployeeBase.h"
#include "XyzFullTimeEmployee.h"
#include "XyzContractorEmployee.h"
#include "XyzInternEmployee.h"
#include "XyzResignedEmployee.h"
#include "EmployeeIDGenerator.h"
#include "DateCalculator.h"
#include "HelperFunctions.h"
#include <iostream>
#include <cstdlib> //for rand()
#include <ctime>
#include <cctype>

/**
 * @brief Constructor: Initializes the employee manager and seeds the random number generator.
 */
XyzEmployeeManager::XyzEmployeeManager() : mEmployeeCounter(1)
{
    std::srand(static_cast<unsigned int>(std::time(0)));
}

/**
 * @brief Destructor: Cleans up all employee objects.
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
 */
void XyzEmployeeManager::start()
{
    pShowMainMenu();
}

/**
 * @brief Displays the main menu and handles user choices.
 */
void XyzEmployeeManager::pShowMainMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {"Add an Employee", "Remove an Employee", "Get Employee Details", "Others"};
        HelperFunctions::printMenu("Employee Management System", sOptions, MaxMainMenuOptions, ExitMainMenu);
        std::cout << "Your Choice: ";

        if (!(std::cin >> sChoice))
        {
            std::cout << "Invalid input. Please enter a number.\n";
            HelperFunctions::clearInputBuffer();
            sChoice = 0;
            continue;
        }

        switch (sChoice)
        {
        case AddEmployee:
            pShowAddEmployeeMenu();
            break;
        case RemoveEmployee:
            pShowRemoveEmployeeMenu();
            break;
        case GetEmployeeDetails:
            pShowEmployeeDetailsMenu();
            break;
        case DoSomethingElse:
            pShowOtherOperationsMenu();
            break;
        case ExitMainMenu:
            std::cout << "Exiting system. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (sChoice != ExitMainMenu);
}

/**
 * @brief Displays the add employee menu.
 */
void XyzEmployeeManager::pShowAddEmployeeMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {"Add an Employee at Random", "Add an Employee (F/C/I)"};
        HelperFunctions::printMenu("Add an Employee:", sOptions, MaxAddMenuOptions, BackToMainMenu);
        std::cout << "Your Choice: ";

        if (!(std::cin >> sChoice))
        {
            std::cout << "Invalid input. Please enter a number.\n";
            HelperFunctions::clearInputBuffer();
            sChoice = 0;
            continue;
        }

        switch (sChoice)
        {
        case AddRandomEmployee:
        {
            addEmployee(HelperFunctions::getRandomType(), true);
            break;
        }
        case AddSpecificEmployee:
        {
            pShowSpecificEmployeeMenu();
            break;
        }
        case BackToMainMenu:
        {
            break;
        }
        default:
        {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (sChoice != BackToMainMenu);
}

/**
 * @brief Displays the specific employee type menu.
 */
void XyzEmployeeManager::pShowSpecificEmployeeMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {"Add Full-Time Employee", "Add Contractor Employee", "Add Intern Employee"};
        HelperFunctions::printMenu("Add an Employee (F/C/I):", sOptions, 3, BackToAddMenu);
        std::cout << "Your Choice: ";

        if (!(std::cin >> sChoice))
        {
            std::cout << "Invalid input. Please enter a number.\n";
            HelperFunctions::clearInputBuffer();
            sChoice = 0;
            continue;
        }

        switch (sChoice)
        {
        case AddFullTimeEmployee:
        {
            addEmployee(FullTime, false);
            break;
        }
        case AddContractorEmployee:
        {
            addEmployee(Contractor, false);
            break;
        }
        case AddInternEmployee:
        {
            addEmployee(Intern, false);
            break;
        }
        case BackToAddMenu:
        {
            break;
        }
        default:
        {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (sChoice != BackToAddMenu);
}

/**
 * @brief Displays the search menu.
 */
void XyzEmployeeManager::pShowSearchMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {"Search by Employee ID", "Search by Employee Name"};
        HelperFunctions::printMenu("Search Employee", sOptions, MaxSearchMenuOptions, BackToMainMenuFromSearch);
        std::cout << "Your Choice: ";

        if (!(std::cin >> sChoice))
        {
            std::cout << "Invalid input. Please enter a number.\n";
            HelperFunctions::clearInputBuffer();
            sChoice = 0;
            continue;
        }

        std::string sId, sName;

        switch (sChoice)
        {
        case SearchById:
        {
            std::cout << "\nEnter Employee ID to search: ";
            std::cin >> sId;
            searchById(sId);
            break;
        }
        case SearchByName:
        {
            std::cout << "\nEnter Employee Name to search (case-sensitive): ";
            std::cin.ignore();
            std::getline(std::cin, sName);
            searchByName(sName);
            break;
        }
        case BackToMainMenuFromSearch:
        {
            break;
        }
        default:
        {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (sChoice != BackToMainMenuFromSearch);
}

/**
 * @brief Displays the employee details menu.
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
        HelperFunctions::printMenu("Get Employee Details:", sOptions, MaxDetailsMenuOptions, BackToMainMenuFromDetails);
        std::cout << "Your Choice: ";

        if (!(std::cin >> sChoice))
        {
            std::cout << "Invalid input. Please enter a number.\n";
            HelperFunctions::clearInputBuffer();
            sChoice = 0;
            continue;
        }

        switch (sChoice)
        {
        case AllEmployeesSummary:
        {
            printSummaryAll();
            break;
        }
        case SummaryByType:
        {
            printSummaryByType(FullTime);
            printSummaryByType(Contractor);
            printSummaryByType(Intern);
            break;
        }
        case SummaryByGender:
        {
            printSummaryByGender("Male");
            printSummaryByGender("Female");
            break;
        }
        case SummaryByStatus:
        {
            printSummaryByStatus(Active);
            printSummaryByStatus(Inactive);
            printSummaryByStatus(Resigned);
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
        {
            break;
        }
        default:
        {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (sChoice != BackToMainMenuFromDetails);
}

/**
 * @brief Displays the other operations menu.
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
        HelperFunctions::printMenu("Do something else:", sOptions, MaxOperationsMenuOptions, BackToMainMenuFromOperations);
        std::cout << "Your Choice: ";

        if (!(std::cin >> sChoice))
        {
            std::cout << "Invalid input. Please enter a number.\n";
            HelperFunctions::clearInputBuffer();
            sChoice = 0;
            continue;
        }

        std::string sId, sName;
        int sLeaves;

        switch (sChoice)
        {
        case AddLeavesToFullTime:
        {
            std::cout << "\nEnter number of leaves to add to all Full-Time employees: ";
            std::cin >> sLeaves;
            addLeavesToAllFullTime(sLeaves);
            break;
        }
        case ConvertInternToFullTime:
        {
            std::cout << "\nEnter Intern's Employee ID to convert: ";
            std::cin >> sId;
            convertInternToFullTime(sId);
            break;
        }
        case SearchEmployeeById:
        {
            std::cout << "\nEnter Employee ID to search: ";
            std::cin >> sId;
            searchById(sId);
            break;
        }
        case SearchEmployeeByName:
        {
            std::cout << "\nEnter Employee Name to search (case-sensitive): ";
            std::cin.ignore();
            std::getline(std::cin, sName);
            searchByName(sName);
            break;
        }
        case BackToMainMenuFromOperations:
        {
            break;
        }
        default:
        {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (sChoice != BackToMainMenuFromOperations);
}

/**
 * @brief Adds an employee of the given type.
 * @param typeParm EmployeeType to add.
 * @param isRandomParm If true, randomize all fields.
 */
void XyzEmployeeManager::addEmployee(EmployeeType typeParm, bool isRandomParm)
{
    std::string sGender = isRandomParm ? HelperFunctions::getRandomGender() : HelperFunctions::getInputGender();
    std::string sName = isRandomParm ? HelperFunctions::getRandomName(sGender) : HelperFunctions::getInputName();
    std::string sDob = isRandomParm ? HelperFunctions::getRandomDate() : HelperFunctions::getInputDate("Date of Birth");
    std::string sDoj = isRandomParm ? HelperFunctions::getRandomDate() : HelperFunctions::getInputDate("Date of Joining");
    EmployeeStatus sStatus = isRandomParm ? HelperFunctions::getRandomStatus() : Active;
    std::string sId = EmployeeIDGenerator::generateID(typeParm, mEmployeeCounter++);
    std::string sDol = HelperFunctions::computeDateOfLeaving(typeParm, sDoj);

    XyzEmployeeIF *sNewEmployee = nullptr;

    if (sStatus == Resigned)
    {
        sNewEmployee = new XyzResignedEmployee(sName, sId, typeParm, sGender, sDob, sDoj, sDol);
        mResignedEmployees.push_back(sNewEmployee);
        std::cout << "\nCreated and archived a Resigned " << HelperFunctions::convertTypeToString(typeParm) << ": " << sName << " (" << sId << ").\n";
    }
    else
    {
        switch (typeParm)
        {
        case FullTime:
        {
            int sLeaves = std::rand() % (MaxLeavesPerYear + 1);
            sNewEmployee = new XyzFullTimeEmployee(sName, sId, sGender, sDob, sDoj, sStatus, sLeaves);
            break;
        }
        case Contractor:
        {
            Agency sAgency = static_cast<Agency>(std::rand() % MaxAgencies);
            sNewEmployee = new XyzContractorEmployee(sName, sId, sGender, sDob, sDoj, sStatus, sAgency, sDol);
            break;
        }
        case Intern:
        {
            College sCollege = static_cast<College>(std::rand() % MaxColleges);
            Branch sBranch = static_cast<Branch>(std::rand() % MaxBranches);
            sNewEmployee = new XyzInternEmployee(sName, sId, sGender, sDob, sDoj, sStatus, sCollege, sBranch, sDol);
            break;
        }
        }
        mActiveInactiveEmployees.push_back(sNewEmployee);
        std::cout << "\nAdded new " << HelperFunctions::convertTypeToString(typeParm) << ": " << sName << " (" << sId << ") with status: " << HelperFunctions::convertStatusToString(sStatus) << ".\n";
    }
}

/**
 * @brief Removes an employee by ID.
 * @param idParm Employee ID to remove.
 * @return True if removed, false otherwise.
 */
bool XyzEmployeeManager::removeEmployee(const std::string &idParm)
{
    size_t sIndex = 0;
    XyzEmployeeBase *sEmp = pFindEmployeeAndIndex(idParm, mActiveInactiveEmployees, sIndex);
    if (sEmp)
    {
        mActiveInactiveEmployees.removeFrom(sIndex);
        delete sEmp;
        std::cout << "\nEmployee " << idParm << " permanently removed from active list.\n";
        return true;
    }

    sEmp = pFindEmployeeAndIndex(idParm, mResignedEmployees, sIndex);
    if (sEmp)
    {
        mResignedEmployees.removeFrom(sIndex);
        delete sEmp;
        std::cout << "\nEmployee " << idParm << " permanently removed from resigned list.\n";
        return true;
    }

    std::cout << "\nError: Employee with ID " << idParm << " not found for removal.\n";
    return false;
}

/**
 * @brief Marks an employee as resigned and moves to archive.
 * @param idParm Employee ID to mark resigned.
 */
void XyzEmployeeManager::markEmployeeResigned(const std::string &idParm)
{
    size_t sIndex = 0;
    XyzEmployeeBase *sBaseEmp = pFindEmployeeAndIndex(idParm, mActiveInactiveEmployees, sIndex);

    if (!sBaseEmp)
    {
        std::cout << "\nError: Employee ID " << idParm << " not found in active/inactive list.\n";
        return;
    }

    XyzResignedEmployee *sResignedRecord = new XyzResignedEmployee(
        sBaseEmp->getName(), sBaseEmp->getId(), sBaseEmp->getType(),
        sBaseEmp->getGender(), sBaseEmp->getDob(), sBaseEmp->getDoj(),
        HelperFunctions::getRandomDate());

    mActiveInactiveEmployees.removeFrom(sIndex);
    delete sBaseEmp;
    mResignedEmployees.push_back(sResignedRecord);

    std::cout << "\nSuccess: Employee " << idParm << " has been marked as RESIGNED and moved to archives.\n";
}

/**
 * @brief Converts an intern to a full-time employee.
 * @param idParm Intern's Employee ID.
 */
void XyzEmployeeManager::convertInternToFullTime(const std::string &idParm)
{
    size_t sIndex = 0;
    XyzEmployeeBase *sBaseEmp = pFindEmployeeAndIndex(idParm, mActiveInactiveEmployees, sIndex);

    if (!sBaseEmp || sBaseEmp->getType() != Intern)
    {
        std::cout << "\nError: Employee ID " << idParm << " is not a valid, active Intern.\n";
        return;
    }

    XyzInternEmployee *sIntern = static_cast<XyzInternEmployee *>(sBaseEmp);

    XyzFullTimeEmployee *sNewFullTime = new XyzFullTimeEmployee(
        sIntern->getName(), sIntern->getId(), sIntern->getGender(),
        sIntern->getDob(), sIntern->getDoj(), sIntern->getStatus(),
        DefaultLeavesForConversion);

    mActiveInactiveEmployees.removeFrom(sIndex);
    delete sIntern;
    mActiveInactiveEmployees.push_back(sNewFullTime);

    std::cout << "\nSuccess: Intern " << idParm << " has been converted to a Full-Time employee.\n";
}

/**
 * @brief Adds leaves to all full-time employees.
 * @param leavesParm Number of leaves to add.
 */
void XyzEmployeeManager::addLeavesToAllFullTime(int leavesParm)
{
    int sCount = 0;
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
    {
        XyzFullTimeEmployee *sFtEmp = dynamic_cast<XyzFullTimeEmployee *>(mActiveInactiveEmployees[sI]);
        if (sFtEmp)
        {
            sFtEmp->addLeaves(leavesParm);
            sCount++;
        }
    }
    std::cout << "\nAdded " << leavesParm << " leaves to " << sCount << " Full-Time employees.\n";
}

/**
 * @brief Searches for an employee by ID.
 * @param idParm Employee ID to search.
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
 */
void XyzEmployeeManager::printDetailsById(const std::string &idParm)
{
    searchById(idParm);
}

/**
 * @brief Prints summary of all employees.
 */
void XyzEmployeeManager::printSummaryAll()
{
    std::cout << "\n--- Summary of All Employees ---\n";
    if (mActiveInactiveEmployees.size() == 0 && mResignedEmployees.size() == 0)
    {
        std::cout << "No employees in the system.\n";
        return;
    }

    pPrintSummaryHeader();
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
    {
        mActiveInactiveEmployees[sI]->printSummary();
    }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
    {
        mResignedEmployees[sI]->printSummary();
    }
    std::cout << "+---------------------+-----------+--------------+-----------+-----------------+\n";
}

/**
 * @brief Prints summary by employee type.
 * @param typeParm EmployeeType to filter.
 */
void XyzEmployeeManager::printSummaryByType(EmployeeType typeParm)
{
    std::cout << "\n--- Summary for Type: " << HelperFunctions::convertTypeToString(typeParm) << " ---\n";
    int sCount = 0;

    pPrintSummaryHeader();
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
    {
        XyzEmployeeBase *sEmp = static_cast<XyzEmployeeBase *>(mActiveInactiveEmployees[sI]);
        if (sEmp->getType() == typeParm)
        {
            sEmp->printSummary();
            sCount++;
        }
    }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
    {
        XyzEmployeeBase *sEmp = static_cast<XyzEmployeeBase *>(mResignedEmployees[sI]);
        if (sEmp->getType() == typeParm)
        {
            sEmp->printSummary();
            sCount++;
        }
    }

    if (sCount > 0)
    {
        std::cout << "+---------------------+-----------+--------------+-----------+-----------------+\n";
    }
    else
    {
        std::cout << "No employees of this type found.\n";
    }
}

/**
 * @brief Prints summary by gender.
 * @param genderParm Gender string to filter.
 */
void XyzEmployeeManager::printSummaryByGender(const std::string &genderParm)
{
    std::cout << "\n--- Summary for Gender: " << genderParm << " ---\n";
    int sCount = 0;

    pPrintSummaryHeader();
    for (size_t sI = 0; sI < mActiveInactiveEmployees.size(); ++sI)
    {
        if (mActiveInactiveEmployees[sI]->getGender() == genderParm)
        {
            mActiveInactiveEmployees[sI]->printSummary();
            sCount++;
        }
    }
    for (size_t sI = 0; sI < mResignedEmployees.size(); ++sI)
    {
        if (mResignedEmployees[sI]->getGender() == genderParm)
        {
            mResignedEmployees[sI]->printSummary();
            sCount++;
        }
    }

    if (sCount > 0)
    {
        std::cout << "+---------------------+-----------+--------------+-----------+-----------------+\n";
    }
    else
    {
        std::cout << "No employees of this gender found.\n";
    }
}

/**
 * @brief Prints summary by status.
 * @param statusParm EmployeeStatus to filter.
 */
void XyzEmployeeManager::printSummaryByStatus(EmployeeStatus statusParm)
{
    std::cout << "\n--- Summary for Status: " << HelperFunctions::convertStatusToString(statusParm) << " ---\n";
    int sCount = 0;

    Deque<XyzEmployeeIF *> &sTargetDeque = (statusParm == Resigned) ? mResignedEmployees : mActiveInactiveEmployees;

    pPrintSummaryHeader();
    for (size_t sI = 0; sI < sTargetDeque.size(); ++sI)
    {
        XyzEmployeeBase *sEmp = static_cast<XyzEmployeeBase *>(sTargetDeque[sI]);
        if (sEmp->getStatus() == statusParm)
        {
            sEmp->printSummary();
            sCount++;
        }
    }

    if (sCount > 0)
    {
        std::cout << "+---------------------+-----------+--------------+-----------+-----------------+\n";
    }
    else
    {
        std::cout << "No employees with this status found.\n";
    }
}

/**
 * @brief Prints the summary table header.
 */
void XyzEmployeeManager::pPrintSummaryHeader() const
{
    std::cout << "+---------------------+-----------+--------------+-----------+-----------------+\n";
    std::cout << "| Name                | ID        | Type         | Status    | Details         |\n";
    std::cout << "+---------------------+-----------+--------------+-----------+-----------------+\n";
}

/**
 * @brief Finds an employee by ID and returns its index.
 * @param idParm Employee ID to search.
 * @param dequeParm Deque to search.
 * @param indexOutParm Output index if found.
 * @return Pointer to XyzEmployeeBase if found, nullptr otherwise.
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
 * @brief Displays the remove employee menu by type.
 */
void XyzEmployeeManager::pShowRemoveEmployeeMenu()
{
    int sChoice = 0;
    do
    {
        const char *sOptions[] = {"Remove Full-Time Employee", "Remove Contractor Employee", "Remove Intern Employee"};
        HelperFunctions::printMenu("Remove Employee:", sOptions, 3, BackToMainMenu);
        std::cout << "Your Choice: ";

        if (!(std::cin >> sChoice))
        {
            std::cout << "Invalid input. Please enter a number.\n";
            HelperFunctions::clearInputBuffer();
            sChoice = 0;
            continue;
        }

        std::string sId;
        switch (sChoice)
        {
        case FullTime:
        {
            std::cout << "\nEnter Full-Time Employee ID to remove: ";
            std::cin >> sId;
            moveEmployeeToResigned(sId, FullTime);
            break;
        }
        case Contractor:
        {
            std::cout << "\nEnter Contractor Employee ID to remove: ";
            std::cin >> sId;
            moveEmployeeToResigned(sId, Contractor);
            break;
        }
        case Intern:
        {
            std::cout << "\nEnter Intern Employee ID to remove: ";
            std::cin >> sId;
            moveEmployeeToResigned(sId, Intern);
            break;
        }
        case BackToMainMenu:
        {
            break;
        }
        default:
        {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (sChoice != BackToMainMenu);
}

/**
 * @brief Moves an employee to the resigned deque based on type and ID.
 * @param idParm Employee ID to move.
 * @param typeParm EmployeeType to match.
 */
void XyzEmployeeManager::moveEmployeeToResigned(const std::string &idParm, EmployeeType typeParm)
{
    size_t sIndex = 0;
    XyzEmployeeBase *sEmp = pFindEmployeeAndIndex(idParm, mActiveInactiveEmployees, sIndex);
    if (sEmp && sEmp->getType() == typeParm)
    {
        // Create a resigned employee object with minimal info
        XyzResignedEmployee *sResigned = new XyzResignedEmployee(
            sEmp->getName(),
            sEmp->getId(),
            sEmp->getType(),
            sEmp->getGender(),
            sEmp->getDob(),
            sEmp->getDoj(),
            HelperFunctions::computeDateOfLeaving(typeParm, sEmp->getDoj()));
        mResignedEmployees.push_back(sResigned);
        mActiveInactiveEmployees.removeFrom(sIndex);
        delete sEmp;
        std::cout << "\nEmployee " << idParm << " has been moved to resigned employees.\n";
    }
    else
    {
        std::cout << "\nError: Employee with ID " << idParm << " and type " << HelperFunctions::convertTypeToString(typeParm) << " not found in active/inactive list.\n";
    }
}
