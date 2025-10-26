#ifndef XYZ_INTERN_EMPLOYEE_H
#define XYZ_INTERN_EMPLOYEE_H

#include "XyzEmployeeBase.h"
#include <string>

class XyzInternEmployee : public XyzEmployeeBase {
private:
    College mCollege;
    Branch mBranch;

public:
    XyzInternEmployee(const std::string& nameParm, const std::string& idParm,
                      const std::string& genderParm, const std::string& dobParm,
                      const std::string& dojParm, EmployeeStatus statusParm,
                      College collegeParm, Branch branchParm, const std::string& dolParm);

    College getCollege() const;
    Branch getBranch() const;
    EmployeeSummary toSummary() const override;
    void printFullDetails() const override;
};

#endif // XYZ_INTERN_EMPLOYEE_H