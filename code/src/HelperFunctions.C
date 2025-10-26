#include "HelperFunctions.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>
#include <algorithm>
#include <sstream>

// ---------------- Console/menu helpers ----------------

/**
 * @brief Prints a formatted menu box to stdout.
 * @param titleParm Title text displayed at the top of the menu.
 * @param optionsParm Array of C-strings for each option (size >= numOptionsParm).
 * @param numOptionsParm Number of valid entries in optionsParm to display.
 * @param exitCodeParm The numeric code the user should enter to exit/go back (shown at bottom line).
 * @param ctxParm Menu context to decide label wording (Exit vs go back to previous menu).
 * @return void
 */
void HelperFunctions::printMenu(const std::string &titleParm, const char *optionsParm[], int numOptionsParm, int exitCodeParm, MenuContext ctxParm)
{
  size_t sMaxLen = 0;
  std::string sTitleLine = "       " + titleParm;
  if (sTitleLine.length() > sMaxLen) sMaxLen = sTitleLine.length();

  for (int sI = 0; sI < numOptionsParm; ++sI)
  {
    std::string sOpt = "       " + std::to_string(sI + 1) + ". " + optionsParm[sI];
    if (sOpt.length() > sMaxLen) sMaxLen = sOpt.length();
  }

  std::string sExitMsg = "Press " + std::to_string(exitCodeParm) +
                         ((ctxParm == RootMenuContext) ? " to Exit" : " to go back to previous menu");
  std::string sExitLine = "         " + sExitMsg;
  if (sExitLine.length() > sMaxLen) sMaxLen = sExitLine.length();

  size_t sWidth = sMaxLen + 2;

  std::cout << std::string(sWidth, '-') << "\n";
  std::cout << "|" << sTitleLine << std::string(sWidth - 1 - sTitleLine.length(), ' ') << "|\n";
  std::cout << std::string(sWidth, '-') << "\n";

  for (int sI = 0; sI < numOptionsParm; ++sI)
  {
    std::string sOpt = "       " + std::to_string(sI + 1) + ". " + optionsParm[sI];
    std::cout << "|" << sOpt << std::string(sWidth - 1 - sOpt.length(), ' ') << "|\n";
  }

  std::cout << "|" << sExitLine << std::string(sWidth - 1 - sExitLine.length(), ' ') << "|\n";
  std::cout << std::string(sWidth, '-') << "\n";
}

/**
 * @brief Clears std::cin error state and drains remaining input up to newline.
 * @return void
 */
void HelperFunctions::clearInputBuffer()
{
  std::cin.clear();
  int sCh = 0;
  while ((sCh = std::cin.get()) != '\n' && sCh != EOF) { /* drain */ }
}

// ---------------- Random data generators ----------------

/**
 * @brief Returns a random name based on gender.
 * @param genderParm Gender string; "Male" selects male pool, any other selects female pool.
 * @return std::string Randomly chosen name from the respective pool.
 */
std::string HelperFunctions::getRandomName(std::string genderParm)
{
  static const char *sMaleNames[] = {"Bahubali", "Kattappa", "Ballaldeva", "KumaraVarma", "PushpaRaj"};
  static const char *sFemaleNames[] = {"Devasena", "Avantika", "Sivagami", "Srivalli", "Sita"};
  int sIndex = std::rand() % MaxNamesInPool;
  if (genderParm == "Male")
  {
    return sMaleNames[sIndex];
  }
  return sFemaleNames[sIndex];
}

/**
 * @brief Generates a random gender string.
 * @return std::string "Male" or "Female" with equal probability.
 */
std::string HelperFunctions::getRandomGender()
{
  return (std::rand() % 2 == 0) ? "Male" : "Female";
}

/**
 * @brief Generates a random date string.
 * @details Day range 01..28, month 01..12, year 1990..2019 to avoid invalid dates.
 * @return std::string Date in DD-MM-YYYY format.
 */
std::string HelperFunctions::getRandomDate()
{
  int sDay = MinDay + std::rand() % (MaxDay - MinDay + 1);
  int sMonth = MinMonth + std::rand() % (MaxMonth - MinMonth + 1);
  int sYear = MinBirthYear + std::rand() % (MaxBirthYear - MinBirthYear + 1);
  char sDate[11];
  std::snprintf(sDate, sizeof(sDate), "%02d-%02d-%04d", sDay, sMonth, sYear);
  return std::string(sDate);
}

