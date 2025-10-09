#ifndef XYZ_CONTRACTOR_EMPLOYEE_H
#define XYZ_CONTRACTOR_EMPLOYEE_H

#include "XyzEmployeeBase.h"
#include "HelperFunctions.h"
#include <iostream>
#include <iomanip>

/**
 * @class XyzContractorEmployee
 * @brief Represents a contractor, inheriting from XyzEmployeeBase.
 * It includes contractor-specific properties like the external agency.
 */
class XyzContractorEmployee : public XyzEmployeeBase {
private:
    Agency mAgency;

public:
    /**
     * @brief Construct a new XyzContractorEmployee object.
     */
    XyzContractorEmployee(const std::string& nameParm, const std::string& idParm,
                          const std::string& genderParm, const std::string& dobParm,
                          const std::string& dojParm, EmployeeStatus statusParm,
                          Agency agencyParm, const std::string& dolParm)
        : XyzEmployeeBase(nameParm, idParm, genderParm, dobParm, dojParm, statusParm, Contractor, dolParm),
          mAgency(agencyParm) {}

    /**
     * @brief Returns the contractor's agency.
     * @return Agency enum value.
     */
    Agency getAgency() const { return mAgency; }

    /**
     * @brief Prints a compact, single-line summary of the employee for tables.
     */
    void printSummary() const override {
        std::cout << "| " << std::setw(20) << std::left << getName()
                  << "| " << std::setw(10) << std::left << getId()
                  << "| " << std::setw(12) << std::left << "Contractor"
                  << "| " << std::setw(10) << std::left << HelperFunctions::convertStatusToString(getStatus())
                  << "| " << std::setw(15) << std::left << HelperFunctions::convertAgencyToString(mAgency) << "|\n";
    }

    /**
     * @brief Prints a detailed, multi-line view of the employee, matching assignment format.
     */
    void printFullDetails() const override {
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
};

#endif // XYZ_CONTRACTOR_EMPLOYEE_H
