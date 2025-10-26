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
    std::string mDol;
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
        : mName(nameParm), mId(idParm), mGender(genderParm),
          mDob(dobParm), mDoj(dojParm), mDol(dolParm), mStatus(statusParm),
          mType(typeParm) {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~XyzEmployeeBase() {}

    // Getters
    std::string getName() const override { return mName; }
    std::string getId() const override { return mId; }
    std::string getGender() const override { return mGender; }
    std::string getDob() const override { return mDob; }
    std::string getDoj() const override { return mDoj; }
    virtual std::string getDol() const { return mDol; }
    EmployeeStatus getStatus() const override { return mStatus; }
    EmployeeType getType() const override { return mType; }

    void setStatus(EmployeeStatus statusParm) { mStatus = statusParm; }
    void setDol(const std::string& dolParm) { mDol = dolParm; }

    // Default no-op; overridden by full-time.
    void addLeaves(int) override {}
    virtual int getLeaves() const { return DefaultLeaves; }

    virtual void printFullDetails() const override = 0;
};

#endif // XYZ_EMPLOYEE_BASE_H

