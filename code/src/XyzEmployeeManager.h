#ifndef XYZ_EMPLOYEE_MANAGER_H
#define XYZ_EMPLOYEE_MANAGER_H

#include "Deque.h"
#include "XyzEmployeeIF.h"
#include "Enums.h"
#include <string>
#include <cstddef>

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

    /**
     * Holds validated manual inputs when adding an employee.
     */
    struct ManualInputs {
        std::string mGender;
        std::string mName;
        std::string mDob;
        std::string mDoj;
    };

    // --- Private Menu Functions ---
    void pShowMainMenu();
    void pShowAddEmployeeMenu();
    void pShowSpecificEmployeeMenu();
    void pShowEmployeeDetailsMenu();
    void pShowOtherOperationsMenu();
    void pShowSearchMenu();
    void pShowRemoveEmployeeMenu();

    // Helpers (retained)
    XyzEmployeeBase* pFindEmployeeAndIndex(const std::string& idParm,
                                           Deque<XyzEmployeeIF*>& dequeParm,
                                           size_t& indexOutParm);
    ManualInputs pReadManualInputs();
    std::string pReadGender() const;
    std::string pReadName() const;
    std::string pReadDate(bool isDOB) const; 

public:
    XyzEmployeeManager();
    ~XyzEmployeeManager();
    void start();

    // --- Core Employee Management Operations ---
    void addEmployee(EmployeeType typeParm, bool isRandomParm);
    void addMultipleRandomEmployees(int countParm);
    bool removeEmployee(const std::string& idParm);
    void convertInternToFullTime(const std::string& idParm);
    void convertContractorToFullTime(const std::string& idParm);
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

