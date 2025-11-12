#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "Enums.h"
#include <string>

/**
 * @class HelperFunctions
 * @brief Utility class providing static helper methods for the application.
 */
class HelperFunctions
{
public:
  // Random data helpers
  static std::string getRandomName(std::string genderParm);
  static std::string getRandomGender();
  static std::string getRandomDate();
  static EmployeeStatus getRandomStatus();
  static EmployeeType getRandomType();

  // User input helpers
  static int getMenuChoice(int minOptionParm, int maxOptionParm, int backCodeParm);
  static void clearInputBuffer();
  static std::string getCurrentDate();

  // Date helpers
  static void parseDate(const std::string &dateParm, int &d, int &m, int &y);
  static std::string makeDate(int d, int m, int y);
  static std::string addMonths(const std::string &dateParm, int monthsToAdd);
  static std::string addYears(const std::string &dateParm, int yearsToAdd);
  static std::string getRandomDOB();
  static std::string getRandomDOJFromDOB(const std::string &dobParm);
  static std::string computeDateOfLeaving(EmployeeType typeParm, const std::string &dojParm);

  // Conversions
  static std::string convertTypeToString(EmployeeType typeParm);
  static std::string convertStatusToString(EmployeeStatus statusParm);
  static std::string convertAgencyToString(Agency agencyParm);
  static std::string convertCollegeToString(College collegeParm);
  static std::string convertBranchToString(Branch branchParm);

  // String helpers
  static std::string trim(const std::string& sParm);
  static std::string toLower(std::string sParm);

  // Console input helper
  static std::string promptLine(const std::string& promptParm);

  // Validation helpers
  static bool isValidDateString(const std::string& sParm);
  static std::string normalizeGender(const std::string& sParm);
  static bool isAtLeastYearsApart(const std::string &fromDateParm, const std::string &toDateParm, int yearsParm);
};

#endif // HELPER_FUNCTIONS_H
