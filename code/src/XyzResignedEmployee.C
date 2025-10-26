#include "XyzResignedEmployee.h"
#include "HelperFunctions.h"
#include "EmployeeSummary.h"
#include <iostream>

/**
 * @class XyzResignedEmployee
 * @brief Archived/resigned employee record.
 */

/**
 * @brief Constructs a resigned employee record with last known details.
 * @param nameParm Employee's full name.
 * @param idParm Unique employee identifier.
 * @param typeParm Employee type at time of resignation.
 * @param genderParm Employee gender string.
 * @param dobParm Date of birth in DD-MM-YYYY format.
 * @param dojParm Date of joining in DD-MM-YYYY format.
 * @param dolParm Date of leaving in DD-MM-YYYY format.
 * @return void
 */
XyzResignedEmployee::XyzResignedEmployee(const std::string& nameParm, const std::string& idParm,
                                         EmployeeType typeParm, const std::string& genderParm,
                                         const std::string& dobParm, const std::string& dojParm,
                                         const std::string& dolParm)
    : XyzEmployeeBase(nameParm, idParm, genderParm, dobParm, dojParm, Resigned, typeParm, dolParm) {}

/**
 * @brief Prints a multi-line detailed description to stdout.
 * @return void
 */
void XyzResignedEmployee::printFullDetails() const
{
    std::cout << "\n--- Archived Employee Details ---\n"
              << "  Employee Name  : " << getName() << "\n"
              << "  Employee ID    : " << getId() << "\n"
              << "  Last Known Type: " << HelperFunctions::convertTypeToString(getType()) << "\n"
              << "  Status         : " << "Resigned" << "\n"
              << "  Gender         : " << getGender() << "\n"
              << "  Date of Birth  : " << getDob() << "\n"
              << "  Date of Joining: " << getDoj() << "\n"
              << "  Date of Leaving: " << getDol() << "\n"
              << "-------------------------------\n";
}

EmployeeSummary XyzResignedEmployee::toSummary() const
{
    EmployeeSummary sSummary;
    sSummary.name = getName();
    sSummary.id = getId();
    sSummary.gender = getGender();
    sSummary.type = HelperFunctions::convertTypeToString(getType());
    sSummary.status = "Resigned";
    sSummary.dob = getDob();
    sSummary.doj = getDoj();
    sSummary.dol = getDol();
    return sSummary;
}