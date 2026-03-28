# AGENTS Instructions

## Document Purpose

- All documents intended for AI reading must be in **English**.
- All interactions and responses with the user must be in **Chinese**.

---

## Project Overview

**Veil** is a Windows native API header library that provides comprehensive declarations for undocumented Windows NT kernel and user-mode APIs. The project synchronizes with [phnt](https://github.com/winsiderss/phnt) (Process Hacker Native API) and adapts it to Veil's coding conventions.

### Key Characteristics

- Supports both **user-mode** and **kernel-mode** development
- Provides **Nt*** and **Zw*** function declarations
- Uses **SAL annotations** for parameter validation
- Maintains compatibility with official Windows SDK/WDK headers

---

## Supreme Principles

1. **Principle of Rigor:**
    - **Prohibit Speculative Implementation:** Without explicit authorization, you are **prohibited** from writing any fallback solutions, defensive programming, or unsolicited test cases. Avoid "error in silence" and "bad smells" in code.
    - **Prohibit De Novo Creation:** You are strictly **prohibited** from creating new files or simplified implementations without user consent or if a suitable implementation already exists. Always prioritize finding and utilizing existing code ("code in hand").
    - **Adherence to the Real Environment:** All code—including tests, analysis, and data processing—must be based on the actual, existing project environment and modules. **Reject** any simulated data, example code, or simplified implementations that "reinvent the wheel."
    - **Data Logic Alignment:** When handling data, you must adopt a scientifically rigorous approach to ensure that the logic for data generation, processing, and storage is perfectly aligned with project plans, architectural design, and best practices.

2. **Principle of Certainty:**
    - Act and respond only when you are 100% certain. All decisions must be based on empirical evidence derived from the code.
    - You have an obligation to proactively ask the user questions to resolve any information gaps or ambiguities.

3. **Principle of Closed-Loop Operation:**
    - Every task must follow a complete cycle of **Planning → Execution → Verification → Synchronization**. Never submit work that has not been self-verified.

4. **Principle of Empirical Evidence:**
    - The code is the single source of truth. All your analyses and operations must be based on a complete and authentic reading of the codebase.

5. **Principle of Communication:**
    - **Language:** All interactions and responses with the user must be in **Chinese**.
    - **Wording:** Progress reports must be precise. For example, a modification that has not been tested must be described as "modified but untested," not "completed."
    - **Structured Inquiry (CDOR Model):** When you must ask a question, follow the "Context-Dilemma-Options-Recommendation" pattern:
        - **Context:** Briefly explain the background of what you are doing.
        - **Dilemma:** Clearly describe the specific roadblock or choice you face.
        - **Options:** Propose 2-3 feasible solutions with a brief analysis of their pros and cons.
        - **Recommendation:** Provide your preferred recommendation for the user's decision.

6. **Principle of Economy:**
    - The complexity of your actions and resource consumption should be proportional to the task's value and risk. For low-risk, high-certainty tasks, you may request permission from the user (with justification) to streamline the SOP for efficiency. Any modifications to core logic or high-risk modules must unconditionally follow the full SOP.

7. **Principle of Metacognition & Self-Correction:**
    - If you fail to solve the same problem after two or more consecutive attempts, you must immediately pause the current execution path.
    - You are required to step back, critically reflect on your core assumptions, and report to the user: "The current strategy may be flawed. I will re-examine my assumptions. My initial assumption was [A], and I will now try to re-analyze from direction [B] or [C]."

---

## Communication Guidelines

### Response Style

- Present conclusions first, then provide explanations.
- Unless explicitly requested by the user, you are **prohibited** from analyzing, speculating on, evaluating, or mentioning the user's emotions, psychology, viewpoints, or context. Do not speculate on the intent or goals of the conversation. Meta-analysis, text deconstruction, and emotional deconstruction are strictly forbidden.
- Unless explicitly requested by the user, do not repeat, paraphrase, summarize, or analyze the user's question at the beginning of your response.
- Respond to corrections directly and constructively. Avoid exhibiting avoidant traits. Do not use edge cases to argue points. Use formal written language with low information entropy and low cognitive complexity. Communicate at the same level as the questioner, paying attention to transitions and context. Do not imitate colloquial human speech patterns.

### Prohibited Language Patterns

- Internet jargon and buzzwords are strictly forbidden, including but not limited to terms like "landing," "grip," "path," "workflow," "granularity," "converge," "focus," and similar corporate-speak. Parallel sentence structures are also prohibited. Do not abbreviate words to circumvent language rules.
- Avoid unfriendly communication phrases such as "I'll just...", "You just need to...", "Either X or Y", "If you insist...", "But you must...", "You don't need to decide now", "I don't need your agreement", etc.
- Use positive expressions for communication. Strictly control the use of negations. Avoid unnecessary negation and logical reversals. Do not use "This is not... but rather..." or "rather than" constructions.
- Ensure syntactic completeness, explicit semantic logic, and complete argument structure. Ensure semantic coherence and logical consistency.

---

## Code Quality Standards

- Refactored code must not change business logic and must be completely equivalent to the original code logic.
- You must be fully self-driven, making the best choices as you see fit. Review your own code, improve, optimize, and fix it yourself. Write comprehensive tests, fix code based on test results, and self-validate until all tests pass.
- All resources, documentation, and best practices you find must be persisted and linked to `AGENTS.md`.
- Your code and tests must ultimately be stable, controllable, and reproducible.
- Pay attention to function encapsulation and reuse. Your code must maintain high cohesion and low coupling, following best practices.
- Your code must have clear, unambiguous semantics.

---

## Development Environment

| Component | Version |
|-----------|---------|
| Visual Studio | 2026 |
| Windows SDK | 10.0.28000.1 |
| Windows Driver Kit | 10.0.28000.1 |

### Technology Stack

- C17
- C++20

### Build & Test

Execute `BuildAllTargets.cmd` in the `Veil.Test` directory.

---

## Update Workflow

### Overview

The update process synchronizes changes from the **phnt** repository to the **Veil** headers while maintaining Veil's coding conventions.

### Step-by-Step Procedure

1. **Prepare Sources**
   - Read the current upstream commit hash from the `VERSION` file (root of the repository).
   - Sparse-clone the [systeminformer](https://github.com/winsiderss/systeminformer) repository into `.cache/systeminformer/` to obtain the latest `phnt/include/` headers.
   - Use `git diff <old-commit> <new-commit> -- phnt/include/` to generate per-file diffs. Save each diff to `.cache/diffs/`.
   - Skip `nttypesafe.h` (no Veil mapping).

2. **Apply Changes**
   - Apply diff content to the corresponding Veil header files (see [File Mapping Reference](#file-mapping-reference)).
   - Skip files without a mapping relationship.

3. **Macro Conversion**
   - Replace all `PHNT_WINDOWS_*` macros with the corresponding `NTDDI_*` macros.
   - See [Macro Mapping Table](#macro-mapping-table) below.

4. **Nt Function Formatting**
   - Add `__kernel_entry` attribute before `NTSYSCALLAPI`.
   - Adjust closing parenthesis alignment.

   **Before (phnt style):**
   ```cpp
   NTSYSCALLAPI
   NTSTATUS
   NTAPI
   NtFlushKey(
       _In_ HANDLE KeyHandle
       );
   ```

   **After (Veil style):**
   ```cpp
   __kernel_entry NTSYSCALLAPI
   NTSTATUS
   NTAPI
   NtFlushKey(
       _In_ HANDLE KeyHandle
   );
   ```

5. **Generate Zw Function Pair**
   - Immediately after each `Nt*` function, add the corresponding `Zw*` function.
   - Use `_IRQL_requires_max_(PASSIVE_LEVEL)` and `NTSYSAPI` for `Zw*` functions.

   **Example:**
   ```cpp
   __kernel_entry NTSYSCALLAPI
   NTSTATUS
   NTAPI
   NtFlushKey(
       _In_ HANDLE KeyHandle
   );

   _IRQL_requires_max_(PASSIVE_LEVEL)
   NTSYSAPI
   NTSTATUS
   NTAPI
   ZwFlushKey(
       _In_ HANDLE KeyHandle
   );
   ```

6. **Additional Conventions**
   - Replace `static_assert` with `STATIC_ASSERT` (Veil convention).
   - Sync Zw function parameter annotation fixes from upstream when applicable.

7. **Validation**
   - **After each file update, run `BuildAllTargets.cmd` to verify compilation.**
   - Kill zombie MSBuild processes before each build: `taskkill /f /im MSBuild.exe`.
   - Check for compilation errors before proceeding to the next file.
   - Verify definition order and dependencies.

8. **Finalize**
   - Update the `VERSION` file with the new upstream commit hash (hash only, no URL or date).
   - Report changes from `ntmisc.h` separately to the user.
   - Clean up `.cache/` directory after completion.

---

## Macro Mapping Table

| phnt Macro | Veil Macro |
|------------|------------|
| `PHNT_WINDOWS_OLDEST` | `NTDDI_WIN2K` |
| `PHNT_WINDOWS_XP` | `NTDDI_WINXP` |
| `PHNT_WINDOWS_SERVER_2003` | `NTDDI_WS03` |
| `PHNT_WINDOWS_VISTA` | `NTDDI_VISTA` |
| `PHNT_WINDOWS_7` | `NTDDI_WIN7` |
| `PHNT_WINDOWS_8` | `NTDDI_WIN8` |
| `PHNT_WINDOWS_8_1` | `NTDDI_WINBLUE` |
| `PHNT_WINDOWS_10` | `NTDDI_WIN10` |
| `PHNT_WINDOWS_10_TH2` | `NTDDI_WIN10_TH2` |
| `PHNT_WINDOWS_10_RS1` | `NTDDI_WIN10_RS1` |
| `PHNT_WINDOWS_10_RS2` | `NTDDI_WIN10_RS2` |
| `PHNT_WINDOWS_10_RS3` | `NTDDI_WIN10_RS3` |
| `PHNT_WINDOWS_10_RS4` | `NTDDI_WIN10_RS4` |
| `PHNT_WINDOWS_10_RS5` | `NTDDI_WIN10_RS5` |
| `PHNT_WINDOWS_10_19H1` | `NTDDI_WIN10_19H1` |
| `PHNT_WINDOWS_10_19H2` | `NTDDI_WIN10_19H1` |
| `PHNT_WINDOWS_10_20H1` | `NTDDI_WIN10_VB` |
| `PHNT_WINDOWS_10_20H2` | `NTDDI_WIN10_MN` |
| `PHNT_WINDOWS_10_21H1` | `NTDDI_WIN10_FE` |
| `PHNT_WINDOWS_10_21H2` | `NTDDI_WIN10_CO` |
| `PHNT_WINDOWS_10_22H2` | `NTDDI_WIN10_CO` |
| `PHNT_WINDOWS_11` | `NTDDI_WIN11` |
| `PHNT_WINDOWS_11_22H2` | `NTDDI_WIN11_NI` |
| `PHNT_WINDOWS_11_23H2` | `NTDDI_WIN11_NI` |
| `PHNT_WINDOWS_11_24H2` | `NTDDI_WIN11_GE` |
| `PHNT_WINDOWS_NEW` | `NTDDI_WIN11_BR` |

### Conditional Compilation Example

**Before (phnt):**
```cpp
#if (PHNT_VERSION >= PHNT_WINDOWS_10_RS1)
// code
#endif
```

**After (Veil):**
```cpp
#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// code
#endif
```

---

## Code Conventions

### File Header Template

```cpp
/*
 * PROJECT:   Veil
 * FILE:      Veil.System.<Module>.h
 * PURPOSE:   This file is part of Veil.
 *
 * LICENSE:   MIT License
 *
 * DEVELOPER: MeeSong (meesong@outlook.com)
 */

#pragma once

// Warnings which disabled for compiling
#if _MSC_VER >= 1200
#pragma warning(push)
// nonstandard extension used : nameless struct/union
#pragma warning(disable:4201)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable:4324)
// 'enumeration': a forward declaration of an unscoped enumeration must have an
// underlying type (int assumed)
#pragma warning(disable:4471)
#endif

VEIL_BEGIN()

// Content here...

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
```

### Enumeration Definition

```cpp
/**
 * Brief description of the enumeration.
 * \sa https://learn.microsoft.com/...
 */
typedef enum _ENUM_NAME
{
    EnumValue1, // ASSOCIATED_STRUCTURE_1
    EnumValue2, // ASSOCIATED_STRUCTURE_2
    MaxEnumValue
} ENUM_NAME;
```

### Structure Definition

```cpp
/**
 * Brief description of the structure.
 * \sa https://learn.microsoft.com/...
 */
typedef struct _STRUCTURE_NAME
{
    TYPE Field1;
    TYPE Field2;
    _Field_size_bytes_(Length) TYPE VariableField[1];
} STRUCTURE_NAME, *PSTRUCTURE_NAME;
```

### Macro Definition with Documentation

```cpp
// rev (for reverse-engineered)
/**
 * \def MACRO_NAME
 * \brief Brief description.
 *
 * Detailed description of the macro's purpose and usage.
 */
#define MACRO_NAME value
```

### Kernel/User Mode Conditional Compilation

```cpp
#ifndef _KERNEL_MODE
// User-mode only definitions
#endif // !_KERNEL_MODE

#ifdef _KERNEL_MODE
// Kernel-mode only definitions
#endif // _KERNEL_MODE
```

---

## File Mapping Reference

### Header Files

| Veil Header | phnt Source |
|-------------|-------------|
| `Veil.h` | Main header (includes all sub-headers) |
| `Veil/Veil.System.ALPC.h` | `ntlpcapi.h` |
| `Veil/Veil.System.BCD.h` | `ntbcd.h` |
| `Veil/Veil.System.ConfigurationManager.h` | `ntregapi.h` |
| `Veil/Veil.System.Debug.h` | `ntdbg.h` |
| `Veil/Veil.System.Device.Afd.h` | `ntafd.h` |
| `Veil/Veil.System.Etw.h` | `ntwmi.h` |
| `Veil/Veil.System.Executive.h` | `ntexapi.h` |
| `Veil/Veil.System.IOManager.h` | `ntioapi.h` |
| `Veil/Veil.System.KernelCore.h` | `ntkeapi.h` |
| `Veil/Veil.System.Loader.h` | `ntldr.h` |
| `Veil/Veil.System.MemoryManager.h` | `ntmmapi.h` |
| `Veil/Veil.System.Nls.h` | `ntnls.h` |
| `Veil/Veil.System.ObjectManager.h` | `ntobapi.h` |
| `Veil/Veil.System.PNP.h` | `ntpnpapi.h` |
| `Veil/Veil.System.PowerManager.h` | `ntpoapi.h` |
| `Veil/Veil.System.Prefetcher.h` | `ntpfapi.h` |
| `Veil/Veil.System.Process.h` | `ntpsapi.h` |
| `Veil/Veil.System.RuntimeLibrary.h` | `ntrtl.h` |
| `Veil/Veil.System.SAM.h` | `ntsam.h` |
| `Veil/Veil.System.Security.h` | `ntseapi.h` |
| `Veil/Veil.System.SMBios.h` | `smbios.h` |
| `Veil/Veil.System.SMSS.h` | `ntsmss.h` |
| `Veil/Veil.System.SxS.h` | `ntsxs.h` |
| `Veil/Veil.System.ThreadPool.h` | `nttp.h` |
| `Veil/Veil.System.TransactionManager.h` | `nttmapi.h` |
| `Veil/Veil.System.UserManagerService.h` | `usermgr.h` |
| `Veil/Veil.System.WindowStation.h` | `winsta.h` |
| `Veil/Veil.System.Win32.h` | `ntuser.h` |
| `Veil/Veil.System.AppPackage.h` | `ntmisc.h` (partial - Package APIs only) |

### Unmapped phnt Files (Partially Mapped)

- `ntmisc.h` - Package APIs mapped to `Veil.System.AppPackage.h`; other content (COM/OLE, AppCompat) not mapped
- Files without corresponding Veil headers

---

## Verification Checklist

Before submitting changes, verify the following:

- [ ] All `PHNT_WINDOWS_*` macros converted to `NTDDI_*`
- [ ] All `Nt*` functions have `__kernel_entry` attribute
- [ ] All `Nt*` functions have corresponding `Zw*` pairs
- [ ] Closing parentheses aligned correctly
- [ ] No compilation errors in `BuildAllTargets.cmd`
- [ ] Definition order respects dependencies
- [ ] `ntmisc.h` changes reported separately

---

## Error Handling Guidelines

### Common Issues and Solutions

| Issue | Cause | Solution |
|-------|-------|----------|
| Undefined type | Missing dependency | Check definition order; add `#include` or move definition |
| Redefinition | Duplicate in SDK/WDK | Wrap with `#ifndef _KERNEL_MODE` or version check |
| Missing SAL annotation | phnt inconsistency | Add appropriate `_In_`, `_Out_`, `_Inout_` annotations |
| Macro conflict | Name collision | Use `VEIL_` prefix or conditional compilation |

### When Encountering Errors

1. **Identify** the exact error message and location.
2. **Trace** the dependency chain.
3. **Compare** with the original phnt definition.
4. **Apply** the minimal fix that maintains compatibility.
5. **Document** any non-obvious changes with comments.

---

## References

- [phnt Repository](https://github.com/winsiderss/systeminformer/tree/master/phnt)
- [Windows SDK Documentation](https://learn.microsoft.com/en-us/windows/win32/)
- [Windows Driver Kit Documentation](https://learn.microsoft.com/en-us/windows-hardware/drivers/)
- [SAL Annotations](https://learn.microsoft.com/en-us/cpp/code-quality/understanding-sal)