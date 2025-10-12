#include "XyzInternEmployee.h"
#include "HelperFunctions.h"
#include <iostream>
#include <iomanip>

/**
 * @class XyzInternEmployee
 * @brief Represents an intern employee.
 */

/**
 * @brief Constructs an intern with college and branch details.
 * @param nameParm Employee's full name.
 * @param idParm Unique employee identifier.
 * @param genderParm Employee gender string.
 * @param dobParm Date of birth in ISO format (YYYY-MM-DD).
 * @param dojParm Date of joining in ISO format (YYYY-MM-DD).
 * @param statusParm Current employment status.
 * @param collegeParm College enum value.
 * @param branchParm Branch enum value.
 * @param dolParm Date of leaving in ISO format (YYYY-MM-DD).
 * @return void
 */
XyzInternEmployee::XyzInternEmployee(const std::string& nameParm, const std::string& idParm,
                                     const std::string& genderParm, const std::string& dobParm,
                                     const std::string& dojParm, EmployeeStatus statusParm,
                                     College collegeParm, Branch branchParm, const std::string& dolParm)
    : XyzEmployeeBase(nameParm, idParm, genderParm, dobParm, dojParm, statusParm, Intern, dolParm),
      mCollege(collegeParm), mBranch(branchParm) {}

/**
 * @brief Returns the intern's college.
 * @return College College enum value.
 */
College XyzInternEmployee::getCollege() const {
    return mCollege;
}

/**
 * @brief Returns the intern's branch.
 * @return Branch Branch enum value.
 */
Branch XyzInternEmployee::getBranch() const {
    return mBranch;
}

/**
 * @brief Prints a one-line tabular summary to stdout.
 * @return void
 */
void XyzInternEmployee::printSummary() const {
    std::cout << "| " << std::setw(20) << std::left << getName()
              << "| " << std::setw(10) << std::left << getId()
              << "| " << std::setw(12) << std::left << "Intern"
              << "| " << std::setw(10) << std::left << HelperFunctions::convertStatusToString(getStatus())
              << "| " << std::setw(15) << std::left << HelperFunctions::convertCollegeToString(mCollege) << "|\n";
}

/**
 * @brief Prints a multi-line detailed description to stdout.
 * @return void
 */
void XyzInternEmployee::printFullDetails() const {
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