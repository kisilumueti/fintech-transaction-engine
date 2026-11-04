#pragma once
#include "fintech/money.hpp"
#include <expected>
#include <string>
#include <vector>
namespace fintech{
enum class Side{debit,credit};
struct Line{std::string id,account_id;Money amount;Side side;};
struct Journal{std::string id;std::vector<Line> lines;};
enum class JournalError{missing_id,too_few_lines,invalid_line,duplicate_line,unbalanced,overflow};
std::expected<void,JournalError> validate(const Journal&);
}
