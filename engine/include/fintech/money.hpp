#pragma once
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
namespace fintech {
enum class MoneyError{invalid_currency,currency_mismatch,overflow};
class Money final{
public:
 static std::expected<Money,MoneyError> create(std::int64_t,std::string_view);
 [[nodiscard]] std::int64_t minor()const noexcept{return minor_;}
 [[nodiscard]] const std::string& currency()const noexcept{return currency_;}
 [[nodiscard]] std::expected<Money,MoneyError> add(const Money&)const noexcept;
 [[nodiscard]] std::expected<Money,MoneyError> negate()const noexcept;
private:
 Money(std::int64_t v,std::string c):minor_(v),currency_(std::move(c)){}
 std::int64_t minor_;std::string currency_;
};
}
