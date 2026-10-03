# 0002 Plugin model: in-process first, out-of-process events later — Status: Accepted
Date: 2026-10-03

## Context
The community should be able to build plugins such as `moltest-coverage` or
`moltest-junit`. Today `moltest_set_reporter()` accepts one observer with
run/file/test callbacks, no API version and no failure details.

## Decision
Support both models, in order:
1. **In-process (M3, first).** A plugin is a molto package (a C library) that
   registers a `moltest_reporter`. Users add it with `molto add <plugin> --dev`.
   The API gains: several reporters at once, an `api_version` field so old
   plugins are detected rather than misread, and failure details on test end.
   `moltest_set_reporter()` stays as a shim.
2. **Out-of-process (M4).** A built-in reporter writes a versioned JSON Lines
   event stream (`--report=jsonl[:path]`). External tools in any language
   consume it, with no linking and no ABI to match.

## Alternatives considered
- In-process only: easiest, but excludes non-C tooling and gives no isolation.
- Out-of-process only (like molto's frontend plugins): isolated, but heavier for
  simple reporters and cannot observe in-process state such as coverage counters.
- Dynamic loading (`dlopen`) of plugins: platform-specific and a trust problem
  without a gain over linking a `[dev-deps]` package.

## Consequences
- The reporter struct and the event schema become public contracts, versioned
  independently and documented in `docs/Plugins.md`.
- Naming convention for community packages: `moltest-<name>`.
