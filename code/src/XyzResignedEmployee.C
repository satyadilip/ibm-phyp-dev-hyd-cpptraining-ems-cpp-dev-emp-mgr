#include "XyzResignedEmployee.h"
#include "HelperFunctions.h"
#include <iostream>
#include <iomanip>

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
 * @param dobParm Date of birth in ISO format (YYYY-MM-DD).
 * @param dojParm Date of joining in ISO format (YYYY-MM-DD).
 * @param dolParm Date of leaving in ISO format (YYYY-MM-DD).
 * @return void
 */
XyzResignedEmployee::XyzResignedEmployee(const std::string& nameParm, const std::string& idParm,
                                         EmployeeType typeParm, const std::string& genderParm, 
                                         const std::string& dobParm, const std::string& dojParm, 
                                         const std::string& dolParm)
    : XyzEmployeeBase(nameParm, idParm, genderParm, dobParm, dojParm, Resigned, typeParm, dolParm) {}

/**
 * @brief Prints a one-line tabular summary to stdout.
 * @return void
 */
void XyzResignedEmployee::printSummary() const {
    std::cout << "| " << std::setw(20) << std::left << getName()
              << "| " << std::setw(10) << std::left << getId()
              << "| " << std::setw(12) << std::left << HelperFunctions::convertTypeToString(getType())
              << "| " << std::setw(10) << std::left << "Resigned"
              << "| " << std::setw(15) << std::left << ("DOL: " + getDol()) << "|\n";
}

/**
 * @brief Prints a multi-line detailed description to stdout.
 * @return void
 */
void XyzResignedEmployee::printFullDetails() const {
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