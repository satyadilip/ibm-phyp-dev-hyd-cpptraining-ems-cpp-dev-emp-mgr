#ifndef XYZ_EMPLOYEE_IF_H
#define XYZ_EMPLOYEE_IF_H

#include <string>
#include "EmployeeSummary.h"
#include "Enums.h"

/**
 * @class XyzEmployeeIF
 * @brief The interface class for all employee types.
 *
 * This abstract class defines the common contract that all concrete employee
 * classes must adhere to. It uses pure virtual functions to enforce implementation.
 */
class XyzEmployeeIF {
public:
    virtual std::string getName() const = 0;
    virtual std::string getId() const = 0;
    virtual std::string getGender() const = 0;
    virtual std::string getDob() const = 0;
    virtual std::string getDoj() const = 0;

    virtual EmployeeType getType() const = 0;
    virtual EmployeeStatus getStatus() const = 0;

    virtual EmployeeSummary toSummary() const = 0;
    virtual void printFullDetails() const = 0;

    virtual void addLeaves(int leavesParm) = 0;

    virtual ~XyzEmployeeIF() {}
};

#endif // XYZ_EMPLOYEE_IF_H

