#include "fintech/money.hpp"
#include <limits>
#include <utility>
namespace fintech {
std::expected<Money,MoneyError> Money::create(std::int64_t v,std::string_view c){if(c.size()!=3)return std::unexpected(MoneyError::invalid_currency);for(char x:c)if(x<'A'||x>'Z')return std::unexpected(MoneyError::invalid_currency);return Money{v,std::string{c}};}
std::expected<Money,MoneyError> Money::add(const Money&o)const noexcept{if(currency_!=o.currency_)return std::unexpected(MoneyError::currency_mismatch);if((o.minor_>0&&minor_>std::numeric_limits<std::int64_t>::max()-o.minor_)||(o.minor_<0&&minor_<std::numeric_limits<std::int64_t>::min()-o.minor_))return std::unexpected(MoneyError::overflow);return Money{minor_+o.minor_,currency_};}
std::expected<Money,MoneyError> Money::negate()const noexcept{if(minor_==std::numeric_limits<std::int64_t>::min())return std::unexpected(MoneyError::overflow);return Money{-minor_,currency_};}
}
