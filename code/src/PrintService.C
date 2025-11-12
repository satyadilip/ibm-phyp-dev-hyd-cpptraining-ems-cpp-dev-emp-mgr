#include "PrintService.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

static constexpr int WTotalLeavesAlias   = WTotLeaves;
static constexpr int WAvailedLeavesAlias = WAvailed;

/**
 * @brief Prints a titled section header with dividers.
 * @param titleTextParm Text of the title line.
 */
void PrintService::printTitle(const std::string& titleTextParm) {
    printDivider('=');
    std::cout << titleTextParm << '\n';
    printDivider('=');
}

/**
 * @brief Prints a horizontal divider line of fixed width.
 * @param fillCharParm Character used to fill the divider.
 */
void PrintService::printDivider(char fillCharParm) {
    std::cout << pRepeat(fillCharParm, DividerWidth) << '\n';
}

/**
 * @brief Prints a blank line.
 */
void PrintService::printBlankLine() {
    std::cout << '\n';
}

/**
 * @brief Prints an informational message.
 * @param messageParm Message text.
 */
void PrintService::printInfo(const std::string& messageParm) {
    std::cout << messageParm << '\n';
}

/**
 * @brief Prints an error message.
 * @param messageParm Message text.
 */
void PrintService::printError(const std::string& messageParm) {
    std::cout << messageParm << '\n';
}

/**
 * @brief Prints key/value string pair.
 * @param keyParm Label text.
 * @param valueParm Value text.
 */
void PrintService::printKeyValue(const std::string& keyParm, const std::string& valueParm) {
    std::cout << std::left << std::setw(20) << (keyParm + " : ") << valueParm << '\n';
}

/**
 * @brief Overload: prints key/value integer pair.
 */
void PrintService::printKeyValue(const std::string& keyParm, int valueParm) {
    std::cout << std::left << std::setw(20) << (keyParm + " : ") << valueParm << '\n';
}

/**
 * @brief Overload: prints key/value long pair.
 */
void PrintService::printKeyValue(const std::string& keyParm, long valueParm) {
    std::cout << std::left << std::setw(20) << (keyParm + " : ") << valueParm << '\n';
}

/**
 * @brief Renders a menu box with numbered options and exit/back instruction.
 * @param titleParm Menu title.
 * @param optionsParm Array of option labels.
 * @param optionCountParm Count of options in array.
 * @param exitCodeParm Exit/back code displayed.
 * @param contextParm Distinguishes root vs submenu wording.
 */
void PrintService::printMenu(const std::string& titleParm,
                             const char* optionsParm[],
                             int optionCountParm,
                             int exitCodeParm,
                             MenuContext contextParm)
{
    size_t sMaxLen = 0;
    std::string sTitleLine = "       " + titleParm;
    sMaxLen = std::max(sMaxLen, sTitleLine.length());
    for (int sI = 0; sI < optionCountParm; ++sI) {
        std::string sOpt = "       " + std::to_string(sI + 1) + ". " + optionsParm[sI];
        sMaxLen = std::max(sMaxLen, sOpt.length());
    }
    std::string sExitMsg = "Press " + std::to_string(exitCodeParm) +
        ((contextParm == RootMenuContext) ? " to Exit" : " to go back to previous menu");
    std::string sExitLine = "         " + sExitMsg;
    sMaxLen = std::max(sMaxLen, sExitLine.length());

    size_t sWidth = sMaxLen + 2;
    std::cout << std::string(sWidth, '-') << "\n";
    std::cout << "|" << sTitleLine << std::string(sWidth - 1 - sTitleLine.length(), ' ') << "|\n";
    std::cout << std::string(sWidth, '-') << "\n";
    for (int sI = 0; sI < optionCountParm; ++sI) {
        std::string sOpt = "       " + std::to_string(sI + 1) + ". " + optionsParm[sI];
        std::cout << "|" << sOpt << std::string(sWidth - 1 - sOpt.length(), ' ') << "|\n";
    }
    std::cout << "|" << sExitLine << std::string(sWidth - 1 - sExitLine.length(), ' ') << "|\n";
    std::cout << std::string(sWidth, '-') << "\n";
}

/**
 * @brief Wraps a text string into lines <= width.
 * @param textParm Source text.
 * @param widthParm Maximum line width.
 * @return std::vector<std::string> Wrapped lines.
 */