/**
 * @brief Picks a random EmployeeStatus.
 * @return EmployeeStatus One of the defined status enum values.
 */
EmployeeStatus HelperFunctions::getRandomStatus()
{
  int sRand = std::rand() % MaxEmployeeStatuses;
  return static_cast<EmployeeStatus>(sRand);
}

/**
 * @brief Picks a random EmployeeType.
 * @return EmployeeType One of the defined type enum values.
 */
EmployeeType HelperFunctions::getRandomType()
{
  int sRand = std::rand() % MaxEmployeeTypes;
  return static_cast<EmployeeType>(sRand);
}

// ---------------- User input helpers ----------------

/**
 * Safely reads an integer input from the user with validation.
 * Uses character-by-character reading to prevent buffer overflow.
 * 
 * @param minOptionParm Minimum valid option (typically 1)
 * @param maxOptionParm Maximum valid option (typically 9)
 * @param backCodeParm Back/exit code (typically -1)
 * @return Valid user choice within range or backCodeParm
 */
int HelperFunctions::getMenuChoice(int minOptionParm, int maxOptionParm, int backCodeParm)
{
  int value;
  while (true)
  {
    std::cin >> value;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if ((value == backCodeParm) || (value >= minOptionParm && value <= maxOptionParm)) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return value;
    } else {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Invalid input. Enter " << minOptionParm << "-" << maxOptionParm
              << " or " << backCodeParm << ".\n";
    std::cout << "Your Choice: ";
  }
}

// ---------------- Date helpers (DD-MM-YYYY) ----------------

/**
 * @brief Parses a DD-MM-YYYY date string into day, month, and year integers.
 * @param dateParm Input date string in DD-MM-YYYY format.
 * @param d Output day (1..31, but callers in this module clamp to <= 28).
 * @param m Output month (1..12).
 * @param y Output year (e.g., 1995).
 * @return void
 */
void HelperFunctions::parseDate(const std::string &dateParm, int &d, int &m, int &y)
{
  d = std::stoi(dateParm.substr(0, 2));
  m = std::stoi(dateParm.substr(3, 2));
  y = std::stoi(dateParm.substr(6, 4));
}

/**
 * @brief File-local clamp helper to bound integer values.
 * @param v Input value.
 * @param lo Minimum bound (inclusive).
 * @param hi Maximum bound (inclusive).
 * @return int Clamped value in [lo, hi].
 */
static inline int sClamp(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }

/**
 * @brief Composes a DD-MM-YYYY date string from day, month, and year.
 * @details Day is clamped to 1..28 and month to 1..12 to avoid invalid dates.
 * @param d Day value (1..31; clamped to 1..28).
 * @param m Month value (1..12; clamped).
 * @param y Year value (e.g., 2001).
 * @return std::string Formatted date string DD-MM-YYYY.
 */
std::string HelperFunctions::makeDate(int d, int m, int y)
{
  d = sClamp(d, 1, 28);
  m = sClamp(m, 1, 12);
  char sDate[11];
  std::snprintf(sDate, sizeof(sDate), "%02d-%02d-%04d", d, m, y);
  return std::string(sDate);
}

/**
 * @brief Adds a number of months to a DD-MM-YYYY date string.
 * @details Preserves day up to 28; rolls month/year correctly across boundaries.
 * @param dateParm Base date in DD-MM-YYYY format.
 * @param monthsToAdd Number of months to add (can be negative; result is floored at year 0, month 1).
 * @return std::string New date in DD-MM-YYYY format.
 */
std::string HelperFunctions::addMonths(const std::string &dateParm, int monthsToAdd)
{
  int d, m, y;
  parseDate(dateParm, d, m, y);
  int sTotalMonths = (y * 12 + (m - 1)) + monthsToAdd;
  if (sTotalMonths < 0) sTotalMonths = 0;
  int sNewY = sTotalMonths / 12;
  int sNewM = (sTotalMonths % 12) + 1;
  int sNewD = (d > 28 ? 28 : d);
  return makeDate(sNewD, sNewM, sNewY);
}

/**
 * @brief Adds a number of years to a DD-MM-YYYY date string.
 * @details Preserves month and clamps day to <= 28 to avoid invalid dates.
 * @param dateParm Base date in DD-MM-YYYY format.
 * @param yearsToAdd Number of years to add (can be negative).
 * @return std::string New date in DD-MM-YYYY format.
 */
