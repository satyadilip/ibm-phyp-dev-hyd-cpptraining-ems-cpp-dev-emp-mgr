#ifndef XYZ_RESIGNED_EMPLOYEE_H
#define XYZ_RESIGNED_EMPLOYEE_H

#include "XyzEmployeeBase.h"
#include "HelperFunctions.h"
#include <iostream>
#include <iomanip>

/**
 * @class XyzResignedEmployee
 * @brief Represents a resigned employee with a minimal set of archived data.
 */
class XyzResignedEmployee : public XyzEmployeeBase {
public:
    /**
     * @brief Construct a new XyzResignedEmployee object.
     * @param nameParm Employee's full name.
     * @param idParm Employee's ID.
     * @param typeParm The employee's type at the time of resignation.
     * @param genderParm Employee's gender.
     * @param dobParm Employee's date of birth.
     * @param dojParm Employee's original date of joining.
     * @param dolParm Employee's date of leaving.
     */
    XyzResignedEmployee(const std::string& nameParm, const std::string& idParm,
                          EmployeeType typeParm, const std::string& genderParm, 
                          const std::string& dobParm, const std::string& dojParm, 
                          const std::string& dolParm)
        : XyzEmployeeBase(nameParm, idParm, genderParm, dobParm, dojParm, Resigned, typeParm, dolParm) {}

    /**
     * @brief Prints a compact, single-line summary of the resigned employee for tables.
     */
    void printSummary() const override {
        std::cout << "| " << std::setw(20) << std::left << getName()
                  << "| " << std::setw(10) << std::left << getId()
                  << "| " << std::setw(12) << std::left << HelperFunctions::convertTypeToString(getType())
                  << "| " << std::setw(10) << std::left << "Resigned"
                  << "| " << std::setw(15) << std::left << ("DOL: " + getDol()) << "|\n";
    }

    /**
     * @brief Prints a detailed, multi-line view of the resigned employee's archived data.
     */
    void printFullDetails() const override {
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
};

#endif // XYZ_RESIGNED_EMPLOYEE_H