std::vector<std::string> PrintService::pWrapToWidth(const std::string& textParm, std::size_t widthParm) {
    std::vector<std::string> sLines;
    if (widthParm == 0) return sLines;
    if (textParm.empty()) { sLines.emplace_back(""); return sLines; }
    std::istringstream sIss(textParm);
    std::string sWord, sLine;
    auto sFlushLine = [&](bool sForceEmpty = false) {
        if (!sLine.empty() || sForceEmpty) { sLines.push_back(sLine); sLine.clear(); }
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

/**
 * @brief Prints tabular employee summaries.
 * @param rowsParm Vector of summary rows.
 * @param tableTitleParm Table caption.
 */
void PrintService::printEmployeeSummaryTable(const std::vector<EmployeeSummary>& rowsParm,
                                             const std::string& tableTitleParm)
{
    using std::left;
    using std::setw;

    std::cout << "\n--- " << tableTitleParm << " ---\n";
    if (rowsParm.empty()) {
        std::cout << "No records found.\n";
        return;
    }

    const int sWName = WName, sWId = WId, sWGender = WGender, sWType = WType, sWStatus = WStatus;
    const int sWDob = WDob, sWDoj = WDoj, sWDol = WDol, sWTotLeaves = WTotalLeavesAlias, sWAvailed = WAvailedLeavesAlias;
    const int sWAgency = WAgency, sWCollege = WCollege, sWBranch = WBranch;

    auto sSep = [&]() {
        std::cout
            << "+" << std::string(sWName, '-') 
            << "+" << std::string(sWId, '-') 
            << "+" << std::string(sWGender, '-') 
            << "+" << std::string(sWType, '-') 
            << "+" << std::string(sWStatus, '-') 
            << "+" << std::string(sWDob, '-') 
            << "+" << std::string(sWDoj, '-') 
            << "+" << std::string(sWDol, '-') 
            << "+" << std::string(sWTotLeaves, '-') 
            << "+" << std::string(sWAvailed, '-') 
            << "+" << std::string(sWAgency, '-') 
            << "+" << std::string(sWCollege, '-') 
            << "+" << std::string(sWBranch, '-') 
            << "+\n";
    };

    sSep();
    std::cout << "|"
        << left << setw(sWName)    << "Name"           << "|"
        << left << setw(sWId)      << "ID"             << "|"
        << left << setw(sWGender)  << "Gender"         << "|"
        << left << setw(sWType)    << "Type"           << "|"
        << left << setw(sWStatus)  << "Status"         << "|"
        << left << setw(sWDob)     << "DOB"            << "|"
        << left << setw(sWDoj)     << "DOJ"            << "|"
        << left << setw(sWDol)     << "DOL"            << "|"
        << left << setw(sWTotLeaves) << "Total Leaves" << "|"
        << left << setw(sWAvailed) << "Availed Leaves" << "|"
        << left << setw(sWAgency)  << "Agency Name"    << "|"
        << left << setw(sWCollege) << "College"        << "|"
        << left << setw(sWBranch)  << "Branch"         << "|\n";
    sSep();

    for (const auto& sRow : rowsParm) {
        std::vector<std::string> sNameLines = pWrapToWidth(sRow.name, WName);
        if (sNameLines.empty()) sNameLines.emplace_back("");
        size_t sRowHeight = sNameLines.size();

        for (size_t sL = 0; sL < sRowHeight; ++sL) {
            bool sFirstLine = (sL == 0);
            const std::string& sNamePart = sNameLines[sL];

            std::string sTotLeavesStr = sFirstLine
              ? (sRow.totalLeaves.has_value() ? std::to_string(*sRow.totalLeaves) : std::string("-"))
              : std::string("");
            std::string sAvailedStr = sFirstLine
              ? (sRow.availedLeaves.has_value() ? std::to_string(*sRow.availedLeaves) : std::string("-"))
              : std::string("");

            std::string sAgencyStr  = sFirstLine ? sRow.agency.value_or(std::string("-"))  : std::string("");
            std::string sCollegeStr = sFirstLine ? sRow.college.value_or(std::string("-")) : std::string("");
            std::string sBranchStr  = sFirstLine ? sRow.branch.value_or(std::string("-"))  : std::string("");

            std::cout << "|"
                << left << setw(WName)       << sNamePart                        << "|"
                << left << setw(WId)         << (sFirstLine ? sRow.id : "")      << "|"
                << left << setw(WGender)     << (sFirstLine ? sRow.gender : "")  << "|"
                << left << setw(WType)       << (sFirstLine ? sRow.type : "")    << "|"
                << left << setw(WStatus)     << (sFirstLine ? sRow.status : "")  << "|"
                << left << setw(WDob)        << (sFirstLine ? sRow.dob : "")     << "|"
                << left << setw(WDoj)        << (sFirstLine ? sRow.doj : "")     << "|"
                << left << setw(WDol)        << (sFirstLine ? sRow.dol : "")     << "|"
                << left << setw(sWTotLeaves) << sTotLeavesStr                    << "|"
                << left << setw(sWAvailed)   << sAvailedStr                      << "|"
                << left << setw(WAgency)     << sAgencyStr                       << "|"
                << left << setw(WCollege)    << sCollegeStr                      << "|"
                << left << setw(WBranch)     << sBranchStr                       << "|\n";
        }

        std::cout << "+"
            << std::string(WName, '-')    << "+"
            << std::string(WId, '-')      << "+"
            << std::string(WGender, '-')  << "+"
            << std::string(WType, '-')    << "+"
            << std::string(WStatus, '-')  << "+"
            << std::string(WDob, '-')     << "+"
            << std::string(WDoj, '-')     << "+"
            << std::string(WDol, '-')     << "+"
            << std::string(sWTotLeaves, '-') << "+"
            << std::string(sWAvailed, '-') << "+"
            << std::string(WAgency, '-')  << "+"
            << std::string(WCollege, '-') << "+"
            << std::string(WBranch, '-')  << "+\n";
    }
}

/**
 * @brief Returns repeated character string.
 * @param chParm Character to repeat.
 * @param countParm Number of repetitions.
 */
std::string PrintService::pRepeat(char chParm, std::size_t countParm) {
    return std::string(countParm, chParm);
}