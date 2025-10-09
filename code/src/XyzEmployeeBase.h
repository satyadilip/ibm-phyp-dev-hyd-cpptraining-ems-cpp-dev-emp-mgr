#ifndef XYZ_EMPLOYEE_BASE_H
#define XYZ_EMPLOYEE_BASE_H

#include "XyzEmployeeIF.h"
#include "Enums.h"
#include <string>

/**
 * @class XyzEmployeeBase
 * @brief An abstract base class that implements the XyzEmployeeIF interface.
 *
 * This class holds all the common data members and provides default implementations
 * for some virtual functions, reducing code duplication in derived classes.
 */
class XyzEmployeeBase : public XyzEmployeeIF {
protected:
    std::string mName;
    std::string mId;
    std::string mGender;
    std::string mDob;
    std::string mDoj;
    std::string mDol; // Date of Leaving
    EmployeeStatus mStatus;
    EmployeeType mType;

public:
    /**
     * @brief Construct a new XyzEmployeeBase object.
     */
    XyzEmployeeBase(const std::string& nameParm, const std::string& idParm,
                    const std::string& genderParm, const std::string& dobParm,
                    const std::string& dojParm, EmployeeStatus statusParm,
                    EmployeeType typeParm, const std::string& dolParm = "NA")
        // Corrected initialization order to match member declaration order.
        : mName(nameParm), mId(idParm), mGender(genderParm),
          mDob(dobParm), mDoj(dojParm), mDol(dolParm), mStatus(statusParm), 
          mType(typeParm) {}
    
    /**
     * @brief Virtual destructor.
     */
    virtual ~XyzEmployeeBase() {}

    // --- Getters (implementing the interface) ---
    // Corrected function names to match the interface and coding conventions.
    std::string getName() const override { return mName; }
    std::string getId() const override { return mId; }
    std::string getGender() const override { return mGender; }
    std::string getDob() const override { return mDob; }
    std::string getDoj() const override { return mDoj; }
    
    // --- Additional Getters for Base Properties ---
    virtual std::string getDol() const { return mDol; }
    EmployeeStatus getStatus() const { return mStatus; }
    EmployeeType getType() const { return mType; }
    
    // --- Setters for Updatable Fields ---
    void setStatus(EmployeeStatus statusParm) { mStatus = statusParm; }
    void setDol(const std::string& dolParm) { mDol = dolParm; }

    // --- Virtual Functions for Type-Specific Behavior ---
    
    /**
     * @brief Adds leaves to an employee. Default is a no-op.
     * Only overridden by XyzFullTimeEmployee.
     * @param leavesParm The number of leaves to add.
     */
    virtual void addLeaves(int leavesParm) { /* No-op for non-full-time */ }

    /**
     * @brief Gets the available leaves of an employee. Default is DefaultLeaves.
     * Only overridden by XyzFullTimeEmployee.
     * @return Number of leaves.
     */
    virtual int getLeaves() const { return DefaultLeaves; }

    // --- Pure Virtual Print Functions (from interface) ---
    virtual void printSummary() const override = 0;
    virtual void printFullDetails() const override = 0;
};

#endif // XYZ_EMPLOYEE_BASE_H

