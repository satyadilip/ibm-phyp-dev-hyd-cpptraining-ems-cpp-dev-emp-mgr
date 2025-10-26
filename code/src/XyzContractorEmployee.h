#ifndef XYZ_CONTRACTOR_EMPLOYEE_H
#define XYZ_CONTRACTOR_EMPLOYEE_H

#include "XyzEmployeeBase.h"
#include <string>

class XyzContractorEmployee : public XyzEmployeeBase {
private:
    Agency mAgency;

public:
    XyzContractorEmployee(const std::string& nameParm, const std::string& idParm,
                          const std::string& genderParm, const std::string& dobParm,
                          const std::string& dojParm, EmployeeStatus statusParm,
                          Agency agencyParm, const std::string& dolParm);

    Agency getAgency() const;
    EmployeeSummary toSummary() const override;
    void printFullDetails() const override;
};

#endif // XYZ_CONTRACTOR_EMPLOYEE_H