#include "XyzFullTimeEmployee.h"
#include "HelperFunctions.h"
#include "EmployeeSummary.h"
#include "PrintService.h"
#include <iostream>

/**
 * @class XyzFullTimeEmployee
 * @brief Represents a full-time employee.
 */

/**
 * @brief Constructs a full-time employee with an initial leave state.
 * @param nameParm Employee's full name.
 * @param idParm Unique employee identifier.
 * @param genderParm Employee gender string.
 * @param dobParm Date of birth in DD-MM-YYYY format.
 * @param dojParm Date of joining in DD-MM-YYYY format.
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
 * @brief Converts the employee details to a summary structure.
 * @return EmployeeSummary Struct containing summary information.
 */
EmployeeSummary XyzFullTimeEmployee::toSummary() const
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
    sSummary.totalLeaves = MaxLeavesPerYear;
    sSummary.availedLeaves = MaxLeavesPerYear - getLeaves();
    return sSummary;
}

/**
 * @brief Prints a multi-line detailed description using PrintService.
 * @return void
 */
void XyzFullTimeEmployee::printFullDetails() const
{
    PrintService::printTitle("Employee Details");
    PrintService::printKeyValue("Employee Name", getName());
    PrintService::printKeyValue("Employee ID", getId());
    PrintService::printKeyValue("Employee Type", HelperFunctions::convertTypeToString(getType()));
    PrintService::printKeyValue("Employee Status", HelperFunctions::convertStatusToString(getStatus()));
    PrintService::printKeyValue("Gender", getGender());
    PrintService::printKeyValue("Date of Birth", getDob());
    PrintService::printKeyValue("Date of Joining", getDoj());
    PrintService::printKeyValue("Leaves Availed", mLeavesAvail);
    PrintService::printKeyValue("Leaves Left", MaxLeavesPerYear - mLeavesAvail);
    PrintService::printDivider('-');
}