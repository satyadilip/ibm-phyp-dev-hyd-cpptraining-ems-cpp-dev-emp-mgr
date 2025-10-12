#include "XyzContractorEmployee.h"
#include "HelperFunctions.h"
#include <iostream>
#include <iomanip>

/**
 * @class XyzContractorEmployee
 * @brief Represents a contractor employee.
 */

/**
 * @brief Constructs a contractor with external agency details.
 * @param nameParm Employee's full name.
 * @param idParm Unique employee identifier.
 * @param genderParm Employee gender string.
 * @param dobParm Date of birth in ISO format (YYYY-MM-DD).
 * @param dojParm Date of joining in ISO format (YYYY-MM-DD).
 * @param statusParm Current employment status.
 * @param agencyParm Contracting agency enum value.
 * @param dolParm Date of leaving in ISO format (YYYY-MM-DD).
 * @return void
 */
XyzContractorEmployee::XyzContractorEmployee(const std::string& nameParm, const std::string& idParm,
                                             const std::string& genderParm, const std::string& dobParm,
                                             const std::string& dojParm, EmployeeStatus statusParm,
                                             Agency agencyParm, const std::string& dolParm)
    : XyzEmployeeBase(nameParm, idParm, genderParm, dobParm, dojParm, statusParm, Contractor, dolParm),
      mAgency(agencyParm) {}

/**
 * @brief Returns the contractor's agency.
 * @return Agency Agency enum value.
 */
Agency XyzContractorEmployee::getAgency() const {
    return mAgency;
}

/**
 * @brief Prints a one-line tabular summary to stdout.
 * @return void
 */
void XyzContractorEmployee::printSummary() const {
    std::cout << "| " << std::setw(20) << std::left << getName()
              << "| " << std::setw(10) << std::left << getId()
              << "| " << std::setw(12) << std::left << "Contractor"
              << "| " << std::setw(10) << std::left << HelperFunctions::convertStatusToString(getStatus())
              << "| " << std::setw(15) << std::left << HelperFunctions::convertAgencyToString(mAgency) << "|\n";
}

/**
 * @brief Prints a multi-line detailed description to stdout.
 * @return void
 */
void XyzContractorEmployee::printFullDetails() const {
    std::cout << "\n--- Employee Details ---\n"
              << "  Employee Name  : " << getName() << "\n"
              << "  Employee ID    : " << getId() << "\n"
              << "  Employee Type  : " << "Contractor" << "\n"
              << "  Employee Status: " << HelperFunctions::convertStatusToString(getStatus()) << "\n"
              << "  Gender         : " << getGender() << "\n"
              << "  Date of Birth  : " << getDob() << "\n"
              << "  Date of Joining: " << getDoj() << "\n"
              << "  Date of Leaving: " << getDol() << "\n"
              << "  External Agency: " << HelperFunctions::convertAgencyToString(mAgency) << "\n"
              << "------------------------\n";
}