std::string HelperFunctions::addYears(const std::string &dateParm, int yearsToAdd)
{
  int d, m, y;
  parseDate(dateParm, d, m, y);
  int sNewD = (d > 28 ? 28 : d);
  return makeDate(sNewD, m, y + yearsToAdd);
}

/**
 * @brief Generates a random Date of Birth consistent with adult employment.
 * @details Year range 1970..2004, month 01..12, day 01..28.
 * @return std::string DOB in DD-MM-YYYY format.
 */
std::string HelperFunctions::getRandomDOB()
{
  int sDay = MinDay + std::rand() % (MaxDay - MinDay + 1);
  int sMonth = MinMonth + std::rand() % (MaxMonth - MinMonth + 1);
  int sYear = MinBirthYear + std::rand() % (MaxBirthYear - MinBirthYear + 1);
  return makeDate(sDay, sMonth, sYear);
}

/**
 * @brief Generates a random Date of Joining from a given DOB.
 * @details Ensures DOJ >= DOB + 18 years, then adds up to 20 years and up to 11 months randomly.
 * @param dobParm DOB in DD-MM-YYYY format.
 * @return std::string DOJ in DD-MM-YYYY format.
 */
std::string HelperFunctions::getRandomDOJFromDOB(const std::string &dobParm)
{
  std::string sBase = addYears(dobParm, 18);
  int sExtraYears = std::rand() % 21;  // 0..20
  int sExtraMonths = std::rand() % 12; // 0..11
  std::string sWithYears = addYears(sBase, sExtraYears);
  return addMonths(sWithYears, sExtraMonths);
}

/**
 * @brief Computes Date of Leaving based on employee type and DOJ.
 * @details
 *  - Contractor: DOJ + ~12 months (+/- up to 3 months, min 1 month).
 *  - Intern: DOJ + 6 months.
 *  - Others: DOJ + 1..10 years plus 0..11 extra months.
 * @param typeParm Employee type used to determine rule.
 * @param dojParm Date of joining in DD-MM-YYYY format.
 * @return std::string DOL in DD-MM-YYYY format.
 */
std::string HelperFunctions::computeDateOfLeaving(EmployeeType typeParm, const std::string &dojParm)
{
  if (typeParm == Contractor)
  {
    int sJitter = (std::rand() % 7) - 3; // -3..+3 months
    int sMonths = 12 + sJitter;
    if (sMonths < 1) sMonths = 1;
    return addMonths(dojParm, sMonths);
  }
  if (typeParm == Intern)
  {
    return addMonths(dojParm, 6);
  }
  int sYears = 1 + (std::rand() % 10);
  int sMonths = std::rand() % 12;
  std::string sWithYears = addYears(dojParm, sYears);
  return addMonths(sWithYears, sMonths);
}

// ---------------- Conversions ----------------

/**
 * @brief Converts an EmployeeType enum to a human-readable string.
 * @param typeParm EmployeeType value.
 * @return std::string "Full-Time", "Contractor", "Intern", or "Unknown".
 */
std::string HelperFunctions::convertTypeToString(EmployeeType typeParm)
{
  switch (typeParm)
  {
  case FullTime:   return "Full-Time";
  case Contractor: return "Contractor";
  case Intern:     return "Intern";
  default:         return "Unknown";
  }
}

/**
 * @brief Converts an EmployeeStatus enum to a human-readable string.
 * @param statusParm EmployeeStatus value.
 * @return std::string "Active", "Inactive", "Resigned", or "Unknown".
 */
std::string HelperFunctions::convertStatusToString(EmployeeStatus statusParm)
{
  switch (statusParm)
  {
  case Active:   return "Active";
  case Inactive: return "Inactive";
  case Resigned: return "Resigned";
  default:       return "Unknown";
  }
}

/**
 * @brief Converts an Agency enum to a human-readable string.
 * @param agencyParm Agency value.
 * @return std::string Agency name or "Unknown".
 */
std::string HelperFunctions::convertAgencyToString(Agency agencyParm)
{
  switch (agencyParm)
  {
  case Avengers:      return "Avengers";
  case JusticeLeague: return "Justice League";
  case XMen:          return "X-Men";
  default:            return "Unknown";
  }
}

