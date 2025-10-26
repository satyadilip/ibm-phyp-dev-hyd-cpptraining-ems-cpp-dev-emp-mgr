#include "XyzInternEmployee.h"
#include "HelperFunctions.h"
#include "EmployeeSummary.h"
#include <iostream>

/**
 * @class XyzInternEmployee
 * @brief Represents an intern employee.
 */

/**
 * @brief Constructs an intern with college and branch details.
 * @param nameParm Employee's full name.
 * @param idParm Unique employee identifier.
 * @param genderParm Employee gender string.
 * @param dobParm Date of birth in DD-MM-YYYY format.
 * @param dojParm Date of joining in DD-MM-YYYY format.
 * @param statusParm Current employment status.
 * @param collegeParm College enum value.
 * @param branchParm Branch enum value.
 * @param dolParm Date of leaving in DD-MM-YYYY format.
 * @return void
 */
XyzInternEmployee::XyzInternEmployee(const std::string& nameParm, const std::string& idParm,
                                     const std::string& genderParm, const std::string& dobParm,
                                     const std::string& dojParm, EmployeeStatus statusParm,
                                     College collegeParm, Branch branchParm, const std::string& dolParm)
    : XyzEmployeeBase(nameParm, idParm, genderParm, dobParm, dojParm, statusParm, Intern, dolParm),
      mCollege(collegeParm), mBranch(branchParm) {}

/**
 * @brief Returns the intern's college enum.
 * @return College College enum value.
 */
College XyzInternEmployee::getCollege() const {
    return mCollege;
}

/**
 * @brief Returns the intern's branch enum.
 * @return Branch Branch enum value.
 */
Branch XyzInternEmployee::getBranch() const {
    return mBranch;
}

/**
 * @brief Converts the intern's details to an EmployeeSummary object.
 * @return EmployeeSummary Struct containing summary information.
 */
EmployeeSummary XyzInternEmployee::toSummary() const
{
    EmployeeSummary sSummary;
    sSummary.name = getName();
    sSummary.id = getId();
    sSummary.gender = getGender();
    sSummary.type = HelperFunctions::convertTypeToString(getType());
    sSummary.status = HelperFunctions::convertStatusToString(getStatus());
    sSummary.dob = getDob();
    sSummary.doj = getDoj();
    sSummary.dol = (getStatus() == Resigned) ? getDol() : "-";
    sSummary.college = HelperFunctions::convertCollegeToString(mCollege);
    sSummary.branch = HelperFunctions::convertBranchToString(mBranch);
    return sSummary;
}

/**
 * @brief Prints a multi-line detailed description to stdout.
 * @return void
 */
void XyzInternEmployee::printFullDetails() const
{
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
              << "-------------------------------\n";
}