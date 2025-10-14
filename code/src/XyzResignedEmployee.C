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
void XyzResignedEmployee::printSummary() const
{
    using std::left;
    using std::setw;

    const int wName = WName, wId = WId, wGender = WGender, wType = WType, wStatus = WStatus;
    const int wDob = WDob, wDoj = WDoj, wDol = WDol, wTotLeaves = WTotLeaves, wAvailed = WAvailed, wAgency = WAgency, wCollege = WCollege, wBranch = WBranch;

    std::cout << "|"
              << left << setw(wName)    << getName()                                       << "|"
              << left << setw(wId)      << getId()                                         << "|"
              << left << setw(wGender)  << getGender()                                     << "|"
              << left << setw(wType)    << HelperFunctions::convertTypeToString(getType()) << "|"
              << left << setw(wStatus)  << HelperFunctions::convertStatusToString(getStatus()) << "|"
              << left << setw(wDob)     << getDob()                                        << "|"
              << left << setw(wDoj)     << getDoj()                                        << "|"
              << left << setw(wDol)     << getDol()                                        << "|"
              << left << setw(wTotLeaves)<< "-"                                            << "|"
              << left << setw(wAvailed) << "-"                                             << "|"
              << left << setw(wAgency)  << "-"                                             << "|"
              << left << setw(wCollege) << "-"                                             << "|"
              << left << setw(wBranch)  << "-"                                             << "|\n";
}

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