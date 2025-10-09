#ifndef EMPLOYEE_ID_GENERATOR_H
#define EMPLOYEE_ID_GENERATOR_H

#include <string>
#include <sstream>
#include <iomanip>
#include "Enums.h"

/**
 * @class EmployeeIDGenerator
 * @brief A utility class to generate formatted employee IDs.
 *
 * This class provides a static method to create employee IDs according to the
 * format "XYZ" + 4-digit numeric code + Type Code (F/C/I).
 */
class EmployeeIDGenerator {
public:
    /**
     * @brief Generates a unique employee ID based on type and a counter.
     * @param typeParm The type of the employee (FullTime, Contractor, Intern).
     * @param counterParm A unique number for the employee.
     * @return A formatted employee ID string.
     */
    static std::string generateID(EmployeeType typeParm, int counterParm) {
        std::ostringstream sStream;
        sStream << "XYZ" << std::setw(EmployeeIdNumericLength) << std::setfill('0') << counterParm;

        switch (typeParm) {
            case FullTime:   sStream << 'F'; break;
            case Contractor: sStream << 'C'; break;
            case Intern:     sStream << 'I'; break;
        }
        return sStream.str();
    }
};

#endif // EMPLOYEE_ID_GENERATOR_H
