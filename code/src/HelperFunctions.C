#include "HelperFunctions.h"
#include "PrintService.h"

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
 * @brief Clears cin state and discards remaining line buffer.
 */
void HelperFunctions::clearInputBuffer()
{
  std::cin.clear();
  int sCh = 0;
  while ((sCh = std::cin.get()) != '\n' && sCh != EOF) { /* drain */ }
}

// ---------------- Random data generators ----------------

/**
 * @brief Returns random name based on gender.
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
 * @brief Returns random gender ("Male"/"Female").
 */
std::string HelperFunctions::getRandomGender()
{
  return (std::rand() % 2 == 0) ? "Male" : "Female";
}

/**
 * @brief Returns random generic date (legacy use).
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
 * @brief Picks random employee status uniformly.
 */
EmployeeStatus HelperFunctions::getRandomStatus()
{
  int sRand = std::rand() % MaxEmployeeStatuses;
  return static_cast<EmployeeStatus>(sRand);
}

/**
 * @brief Picks random employee type uniformly.
 */
EmployeeType HelperFunctions::getRandomType()
{
  int sRand = std::rand() % MaxEmployeeTypes;
  return static_cast<EmployeeType>(sRand);
}

// ---------------- User input helpers ----------------

/**
 * @brief Secure menu choice input in range or back code.
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
 * @brief Parses DD-MM-YYYY into d,m,y.
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
 * @brief Compose clamped DD-MM-YYYY string.
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
 * @brief Adds months with year rollover, clamps day.
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
 * @brief Adds years, preserving month/day (clamped).
 */
std::string HelperFunctions::addYears(const std::string &dateParm, int yearsToAdd)
{
  int d, m, y;
  parseDate(dateParm, d, m, y);
  int sNewD = (d > 28 ? 28 : d);
  return makeDate(sNewD, m, y + yearsToAdd);
}

/**
 * @brief Random DOB ensuring adulthood range.
 */
std::string HelperFunctions::getRandomDOB()
{
  int sDay = MinDay + std::rand() % (MaxDay - MinDay + 1);
  int sMonth = MinMonth + std::rand() % (MaxMonth - MinMonth + 1);
  int sYear = MinBirthYear + std::rand() % (MaxBirthYear - MinBirthYear + 1);
  return makeDate(sDay, sMonth, sYear);
}

/**
 * @brief Random DOJ >= DOB + 18 years (+ extra years/months).
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
 * @brief Computes date of leaving based on type rules.
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
 * @brief Converts EmployeeType to readable string.
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
 * @brief Converts EmployeeStatus to readable string.
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
 * @brief Converts Agency enum to readable string.
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
 * @brief Converts College enum to readable string.
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
 * @brief Converts Branch enum to readable string.
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

/**
 * @brief Checks date string format and logical validity.
 */
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

/**
 * @brief Normalizes gender tokens to canonical form.
 */
std::string HelperFunctions::normalizeGender(const std::string& sParm) {
  auto v = toLower(trim(sParm));
  if (v == "m" || v == "male") return "Male";
  if (v == "f" || v == "female") return "Female";
  return "";
}

/**
 * @brief Returns current system date DD-MM-YYYY.
 */
std::string HelperFunctions::getCurrentDate()
{
  std::time_t t = std::time(nullptr);
  std::tm* tm = std::localtime(&t);
  char buf[11];
  std::snprintf(buf, sizeof(buf), "%02d-%02d-%04d",
                tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
  return std::string(buf);
}