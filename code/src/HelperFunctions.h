#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "Enums.h"
#include <string>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cstdio>

/**
 * @class HelperFunctions
 * @brief Utility class providing static helper methods for the application.
 */
class HelperFunctions
{
public:
  /**
   * @brief Prints a formatted menu to the console.
   * @param titleParm Title of the menu.
   * @param optionsParm Array of menu option strings.
   * @param numOptionsParm Number of options.
   * @param exitCodeParm Integer code to exit or go back.
   */
  static void printMenu(const std::string &titleParm, const char *optionsParm[], int numOptionsParm, int exitCodeParm)
  {
    size_t maxLen = 0;
    std::string titleLine = "       " + titleParm;
    if (titleLine.length() > maxLen)
      maxLen = titleLine.length();

    for (int i = 0; i < numOptionsParm; ++i)
    {
      std::string optionLine = "       " + std::to_string(i + 1) + ". " + optionsParm[i];
      if (optionLine.length() > maxLen)
        maxLen = optionLine.length();
    }

    // Change only the printed exit/go-back hint. Do not change any input logic.
    // For main menu (exitCodeParm == ExitMainMenu), show -1 as the displayed code.
    int displayExitCode = (exitCodeParm == ExitMainMenu) ? -1 : exitCodeParm;
    std::string exitMsg = "Press " + std::to_string(displayExitCode) +
                          ((exitCodeParm == ExitMainMenu) ? " to Exit" : " to go back to previous menu");
    std::string exitLine = "         " + exitMsg;

    if (exitLine.length() > maxLen)
      maxLen = exitLine.length();

    size_t totalWidth = maxLen + 2;

    std::cout << std::string(totalWidth, '-') << "\n";
    std::cout << "|" << titleLine << std::string(totalWidth - 1 - titleLine.length(), ' ') << "|\n";
    std::cout << std::string(totalWidth, '-') << "\n";

    for (int i = 0; i < numOptionsParm; ++i)
    {
      std::string optionLine = "       " + std::to_string(i + 1) + ". " + optionsParm[i];
      std::cout << "|" << optionLine << std::string(totalWidth - 1 - optionLine.length(), ' ') << "|\n";
    }

    std::cout << "|" << exitLine << std::string(totalWidth - 1 - exitLine.length(), ' ') << "|\n";
    std::cout << std::string(totalWidth, '-') << "\n";
  }

  /**
   * @brief Clears the standard input buffer to handle invalid input.
   */
  static void clearInputBuffer()
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  /**
   * @brief Gets a random employee name.
   * @return Random name string.
   */
  static std::string getRandomName(std::string genderParm)
  {
    static const char *sMaleNames[] = {"Bahubali", "Kattappa", "Ballaldeva", "KumaraVarma", "PushpaRaj"};
    static const char *sFemaleNames[] = {"Devasena", "Avantika", "Sivagami", "Srivalli", "Sita"};
    int sIndex = std::rand() % MaxNamesInPool;
    if (genderParm == "Male")
    {
      return sMaleNames[sIndex];
    }
    else
    {
      return sFemaleNames[sIndex];
    }
  }

  /**
   * @brief Gets a random gender.
   * @return "Male" or "Female".
   */
  static std::string getRandomGender()
  {
    return (std::rand() % 2 == 0) ? "Male" : "Female";
  }

  /**
   * @brief Gets a random date string in DD-MM-YYYY format.
   * @return Random date string.
   */
  static std::string getRandomDate()
  {
    int sDay = 1 + std::rand() % 28;
    int sMonth = 1 + std::rand() % 12;
    int sYear = 1990 + std::rand() % 30;
    char sDate[11];
    std::snprintf(sDate, sizeof(sDate), "%02d-%02d-%04d", sDay, sMonth, sYear);
    return std::string(sDate);
  }

  /**
   * @brief Gets a random employee status.
   * @return EmployeeStatus enum value.
   */
  static EmployeeStatus getRandomStatus()
  {
    int sRand = std::rand() % MaxEmployeeStatuses;
    return static_cast<EmployeeStatus>(sRand);
  }

