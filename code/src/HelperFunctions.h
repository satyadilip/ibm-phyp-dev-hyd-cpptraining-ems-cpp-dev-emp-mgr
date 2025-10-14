#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "Enums.h"
#include <string> // std::string only

/**
 * @class HelperFunctions
 * @brief Utility class providing static helper methods for the application.
 */
class HelperFunctions
{
public:
  // Console/menu helpers
  static void printMenu(const std::string &titleParm, const char *optionsParm[], int numOptionsParm, int exitCodeParm, MenuContext ctxParm);
  static void clearInputBuffer();

  // Random data generators
  static std::string getRandomName(std::string genderParm);
  static std::string getRandomGender();
  static std::string getRandomDate();
  static EmployeeStatus getRandomStatus();
  static EmployeeType getRandomType();

  // User input helpers
  static std::string getInputName();
  static std::string getInputGender();
  static std::string getInputDate(const std::string &promptParm);

  // Date helpers (DD-MM-YYYY)
  static void parseDate(const std::string &dateParm, int &d, int &m, int &y);
  static std::string makeDate(int d, int m, int y);
  static std::string addMonths(const std::string &dateParm, int monthsToAdd);
  static std::string addYears(const std::string &dateParm, int yearsToAdd);
  static std::string getRandomDOB();
  static std::string getRandomDOJFromDOB(const std::string &dobParm);
  static std::string computeDateOfLeaving(EmployeeType typeParm, const std::string &dojParm);

  // Chronology validators
  static bool isAtLeastYearsApart(const std::string &fromDateParm, const std::string &toDateParm, int yearsParm);

  // Conversions
  static std::string convertTypeToString(EmployeeType typeParm);
  static std::string convertStatusToString(EmployeeStatus statusParm);
  static std::string convertAgencyToString(Agency agencyParm);
  static std::string convertCollegeToString(College collegeParm);
  static std::string convertBranchToString(Branch branchParm);
};

#endif // HELPER_FUNCTIONS_H
