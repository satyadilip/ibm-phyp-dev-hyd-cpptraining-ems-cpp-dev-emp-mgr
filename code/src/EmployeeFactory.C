#include "EmployeeFactory.h"
#include "XyzFullTimeEmployee.h"
#include "XyzContractorEmployee.h"
#include "XyzInternEmployee.h"
#include "XyzResignedEmployee.h"

/**
 *@brief Factory method to create different types of Employee objects based on the provided arguments.
 *@param argsParm A structure containing the necessary parameters to create an employee.
 *@return A pointer to the created XyzEmployeeIF object.  
**/
XyzEmployeeIF* EmployeeFactory::create(const NewEmployeeArgs& argsParm)
{
    if (argsParm.mStatus == Resigned) {
        return new XyzResignedEmployee(argsParm.mName, argsParm.mId, argsParm.mType, argsParm.mGender,
                                       argsParm.mDob, argsParm.mDoj, argsParm.mDol);
    }

    switch (argsParm.mType) {
        case FullTime:
            return new XyzFullTimeEmployee(argsParm.mName, argsParm.mId, argsParm.mGender, argsParm.mDob,
                                           argsParm.mDoj, argsParm.mStatus, argsParm.mLeaves);
        case Contractor:
            return new XyzContractorEmployee(argsParm.mName, argsParm.mId, argsParm.mGender, argsParm.mDob,
                                             argsParm.mDoj, argsParm.mStatus, argsParm.mAgency, argsParm.mDol);
        case Intern:
            return new XyzInternEmployee(argsParm.mName, argsParm.mId, argsParm.mGender, argsParm.mDob,
                                         argsParm.mDoj, argsParm.mStatus, argsParm.mCollege, argsParm.mBranch, argsParm.mDol);
    }
    return nullptr;
}