#pragma once
#include <string>
#include <optional>

struct EmployeeSummary {
    std::string name;
    std::string id;
    std::string gender;
    std::string type;
    std::string status;
    std::string dob;
    std::string doj;
    std::string dol; // "-" if not applicable

    std::optional<int> totalLeaves;
    std::optional<int> availedLeaves;

    std::optional<std::string> agency;
    std::optional<std::string> college;
    std::optional<std::string> branch;
};