# Progress

## 2026-10-03 — M0 standalone repository
- Done: split `molto/modules/moltest` history into this repo; Project.toml (static library); self-test suite; docs scaffold; ADRs 0001-0002
- Commit: see `git log`
- Tests: `molto test` 5 passed, 1 skipped; `molto fmt --check` fails on inherited sources; `molto lint` 0 errors, 13 warnings
- Next: M1, format the inherited sources with the molto preset

## 2026-10-03 — recipe.toml
- Done: source recipe so `[dev-deps] moltest = { path = ... }` works; checked with a scratch lib project
- Commit: see `git log`
- Tests: `molto test` passes here; consumer project builds and its moltest suite passes
- Next: publish 0.1.0 to the registry (it reports no package called 'moltest')