  /**
   * @brief Gets a random employee type.
   * @return EmployeeType enum value.
   */
  static EmployeeType getRandomType()
  {
    int sRand = std::rand() % MaxEmployeeTypes;
    return static_cast<EmployeeType>(sRand);
  }

  /**
   * @brief Gets a name from user input.
   * @return Name string.
   */
  static std::string getInputName()
  {
    std::string sName;
    std::cout << "Enter Name: ";
    std::cin.ignore();
    std::getline(std::cin, sName);
    return sName;
  }

  /**
   * @brief Gets a gender from user input.
   * @return Gender string.
   */
  static std::string getInputGender()
  {
    std::string sGender;
    std::cout << "Enter Gender (Male/Female): ";
    std::cin >> sGender;
    return sGender;
  }

  /**
   * @brief Gets a date from user input.
   * @param promptParm Prompt to display.
   * @return Date string.
   */
  static std::string getInputDate(const std::string &promptParm)
  {
    std::string sDate;
    std::cout << "Enter " << promptParm << " (DD-MM-YYYY): ";
    std::cin >> sDate;
    return sDate;
  }

  /**
   * @brief Computes date of leaving based on type and joining date.
   * @param typeParm EmployeeType.
   * @param dojParm Date of joining.
   * @return Date of leaving string.
   */
  static std::string computeDateOfLeaving(EmployeeType typeParm, const std::string &dojParm)
  {
    if (typeParm == Contractor)
    {
      // Simple logic: Contractors leave 1-3 years after joining
      int sYear = std::stoi(dojParm.substr(6, 4)) + 1 + (std::rand() % 3);
      return dojParm.substr(0, 6) + std::to_string(sYear);
    }
    else if (typeParm == Intern)
    {
      // Interns leave 6 months to 1 year after joining
      int sMonth = std::stoi(dojParm.substr(3, 2)) + 6 + (std::rand() % 7);
      int sYear = std::stoi(dojParm.substr(6, 4));
      if (sMonth > 12)
      {
        sMonth -= 12;
        sYear += 1;
      }
      char sDate[11];
      std::sprintf(sDate, "%02d-%02d-%04d", std::stoi(dojParm.substr(0, 2)), sMonth, sYear);
      return std::string(sDate);
    }
    // Full-time employees do not have a predefined leaving date
    return getRandomDate();
  }

  // Conversion functions (add comments as above)
  static std::string convertTypeToString(EmployeeType typeParm)
  {
    switch (typeParm)
    {
    case FullTime:
      return "Full-Time";
    case Contractor:
      return "Contractor";
    case Intern:
      return "Intern";
    default:
      return "Unknown";
    }
  }
  static std::string convertStatusToString(EmployeeStatus statusParm)
  {
    switch (statusParm)
    {
    case Active:
      return "Active";
    case Inactive:
      return "Inactive";
    case Resigned:
      return "Resigned";
    default:
      return "Unknown";
    }
  }
  static std::string convertAgencyToString(Agency agencyParm)
  {
    switch (agencyParm)
    {
    case Avengers:
      return "Avengers";
    case JusticeLeague:
      return "Justice League";
    case XMen:
      return "X-Men";
    default:
      return "Unknown";
    }
  }
  static std::string convertCollegeToString(College collegeParm)
  {
    switch (collegeParm)
    {
    case IITDelhi:
      return "IIT Delhi";
    case IITMumbai:
      return "IIT Mumbai";
    case IITKanpur:
      return "IIT Kanpur";
    case IITHyderabad:
      return "IIT Hyderabad";
    case NITWarangal:
      return "NIT Warangal";
    case NITTiruchi:
      return "NIT Tiruchi";
    case IIITHyderabad:
      return "IIIT Hyderabad";
    default:
      return "Unknown";
    }
  }
  static std::string convertBranchToString(Branch branchParm)
  {
    switch (branchParm)
    {
    case CSE:
      return "CSE";
    case CSIT:
      return "CSIT";
    case ECE:
      return "ECE";
    default:
      return "Unknown";
    }
  }
};

#endif // HELPER_FUNCTIONS_H
