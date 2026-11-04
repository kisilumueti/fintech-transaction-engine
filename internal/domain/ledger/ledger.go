package ledger
import("errors";"fmt";"math";"sort";"github.com/kisilumueti/fintech-transaction-engine/internal/domain/money")
var ErrUnbalanced=errors.New("journal is not balanced")
var ErrInvalidLine=errors.New("invalid journal line")
var ErrDuplicateLine=errors.New("duplicate journal line id")
type Side uint8
const(Debit Side=iota+1;Credit)
type Line struct{ID,AccountID string;Amount money.Money;Side Side;Memo string}
type Journal struct{ID,Reference string;Lines []Line}
func(j Journal)Validate()error{if j.ID==""||len(j.Lines)<2{return fmt.Errorf("%w: journal requires identity and two lines",ErrUnbalanced)};seen:=map[string]bool{};net:=map[string]int64{};for _,line:=range j.Lines{if line.ID==""||line.AccountID==""||line.Amount.Minor()<=0||(line.Side!=Debit&&line.Side!=Credit){return ErrInvalidLine};if seen[line.ID]{return ErrDuplicateLine};seen[line.ID]=true;n:=line.Amount.Minor();c:=line.Amount.Currency();if line.Side==Debit{if net[c]>math.MaxInt64-n{return ErrInvalidLine};net[c]+=n}else{if net[c]<math.MinInt64+n{return ErrInvalidLine};net[c]-=n}};for currency,total:=range net{if total!=0{return fmt.Errorf("%w for %s: net=%d",ErrUnbalanced,currency,total)}};return nil}
func(j Journal)CanonicalLines()[]Line{out:=append([]Line(nil),j.Lines...);sort.Slice(out,func(i,k int)bool{return out[i].ID<out[k].ID});return out}
