#include "fintech/money.hpp"
#include "fintech/journal.hpp"
#include <cassert>
#include <limits>
int main(){using namespace fintech;auto a=Money::create(1000,"KES");auto b=Money::create(1000,"KES");assert(a&&b);auto sum=a->add(*b);assert(sum&&sum->minor()==2000);auto max=Money::create(std::numeric_limits<long long>::max(),"KES");auto one=Money::create(1,"KES");assert(max&&one&&!max->add(*one));Journal j{"j",{{"1","cash",*a,Side::debit},{"2","wallet",*a,Side::credit}}};assert(validate(j));}
