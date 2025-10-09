#ifndef XYZ_INTERN_EMPLOYEE_H
#define XYZ_INTERN_EMPLOYEE_H

#include "XyzEmployeeBase.h"
#include "HelperFunctions.h"
#include <iostream>
#include <iomanip>

/**
 * @class XyzInternEmployee
 * @brief Represents an intern, inheriting from XyzEmployeeBase.
 * It includes intern-specific properties like college and branch.
 */
class XyzInternEmployee : public XyzEmployeeBase {
private:
    College mCollege;
    Branch mBranch;

public:
    /**
     * @brief Construct a new XyzInternEmployee object.
     */
    XyzInternEmployee(const std::string& nameParm, const std::string& idParm,
                      const std::string& genderParm, const std::string& dobParm,
                      const std::string& dojParm, EmployeeStatus statusParm,
                      College collegeParm, Branch branchParm, const std::string& dolParm)
        : XyzEmployeeBase(nameParm, idParm, genderParm, dobParm, dojParm, statusParm, Intern, dolParm),
          mCollege(collegeParm), mBranch(branchParm) {}

    /**
     * @brief Returns the intern's college.
     * @return College enum value.
     */
    College getCollege() const { return mCollege; }

    /**
     * @brief Returns the intern's branch.
     * @return Branch enum value.
     */
    Branch getBranch() const { return mBranch; }
    
    /**
     * @brief Prints a compact, single-line summary of the employee for tables.
     */
    void printSummary() const override {
        std::cout << "| " << std::setw(20) << std::left << getName()
                  << "| " << std::setw(10) << std::left << getId()
                  << "| " << std::setw(12) << std::left << "Intern"
                  << "| " << std::setw(10) << std::left << HelperFunctions::convertStatusToString(getStatus())
                  << "| " << std::setw(15) << std::left << HelperFunctions::convertCollegeToString(mCollege) << "|\n";
    }

    /**
     * @brief Prints a detailed, multi-line view of the employee, matching assignment format.
     */
    void printFullDetails() const override {
        std::cout << "\n--- Employee Details ---\n"
                  << "  Employee Name  : " << getName() << "\n"
                  << "  Employee ID    : " << getId() << "\n"
                  << "  Employee Type  : " << "Intern" << "\n"
                  << "  Employee Status: " << HelperFunctions::convertStatusToString(getStatus()) << "\n"
                  << "  Gender         : " << getGender() << "\n"
                  << "  Date of Birth  : " << getDob() << "\n"
                  << "  Date of Joining: " << getDoj() << "\n"
                  << "  Date of Leaving: " << getDol() << "\n"
                  << "  College        : " << HelperFunctions::convertCollegeToString(mCollege) << "\n"
                  << "  Branch         : " << HelperFunctions::convertBranchToString(mBranch) << "\n"
                  << "------------------------\n";
    }
};

#endif // XYZ_INTERN_EMPLOYEE_H
