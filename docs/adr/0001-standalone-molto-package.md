# 0001 moltest as a standalone molto package — Status: Accepted
Date: 2026-10-03

## Context
moltest lived as a copy in `molto/modules/moltest` and another in
`pickup/modules/moltest`, already diverged (molto's is a superset). It should
be the official tester of the Molto ecosystem, but optional, and open to
community plugins.

## Decision
- Own repository, history split from `molto/modules/moltest` (`git subtree split`).
- Built only with molto (`Project.toml`, no Makefile), C23, `artifact = "static"`.
- Consumed through `molto add moltest --dev` (`[dev-deps]`), never vendored as the intended path.
- Apache-2.0, like molto and pickup.

## Alternatives considered
- Keep a vendored copy per project, synced with `git subtree`: copies drift, as they already did.
- Git submodule: ties consumers to git layout and recursive clones; bypasses the package manager.
- Header-only library: simpler to drop in, but the runner and fake-program support are too large for a header.

## Consequences
- molto and pickup must migrate to the dev-dependency (M2), and their bootstrap Makefiles need an answer.
- moltest gets its own versioning and releases through the molto registry.
