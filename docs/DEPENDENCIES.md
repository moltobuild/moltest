# Dependencies

## Policy
Same as molto:
- **Exact versions only.** No ranges; molto refuses them anyway.
- **Zero runtime dependencies** is the goal: the C standard library and the platform API only.
- **No install or post-install scripts.**
- Any new dependency, of any kind, needs an ADR and the maintainer's approval.
- `Molto.lock` is committed whenever one exists.

## Runtime
None.

## Tooling (not linked)
| Tool | Why |
|---|---|
| molto | build, test, fmt, lint, publish |
| pickup | provides the compiler, formatter and linter molto asks for |
