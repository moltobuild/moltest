# moltest
A small unit-testing framework for C and C++, in the spirit of pytest. It is
the official tester of the Molto ecosystem but optional: nothing in molto
depends on it, projects add it with `molto add moltest --dev`, and it works
without molto too. Its reporter API is open so the community can ship plugins
(`moltest-coverage`, `moltest-junit`, ...) as separate packages.

## Current focus
Milestone: M1 - Ready to publish · Spec: specs/001-standalone-package.md · Next step: format the inherited sources with the molto preset

## Docs
[ROADMAP](ROADMAP.md) · [ARCHITECTURE](ARCHITECTURE.md) · [SECURITY](SECURITY.md) ·
[VALIDATION](VALIDATION.md) · [DEVELOPMENT](DEVELOPMENT.md) ·
[DEPENDENCIES](DEPENDENCIES.md) · [PROGRESS](PROGRESS.md) ·
[KNOWN_ISSUES](KNOWN_ISSUES.md) · [specs/](specs/) · [adr/](adr/)
