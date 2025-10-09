#ifndef XYZ_EMPLOYEE_IF_H
#define XYZ_EMPLOYEE_IF_H

#include <string>

/**
 * @class XyzEmployeeIF
 * @brief The interface class for all employee types.
 *
 * This abstract class defines the common contract that all concrete employee
 * classes must adhere to. It uses pure virtual functions to enforce implementation.
 */
class XyzEmployeeIF {
public:
    // --- Pure Virtual Getters for Common Properties ---
    // Corrected function names to follow coding conventions (camelCase starting small).
    virtual std::string getName() const = 0;
    virtual std::string getId() const = 0;
    virtual std::string getGender() const = 0;
    virtual std::string getDob() const = 0;
    virtual std::string getDoj() const = 0;
    
    /**
     * @brief Prints a single, formatted row for the generic summary table.
     * This method is intended for compact, tabular summaries.
     */
    virtual void printSummary() const = 0; 
    
    /**
     * @brief Prints full, verbose details for an employee.
     * This method is intended for detailed views, typically spanning multiple lines.
     */
    virtual void printFullDetails() const = 0; 
    
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived objects.
     */
    virtual ~XyzEmployeeIF() {}
};

#endif // XYZ_EMPLOYEE_IF_H

