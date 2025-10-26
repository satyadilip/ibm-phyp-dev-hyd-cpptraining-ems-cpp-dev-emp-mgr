#include "TablePrinter.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <optional>
#include "Enums.h"

static constexpr int WTotalLeaves   = WTotLeaves;
static constexpr int WAvailedLeaves = WAvailed;

static inline std::vector<std::string> sWrapToWidth(const std::string& textParm, size_t widthParm) {
    std::vector<std::string> sLines;
    if (widthParm == 0) return sLines;
    if (textParm.empty()) { sLines.emplace_back(""); return sLines; }
    std::istringstream sIss(textParm);
    std::string sWord, sLine;
    auto sFlushLine = [&](bool forceEmpty = false) {
        if (!sLine.empty() || forceEmpty) { sLines.push_back(sLine); sLine.clear(); }
    };
    while (sIss >> sWord) {
        if (sWord.size() > widthParm) {
            if (!sLine.empty()) sFlushLine();
            size_t sPos = 0;
            while (sPos < sWord.size()) {
                size_t sLen = std::min(widthParm, sWord.size() - sPos);
                sLines.push_back(sWord.substr(sPos, sLen));
                sPos += sLen;
            }
            continue;
        }
        if (sLine.empty()) {
            sLine = sWord;
        } else if (sLine.size() + 1 + sWord.size() <= widthParm) {
            sLine.push_back(' ');
            sLine += sWord;
        } else {
            sFlushLine();
            sLine = sWord;
        }
    }
    sFlushLine(true);
    return sLines;
}

void TablePrinter::print(const std::vector<EmployeeSummary> &rowsParm, const std::string &titleParm)
{
    using std::left;
    using std::setw;

    std::cout << "\n--- " << titleParm << " ---\n";
    if (rowsParm.empty()) {
        std::cout << "No records found.\n";
        return;
    }

    const int wName = WName, wId = WId, wGender = WGender, wType = WType, wStatus = WStatus;
    const int wDob = WDob, wDoj = WDoj, wDol = WDol, wTotLeaves = WTotLeaves, wAvailed = WAvailed, wAgency = WAgency, wCollege = WCollege, wBranch = WBranch;

    auto sep = [&]() {
        std::cout
            << "+" << std::string(wName, '-') 
            << "+" << std::string(wId, '-') 
            << "+" << std::string(wGender, '-') 
            << "+" << std::string(wType, '-') 
            << "+" << std::string(wStatus, '-') 
            << "+" << std::string(wDob, '-') 
            << "+" << std::string(wDoj, '-') 
            << "+" << std::string(wDol, '-') 
            << "+" << std::string(wTotLeaves, '-') 
            << "+" << std::string(wAvailed, '-') 
            << "+" << std::string(wAgency, '-') 
            << "+" << std::string(wCollege, '-') 
            << "+" << std::string(wBranch, '-') 
            << "+\n";
    };

    sep();
    std::cout << "|"
              << left << setw(wName)     << "Name"           << "|"
              << left << setw(wId)       << "ID"             << "|"
              << left << setw(wGender)   << "Gender"         << "|"
              << left << setw(wType)     << "Type"           << "|"
              << left << setw(wStatus)   << "Status"         << "|"
              << left << setw(wDob)      << "DOB"            << "|"
              << left << setw(wDoj)      << "DOJ"            << "|"
              << left << setw(wDol)      << "DOL"            << "|"
              << left << setw(wTotLeaves) << "Total Leaves"  << "|"
              << left << setw(wAvailed)  << "Availed Leaves" << "|"
              << left << setw(wAgency)   << "Agency Name"    << "|"
              << left << setw(wCollege)  << "College"        << "|"
              << left << setw(wBranch)   << "Branch"         << "|\n";
    sep();

    for (const auto &sRow : rowsParm)
    {
        std::vector<std::string> sNameLines = sWrapToWidth(sRow.name, WName);
        if (sNameLines.empty()) sNameLines.emplace_back("");
        const size_t sRowHeight = sNameLines.size();

        for (size_t sL = 0; sL < sRowHeight; ++sL)
        {
            const bool sFirstLine = (sL == 0);
            const std::string& sNamePart = sNameLines[sL];
            const std::string sTotLeavesStr = sFirstLine
                                              ? (sRow.totalLeaves.has_value() ? std::to_string(*sRow.totalLeaves) : std::string("-"))
                                              : std::string("");
            const std::string sAvailedStr   = sFirstLine
                                              ? (sRow.availedLeaves.has_value() ? std::to_string(*sRow.availedLeaves) : std::string("-"))
                                              : std::string("");

        
            const std::string sAgencyStr  = sFirstLine ? sRow.agency.value_or(std::string("-"))  : std::string("");
            const std::string sCollegeStr = sFirstLine ? sRow.college.value_or(std::string("-")) : std::string("");
            const std::string sBranchStr  = sFirstLine ? sRow.branch.value_or(std::string("-"))  : std::string("");

            std::cout << "|"
                      << std::left << std::setw(WName)          << sNamePart                  << "|"
                      << std::left << std::setw(WId)            << (sFirstLine ? sRow.id : "")       << "|"
                      << std::left << std::setw(WGender)        << (sFirstLine ? sRow.gender : "")   << "|"
                      << std::left << std::setw(WType)          << (sFirstLine ? sRow.type : "")     << "|"
                      << std::left << std::setw(WStatus)        << (sFirstLine ? sRow.status : "")   << "|"
                      << std::left << std::setw(WDob)           << (sFirstLine ? sRow.dob : "")      << "|"
                      << std::left << std::setw(WDoj)           << (sFirstLine ? sRow.doj : "")      << "|"
                      << std::left << std::setw(WDol)           << (sFirstLine ? sRow.dol : "")      << "|"
                      << std::left << std::setw(WTotalLeaves)   << sTotLeavesStr                     << "|"
                      << std::left << std::setw(WAvailedLeaves) << sAvailedStr                       << "|"
                      << std::left << std::setw(WAgency)        << sAgencyStr                        << "|"
                      << std::left << std::setw(WCollege)       << sCollegeStr                       << "|"
                      << std::left << std::setw(WBranch)        << sBranchStr                        << "|\n";
        }

        std::cout << "+"
                  << std::string(WName, '-')          << "+"
                  << std::string(WId, '-')            << "+"
                  << std::string(WGender, '-')        << "+"
                  << std::string(WType, '-')          << "+"
                  << std::string(WStatus, '-')        << "+"
                  << std::string(WDob, '-')           << "+"
                  << std::string(WDoj, '-')           << "+"
                  << std::string(WDol, '-')           << "+"
                  << std::string(WTotalLeaves, '-')   << "+"
                  << std::string(WAvailedLeaves, '-') << "+"
                  << std::string(WAgency, '-')        << "+"
                  << std::string(WCollege, '-')       << "+"
                  << std::string(WBranch, '-')        << "+\n";
    }
}