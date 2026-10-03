# Security

## Threat model
moltest runs inside a developer's or CI's test binary, with that user's
privileges. It handles no network input and no secrets. Relevant risks:
- Untrusted command-line arguments and environment (`NO_COLOR`, `TEMP`) parsed by the runner.
- Temporary files and directories created by fixture helpers.
- Fake programs and their `.spec` files written and read by fixture helpers.
- Plugins: an in-process reporter runs with full trust inside the test binary.

## Rules
- Every buffer write is bounded and its truncation checked (`snprintf` results).
- Temporary names come from `mkdtemp`/`mkstemp` (`_mktemp_s` on Windows), never a predictable path.
- No `system()` or shell in the runner.
- Plugins are code you link: installing one is trusting it, same as any `[dev-deps]` entry.

## Per-feature checklist
- [ ] Input from argv/env/files is length-checked and validated
- [ ] No new fixed-size buffer without a truncation check
- [ ] Temp files created atomically, in the platform temp dir
- [ ] No sensitive data written to output or logs
- [ ] Plugin-facing API: no pointer handed out that outlives its owner
