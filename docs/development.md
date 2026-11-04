# Development guide

## Prerequisites
Go 1.23+, CMake 3.20+, a C++23-capable compiler, Python 3.12+, and PostgreSQL 16.

## Go service
```bash
go mod tidy
go test -race ./...
go vet ./...
go run ./cmd/api
```
The initial HTTP foundation exposes /health/live, /health/ready, and /v1.

## C++ domain kernel
```bash
cmake -S engine -B build
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

## Python reconciliation
CSV columns: account_id,currency,side,amount_minor. Amounts are positive integer minor units; side is debit or credit.
```bash
python tools/reconcile.py ledger.csv --json
```

## Security
Never commit secrets. Local credentials must not be reused in production. Production requires TLS, managed secrets, least-privilege database roles, independent security review, and a tested backup/restore process.

## Money representation
Store and exchange amounts as integer minor units and explicit currency codes. Currency exponents must be configured explicitly before parsing display decimals. Never route money through binary floating point.
