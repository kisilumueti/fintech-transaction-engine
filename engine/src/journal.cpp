#include "fintech/journal.hpp"
#include <limits>
#include <unordered_map>
#include <unordered_set>
namespace fintech{
std::expected<void,JournalError> validate(const Journal&j){
 if(j.id.empty())return std::unexpected(JournalError::missing_id);
 if(j.lines.size()<2)return std::unexpected(JournalError::too_few_lines);
 std::unordered_set<std::string>ids;std::unordered_map<std::string,std::int64_t>totals;
 for(const auto&l:j.lines){if(l.id.empty()||l.account_id.empty()||l.amount.minor()<=0)return std::unexpected(JournalError::invalid_line);if(!ids.insert(l.id).second)return std::unexpected(JournalError::duplicate_line);auto&v=totals[l.amount.currency()];auto n=l.amount.minor();if(l.side==Side::debit){if(v>std::numeric_limits<std::int64_t>::max()-n)return std::unexpected(JournalError::overflow);v+=n;}else{if(v<std::numeric_limits<std::int64_t>::min()+n)return std::unexpected(JournalError::overflow);v-=n;}}
 for(const auto&[currency,total]:totals){(void)currency;if(total!=0)return std::unexpected(JournalError::unbalanced);}return {};
}
}
