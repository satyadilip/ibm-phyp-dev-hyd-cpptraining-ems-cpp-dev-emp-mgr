#ifndef XYZ_FULL_TIME_EMPLOYEE_H
#define XYZ_FULL_TIME_EMPLOYEE_H

#include "XyzEmployeeBase.h"
#include <string>

class XyzFullTimeEmployee : public XyzEmployeeBase {
private:
    int mLeavesAvail;

public:
    XyzFullTimeEmployee(const std::string& nameParm, const std::string& idParm,
                        const std::string& genderParm, const std::string& dobParm,
                        const std::string& dojParm, EmployeeStatus statusParm,
                        int leavesAvailParm);

    void addLeaves(int leavesParm) override;
    int getLeaves() const override;
    void printSummary() const override;
    void printFullDetails() const override;
};

#endif // XYZ_FULL_TIME_EMPLOYEE_H