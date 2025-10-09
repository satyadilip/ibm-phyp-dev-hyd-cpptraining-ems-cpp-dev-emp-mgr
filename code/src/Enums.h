#ifndef ENUMS_H
#define ENUMS_H

/**
 * @file Enums.h
 * @brief Contains all the enumerations used throughout the Employee Management System.
 * Using enums instead of hardcoded values improves readability and maintainability.
 */

// Represents the type of an employee.
enum EmployeeType {
    FullTime,
    Contractor,
    Intern
};

// Represents the current status of an employee.
enum EmployeeStatus {
    Active,
    Inactive,
    Resigned
};

// Represents the external agencies for contractor employees.
enum Agency {
    Avengers,
    JusticeLeague,
    XMen
};

// Represents the colleges for intern employees.
// Corrected to match the compiler error messages for consistency.
enum College {
    IITDelhi,
    IITMumbai,
    IITKanpur,
    IITHyderabad,
    NITWarangal,
    NITTiruchi,
    IIITHyderabad
};

// Represents the academic branches for intern employees.
enum Branch {
    CSE,
    CSIT,
    ECE
};

// Represents menu options for the main menu
enum MainMenuOptions {
    AddEmployee = 1,
    RemoveEmployee,
    GetEmployeeDetails,
    DoSomethingElse,
    ExitMainMenu = 0
};

enum AddMenuOptions {
    AddRandomEmployee = 1,
    AddSpecificEmployee,
    BackToMainMenu = -1
};

// Represents menu options for the specific employee menu
enum SpecificEmployeeMenuOptions {
    AddFullTimeEmployee = 1,
    AddContractorEmployee,
    AddInternEmployee,
    BackToAddMenu = -1
};

enum SearchMenuOptions {
    SearchById = 1,
    SearchByName,
    BackToMainMenuFromSearch = -1 
};

// Represents menu options for the employee details menu
enum DetailsMenuOptions {
    AllEmployeesSummary = 1,
    SummaryByType,
    SummaryByGender,
    SummaryByStatus,
    DisplayDetailsById,
    BackToMainMenuFromDetails = -1
};

// Represents menu options for the other operations menu
enum OperationsMenuOptions {
    AddLeavesToFullTime = 1,
    ConvertInternToFullTime,
    SearchEmployeeById,    // <-- Renamed to avoid conflict
    SearchEmployeeByName,  // <-- Renamed to avoid conflict
    BackToMainMenuFromOperations = -1
};

// Represents array sizes and limits
enum ArrayLimits {
    MaxNamesInPool = 5,
    MaxAgencies = 3,
    MaxColleges = 7,
    MaxBranches = 3,
    MaxEmployeeTypes = 3,
    MaxEmployeeStatuses = 3,
    MaxMenuOptions = 5,
    MaxMainMenuOptions = 4,
    MaxAddMenuOptions = 2,
    MaxSearchMenuOptions = 2,
    MaxDetailsMenuOptions = 5,
    MaxOperationsMenuOptions = 4
};

// Represents date-related constants
enum DateConstants {
    MinBirthYear = 1980,
    MaxBirthYear = 2000,
    MinMonth = 1,
    MaxMonth = 12,
    MinDay = 1,
    MaxDay = 28,
    ContractorContractYears = 1,
    InternContractMonths = 6,
    DefaultLeavesForConversion = 10
};

// Represents leave policy constants
enum LeavePolicy {
    MaxLeavesPerYear = 22,
    MinLeaves = 0,
    DefaultLeaves = 0
};

// Represents probability weights for random generation
enum RandomWeights {
    ActiveProbability = 7,
    InactiveProbability = 2,
    ResignedProbability = 1,
    TotalProbability = 10
};

// Represents string formatting constants
enum StringFormatting {
    EmployeeIdPrefixLength = 3,
    EmployeeIdNumericLength = 4,
    DateYearLength = 4,
    DateMonthLength = 2,
    DateDayLength = 2,
    DateSeparatorLength = 1,
    TotalDateFormatLength = 10
};

#endif // ENUMS_H

