#include "XyzContractorEmployee.h"
#include "HelperFunctions.h"
#include "EmployeeSummary.h"
#include <iostream>

/**
 * @class XyzContractorEmployee
 * @brief Represents a contractor employee.
 */

/**
 * @brief Constructs a contractor with external agency details.
 * @param nameParm Employee's full name.
 * @param idParm Unique employee identifier.
 * @param genderParm Employee gender string.
 * @param dobParm Date of birth in DD-MM-YYYY format.
 * @param dojParm Date of joining in DD-MM-YYYY format.
 * @param statusParm Current employment status.
 * @param agencyParm Contracting agency enum value.
 * @param dolParm Date of leaving in DD-MM-YYYY format.
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
              << "-------------------------------\n";
}

/**
 * @brief Converts the contractor employee details to a summary object.
 * @return EmployeeSummary Summary object containing employee details.
 */
EmployeeSummary XyzContractorEmployee::toSummary() const
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
    sSummary.agency = HelperFunctions::convertAgencyToString(mAgency);
    return sSummary;
}