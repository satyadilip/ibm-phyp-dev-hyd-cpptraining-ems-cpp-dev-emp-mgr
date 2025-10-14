#include "XyzFullTimeEmployee.h"
#include "HelperFunctions.h"
#include <iostream>
#include <iomanip>

/**
 * @class XyzFullTimeEmployee
 * @brief Represents a full-time employee.
 */

/**
 * @brief Constructs a full-time employee with an initial leave state.
 * @param nameParm Employee's full name.
 * @param idParm Unique employee identifier.
 * @param genderParm Employee gender string.
 * @param dobParm Date of birth in ISO format (YYYY-MM-DD).
 * @param dojParm Date of joining in ISO format (YYYY-MM-DD).
 * @param statusParm Current employment status.
 * @param leavesAvailParm Initial leaves counter.
 * @return void
 */
XyzFullTimeEmployee::XyzFullTimeEmployee(const std::string& nameParm, const std::string& idParm,
                                         const std::string& genderParm, const std::string& dobParm,
                                         const std::string& dojParm, EmployeeStatus statusParm,
                                         int leavesAvailParm)
    : XyzEmployeeBase(nameParm, idParm, genderParm, dobParm, dojParm, statusParm, FullTime),
      mLeavesAvail(leavesAvailParm) {}

/**
 * @brief Adjusts the leaves counter and clamps it to the valid range.
 * @param leavesParm Positive to increase, negative to decrease.
 * @return void
 */
void XyzFullTimeEmployee::addLeaves(int leavesParm)
{
    mLeavesAvail += leavesParm;
    if (mLeavesAvail > MaxLeavesPerYear) {
        mLeavesAvail = MaxLeavesPerYear;
    } else if (mLeavesAvail < MinLeaves) {
        mLeavesAvail = MinLeaves;
    }
}

/**
 * @brief Gets the current leaves counter.
 * @return int Current number of leaves.
 */
int XyzFullTimeEmployee::getLeaves() const
{
    return mLeavesAvail;
}

/**
 * @brief Prints a one-line tabular summary to stdout.
 * @return void
 */
void XyzFullTimeEmployee::printSummary() const
{
    using std::left;
    using std::setw;

    const int wName = WName, wId = WId, wGender = WGender, wType = WType, wStatus = WStatus;
    const int wDob = WDob, wDoj = WDoj, wDol = WDol, wTotLeaves = WTotLeaves, wAvailed = WAvailed, wAgency = WAgency, wCollege = WCollege, wBranch = WBranch;

    const int totalLeaves = MaxLeavesPerYear;
    const int availed = totalLeaves - getLeaves();

    std::cout << "|"
              << left << setw(wName)     << getName()                                        << "|"
              << left << setw(wId)       << getId()                                          << "|"
              << left << setw(wGender)   << getGender()                                      << "|"
              << left << setw(wType)     << HelperFunctions::convertTypeToString(getType())  << "|"
              << left << setw(wStatus)   << HelperFunctions::convertStatusToString(getStatus()) << "|"
              << left << setw(wDob)      << getDob()                                         << "|"
              << left << setw(wDoj)      << getDoj()                                         << "|"
              << left << setw(wDol)      << "-"                                              << "|"
              << left << setw(wTotLeaves)<< totalLeaves                                      << "|"
              << left << setw(wAvailed)  << availed                                          << "|"
              << left << setw(wAgency)   << "-"                                              << "|"
              << left << setw(wCollege)  << "-"                                              << "|"
              << left << setw(wBranch)   << "-"                                              << "|\n";
}

/**
 * @brief Prints a multi-line detailed description to stdout.
 * @return void
 */
void XyzFullTimeEmployee::printFullDetails() const
{
    std::cout << "\n--- Employee Details ---\n"
              << "  Employee Name   : " << getName() << "\n"
              << "  Employee ID     : " << getId() << "\n"
              << "  Employee Type   : " << "Full-Time" << "\n"
              << "  Employee Status : " << HelperFunctions::convertStatusToString(getStatus()) << "\n"
              << "  Gender          : " << getGender() << "\n"
              << "  Date of Birth   : " << getDob() << "\n"
              << "  Date of Joining : " << getDoj() << "\n"
              << "  Leaves Availed  : " << mLeavesAvail << "\n"
              << "  Leaves Left     : " << (MaxLeavesPerYear - mLeavesAvail) << "\n"
              << "-------------------------------\n";
}