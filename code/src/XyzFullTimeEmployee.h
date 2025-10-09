#ifndef XYZ_FULL_TIME_EMPLOYEE_H
#define XYZ_FULL_TIME_EMPLOYEE_H

#include "XyzEmployeeBase.h"
#include "HelperFunctions.h"
#include <iostream>
#include <iomanip>

/**
 * @class XyzFullTimeEmployee
 * @brief Represents a full-time employee, inheriting from XyzEmployeeBase.
 * It includes specific properties like available leaves.
 */
class XyzFullTimeEmployee : public XyzEmployeeBase {
private:
    int mLeavesAvail;

public:
    /**
     * @brief Construct a new XyzFullTimeEmployee object.
     */
    XyzFullTimeEmployee(const std::string& nameParm, const std::string& idParm,
                          const std::string& genderParm, const std::string& dobParm,
                          const std::string& dojParm, EmployeeStatus statusParm,
                          int leavesAvailParm)
        : XyzEmployeeBase(nameParm, idParm, genderParm, dobParm, dojParm, statusParm, FullTime),
          mLeavesAvail(leavesAvailParm) {}

    /**
     * @brief Adds or subtracts leaves, ensuring the total stays within [MinLeaves, MaxLeavesPerYear].
     * @param leavesParm Number of leaves to add (can be negative).
     */
    void addLeaves(int leavesParm) override {
        mLeavesAvail += leavesParm;
        if (mLeavesAvail > MaxLeavesPerYear) {
            mLeavesAvail = MaxLeavesPerYear;
        } else if (mLeavesAvail < MinLeaves) {
            mLeavesAvail = MinLeaves;
        }
    }

    /**
     * @brief Returns the number of leaves currently available.
     * @return The number of leaves.
     */
    int getLeaves() const override {
        return mLeavesAvail;
    }

    /**
     * @brief Prints a compact, single-line summary of the employee for tables.
     */
    void printSummary() const override {
        std::cout << "| " << std::setw(20) << std::left << getName()
                  << "| " << std::setw(10) << std::left << getId()
                  << "| " << std::setw(12) << std::left << "Full-Time"
                  << "| " << std::setw(10) << std::left << HelperFunctions::convertStatusToString(getStatus())
                  << "| " << std::setw(15) << std::left << ("Leaves: " + std::to_string(mLeavesAvail)) << "|\n";
    }
    
    /**
     * @brief Prints a detailed, multi-line view of the employee, matching assignment format.
     */
    void printFullDetails() const override {
        std::cout << "\n--- Employee Details ---\n"
                  << "  Employee Name : " << getName() << "\n"
                  << "  Employee ID   : " << getId() << "\n"
                  << "  Employee Type : " << "Full-Time" << "\n"
                  << "  Employee Status: " << HelperFunctions::convertStatusToString(getStatus()) << "\n"
                  << "  Gender        : " << getGender() << "\n"
                  << "  Date of Birth : " << getDob() << "\n"
                  << "  Date of Joining: " << getDoj() << "\n"
                  << "  Leaves Availed : " << mLeavesAvail << "\n"
                  << "  Leaves Left    : " << (MaxLeavesPerYear - mLeavesAvail) << "\n"
                  << "------------------------\n";
    }
};

#endif // XYZ_FULL_TIME_EMPLOYEE_H
