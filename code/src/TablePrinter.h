#pragma once
#include "EmployeeSummary.h"
#include <vector>
#include <string>

class TablePrinter {
public:
    static void print(const std::vector<EmployeeSummary>& rows, const std::string& title);
};