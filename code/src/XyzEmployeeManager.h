#ifndef XYZ_EMPLOYEE_MANAGER_H
#define XYZ_EMPLOYEE_MANAGER_H

#include "Deque.h"
#include "XyzEmployeeIF.h"
#include "Enums.h"
#include <string>
#include <cstddef>

// Forward declaration to resolve the "unknown type name" compilation error.
class XyzEmployeeBase;

/**
 * @class XyzEmployeeManager
 * @brief The main controller class for managing all employee-related operations.
 *
 * This class handles the user interface, employee creation, storage, modification,
 * and reporting. It uses two separate Deque instances to manage active/inactive
 * and resigned employees as required.
 */
class XyzEmployeeManager {
private:
    Deque<XyzEmployeeIF*> mActiveInactiveEmployees;
    Deque<XyzEmployeeIF*> mResignedEmployees;
    int mEmployeeCounter;

    // --- Private Menu Functions ---
    void pShowMainMenu();
    void pShowAddEmployeeMenu();
    void pShowSpecificEmployeeMenu();
    void pShowEmployeeDetailsMenu(); 
    void pShowOtherOperationsMenu();
    void pShowSearchMenu(); 
    void pShowRemoveEmployeeMenu();
    
    // --- Private Helper Functions for Random Data Generation ---
    std::string pGetRandomName();
    std::string pGetRandomGender();
    std::string pGetRandomDate();
    EmployeeStatus pGetRandomStatus();
    EmployeeType pGetRandomType();
    
    // --- Private Logic and Utility Functions ---
    std::string pComputeDateOfLeaving(EmployeeType typeParm, const std::string& dojParm);
    void pPrintSummaryHeader() const;
    XyzEmployeeBase* pFindEmployeeAndIndex(const std::string& idParm, Deque<XyzEmployeeIF*>& dequeParm, size_t& indexOutParm);

public:
    /**
     * @brief Construct a new XyzEmployeeManager object.
     */
    XyzEmployeeManager();

    /**
     * @brief Destroy the XyzEmployeeManager object and deallocate all employee memory.
     */
    ~XyzEmployeeManager();

    /**
     * @brief Starts the main application loop for the menu-driven interface.
     */
    void start();
    
    // --- Core Employee Management Operations ---
    void addEmployee(EmployeeType typeParm, bool isRandomParm);
    bool removeEmployee(const std::string& idParm);
    void convertInternToFullTime(const std::string& idParm);
    void addLeavesToAllFullTime(int leavesParm);
    void searchById(const std::string& idParm);
    void searchByName(const std::string& nameParm);
    void markEmployeeResigned(const std::string& idParm);
    void moveEmployeeToResigned(const std::string &idParm, EmployeeType typeParm);
    
    // --- Reporting and Display Functions ---
    void printSummaryAll();
    void printSummaryByGender(const std::string& genderParm);
    void printSummaryByType(EmployeeType typeParm);
    void printSummaryByStatus(EmployeeStatus statusParm);
    void printDetailsById(const std::string& idParm);
};

#endif // XYZ_EMPLOYEE_MANAGER_H

