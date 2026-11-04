# Fintech Transaction Engine

A ledger-first financial transaction platform built to demonstrate accounting correctness, deterministic money arithmetic, concurrency-aware design, and operational engineering.

> **Safety notice:** portfolio/reference software only. It is not a licensed payment processor or banking system. Do not use it to hold, route, or move real customer funds.

## Technology
- **Go** — HTTP service foundation and application orchestration.
- **C++23** — deterministic money and journal validation kernel.
- **PostgreSQL** — authoritative financial records and immutable journal.
- **Python** — offline reconciliation tooling.
- **GitHub Actions** — Go, C++, and Python quality gates.

## Implemented foundation
- Integer minor-unit money representation with currency validation and overflow protection.
- Double-entry journal validation, balanced independently per currency.
- Immutable journal-entry database trigger; corrections must use compensating postings.
- PostgreSQL schema for customers, accounts, transactions, journal entries, balance projections, audit events, and transactional outbox.
- Go HTTP service with health endpoints, request IDs, structured logging, timeouts, and graceful process boundaries.
- C++ domain kernel with CMake and regression tests.
- Python CSV reconciliation utility using integer arithmetic.
- CI workflow for Go race tests, C++ build/tests, and Python syntax validation.

## Financial invariants
1. Never use floating-point arithmetic for money.
2. Every posted journal must balance per currency.
3. Posted ledger entries are append-only.
4. Balance projections are rebuildable from the ledger.
5. Account updates and journal postings must share one database transaction.
6. Idempotency must be scoped to the authenticated principal and operation.
7. Redis is never the source of truth for balances.

## Repository layout
```
cmd/api/                         Go HTTP entry point
internal/domain/money/           Go money value object
internal/domain/ledger/          Go journal invariants
internal/httpapi/                HTTP routing and middleware
engine/                          C++ domain kernel
db/migrations/                   PostgreSQL schema
tools/                            Python reconciliation utility
.github/workflows/                CI quality gates
```

## Next milestones
Authentication and authorization, customer/account lifecycle, PostgreSQL repository layer, atomic transfer posting, idempotency middleware, outbox publisher, reconciliation worker, observability, rate limits, API contract, integration tests, and reproducible load testing.

## Build and test
See [docs/development.md](docs/development.md). Performance and 100,000-user capacity claims will only be published after repeatable load tests with documented hardware, workload, latency percentiles, and database configuration.

## License
MIT.
