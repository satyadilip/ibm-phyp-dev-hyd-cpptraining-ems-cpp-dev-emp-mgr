#ifndef PRINT_SERVICE_H
#define PRINT_SERVICE_H

#include <string>
#include <vector>
#include <ostream>
#include "EmployeeSummary.h"
#include "Enums.h"

/**
 * @class PrintService
 * @brief Stateless centralized printing (all to std::cout).
 */
class PrintService {
public:
    // Layout
    static void printTitle(const std::string& titleTextParm);
    static void printDivider(char fillCharParm = '-');
    static void printBlankLine();

    // Messages
    static void printInfo(const std::string& messageParm);
    static void printError(const std::string& messageParm);

    // Key-Value
    static void printKeyValue(const std::string& keyParm, const std::string& valueParm);
    static void printKeyValue(const std::string& keyParm, int valueParm);
    static void printKeyValue(const std::string& keyParm, long valueParm);

    // Menus
    static void printMenu(const std::string& titleParm,
                          const char* optionsParm[],
                          int optionCountParm,
                          int exitCodeParm,
                          MenuContext contextParm);

    // Tables
    static void printEmployeeSummaryTable(const std::vector<EmployeeSummary>& rowsParm,
                                          const std::string& tableTitleParm);

private:
    enum PrintServiceConstants { DividerWidth = 64 };
    static std::string pRepeat(char chParm, std::size_t countParm);
    static std::vector<std::string> pWrapToWidth(const std::string& textParm, std::size_t widthParm);
};

#endif // PRINT_SERVICE_H