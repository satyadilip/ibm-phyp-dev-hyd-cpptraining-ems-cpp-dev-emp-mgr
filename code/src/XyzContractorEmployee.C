#include "XyzContractorEmployee.h"
#include "HelperFunctions.h"
#include "EmployeeSummary.h"
#include "PrintService.h"
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
 * @brief Prints a multi-line detailed description using PrintService.
 * @return void
 */
void XyzContractorEmployee::printFullDetails() const {
    PrintService::printTitle("Employee Details");
    PrintService::printKeyValue("Employee Name", getName());
    PrintService::printKeyValue("Employee ID", getId());
    PrintService::printKeyValue("Employee Type", "Contractor");
    PrintService::printKeyValue("Employee Status", HelperFunctions::convertStatusToString(getStatus()));
    PrintService::printKeyValue("Gender", getGender());
    PrintService::printKeyValue("Date of Birth", getDob());
    PrintService::printKeyValue("Date of Joining", getDoj());
    PrintService::printKeyValue("Date of Leaving", getDol());
    PrintService::printKeyValue("External Agency", HelperFunctions::convertAgencyToString(mAgency));
    PrintService::printDivider('-');
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