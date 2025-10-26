#ifndef EMPLOYEE_FACTORY_H
#define EMPLOYEE_FACTORY_H

#include "XyzEmployeeIF.h"
#include "Enums.h"
#include <string>

struct NewEmployeeArgs {
    std::string mName;
    std::string mId;
    std::string mGender;
    std::string mDob;
    std::string mDoj;
    std::string mDol; // "-" if not applicable
    EmployeeType mType;
    EmployeeStatus mStatus;

    int mLeaves = 0;              // for FullTime
    Agency mAgency = Avengers;    // for Contractor
    College mCollege = IITDelhi;  // for Intern
    Branch mBranch = CSE;         // for Intern
};

class EmployeeFactory {
public:
    static XyzEmployeeIF* create(const NewEmployeeArgs& argsParm);
};

#endif // EMPLOYEE_FACTORY_H