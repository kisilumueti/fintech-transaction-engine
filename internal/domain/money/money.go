package money
import("errors";"fmt";"math")
var ErrCurrencyMismatch=errors.New("currency mismatch")
var ErrOverflow=errors.New("money arithmetic overflow")
var ErrInvalidCurrency=errors.New("invalid currency")
type Money struct{minor int64;currency string}
func New(minor int64,currency string)(Money,error){if len(currency)!=3{return Money{},ErrInvalidCurrency};for _,r:=range currency{if r<'A'||r>'Z'{return Money{},ErrInvalidCurrency}};return Money{minor,currency},nil}
func Must(minor int64,currency string)Money{m,e:=New(minor,currency);if e!=nil{panic(e)};return m}
func(m Money)Minor()int64{return m.minor}
func(m Money)Currency()string{return m.currency}
func(m Money)Add(o Money)(Money,error){if m.currency!=o.currency{return Money{},ErrCurrencyMismatch};if(o.minor>0&&m.minor>math.MaxInt64-o.minor)||(o.minor<0&&m.minor<math.MinInt64-o.minor){return Money{},ErrOverflow};return Money{m.minor+o.minor,m.currency},nil}
func(m Money)Negate()(Money,error){if m.minor==math.MinInt64{return Money{},ErrOverflow};return Money{-m.minor,m.currency},nil}
func(m Money)Sub(o Money)(Money,error){if o.minor==math.MinInt64{return Money{},ErrOverflow};return m.Add(Money{-o.minor,o.currency})}
func(m Money)String()string{return fmt.Sprintf("%s:%d",m.currency,m.minor)}
