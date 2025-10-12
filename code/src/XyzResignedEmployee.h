#ifndef XYZ_RESIGNED_EMPLOYEE_H
#define XYZ_RESIGNED_EMPLOYEE_H

#include "XyzEmployeeBase.h"
#include <string>

class XyzResignedEmployee : public XyzEmployeeBase {
public:
    XyzResignedEmployee(const std::string& nameParm, const std::string& idParm,
                        EmployeeType typeParm, const std::string& genderParm, 
                        const std::string& dobParm, const std::string& dojParm, 
                        const std::string& dolParm);

    void printSummary() const override;
    void printFullDetails() const override;
};

#endif // XYZ_RESIGNED_EMPLOYEE_H