/**
 * @brief Converts a College enum to a human-readable string.
 * @param collegeParm College value.
 * @return std::string College name or "Unknown".
 */
std::string HelperFunctions::convertCollegeToString(College collegeParm)
{
  switch (collegeParm)
  {
  case IITDelhi:       return "IIT Delhi";
  case IITMumbai:      return "IIT Mumbai";
  case IITKanpur:      return "IIT Kanpur";
  case IITHyderabad:   return "IIT Hyderabad";
  case NITWarangal:    return "NIT Warangal";
  case NITTiruchi:     return "NIT Tiruchi";
  case IIITHyderabad:  return "IIIT Hyderabad";
  default:             return "Unknown";
  }
}

/**
 * @brief Converts a Branch enum to a human-readable string.
 * @param branchParm Branch value.
 * @return std::string Branch code or "Unknown".
 */
std::string HelperFunctions::convertBranchToString(Branch branchParm)
{
  switch (branchParm)
  {
  case CSE:  return "CSE";
  case CSIT: return "CSIT";
  case ECE:  return "ECE";
  default:   return "Unknown";
  }
}


static inline int sToMonthIndex(const std::string &date)
{
  int d, m, y;
  HelperFunctions::parseDate(date, d, m, y);
  return y * 12 + (m - 1);
}

bool HelperFunctions::isAtLeastYearsApart(const std::string &fromDateParm, const std::string &toDateParm, int yearsParm)
{
  int sFrom = sToMonthIndex(fromDateParm);
  int sTo = sToMonthIndex(toDateParm);
  int sMinDiffMonths = yearsParm * 12;
  return (sTo - sFrom) >= sMinDiffMonths;
}

// ---------------- String and validation helpers ----------------
namespace {
  inline std::string rtrim(std::string s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) s.pop_back();
    return s;
  }
  inline std::string ltrim(std::string s) {
    size_t sI = 0;
    while (sI < s.size() && std::isspace(static_cast<unsigned char>(s[sI]))) ++sI;
    return s.substr(sI);
  }
  inline bool allDigits(const std::string& sParm, size_t posParm, size_t lenParm) {
    if (posParm + lenParm > sParm.size()) return false;
    for (size_t sI = 0; sI < lenParm; ++sI)
      if (!std::isdigit(static_cast<unsigned char>(sParm[posParm + sI]))) return false;
    return true;
  }
  inline bool isLeap(int yParm) { return (yParm % 400 == 0) || ((yParm % 4 == 0) && (yParm % 100 != 0)); }
  inline int daysInMonth(int mParm, int yParm) {
    switch (mParm) {
      case 1: return 31; case 2: return isLeap(yParm) ? 29 : 28; case 3: return 31; case 4: return 30;
      case 5: return 31; case 6: return 30; case 7: return 31; case 8: return 31;
      case 9: return 30; case 10: return 31; case 11: return 30; case 12: return 31;
      default: return 0;
    }
  }
} // namespace

std::string HelperFunctions::trim(const std::string& sParm) {
  return rtrim(ltrim(sParm));
}

std::string HelperFunctions::toLower(std::string sParm) {
  for (char& c : sParm) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  return sParm;
}

std::string HelperFunctions::promptLine(const std::string& promptParm) {
  std::cout << promptParm;
  std::string sLine;
  std::getline(std::cin >> std::ws, sLine);
  return sLine;
}

bool HelperFunctions::isValidDateString(const std::string& sParm) {
  if (sParm.size() != 10) return false;
  if (sParm[2] != '-' || sParm[5] != '-') return false;
  if (!allDigits(sParm, 0, 2) || !allDigits(sParm, 3, 2) || !allDigits(sParm, 6, 4)) return false;
  int dd = std::stoi(sParm.substr(0, 2));
  int mm = std::stoi(sParm.substr(3, 2));
  int yy = std::stoi(sParm.substr(6, 4));
  if (yy < 1900 || yy > 3000) return false;
  if (mm < 1 || mm > 12) return false;
  int dim = daysInMonth(mm, yy);
  if (dd < 1 || dd > dim) return false;
  return true;
}

std::string HelperFunctions::normalizeGender(const std::string& sParm) {
  auto v = toLower(trim(sParm));
  if (v == "m" || v == "male") return "Male";
  if (v == "f" || v == "female") return "Female";
  return "";
}