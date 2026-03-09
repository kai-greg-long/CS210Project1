# Developer Log (DEVLOG.md)

## Monopoly Board Simulator (Spring 2026)

------------------------------------------------------------------------

### Entry 1

**Date:** 2026-03-08\
**Entry Type:** Bug Fix\
**Task worked on:** Implementing the `MonopolySpace` constructors.\
**Issue or decision:** My overloaded constructor was throwing syntax
errors. I attempted to initialize member variables using `:` incorrectly
and also used assignment syntax in the initializer list.\
**Error message / symptom (if applicable):** Multiple compile errors
around constructor initialization and unexpected tokens.\
**What I tried:** I first attempted to write the constructor using
assignment syntax inside the initializer list. I also tried setting
variables directly inside the constructor body.\
**Fix / resolution (or final decision):** I learned that initializer
lists use the syntax `member(value)` rather than `member = value`. I
rewrote the constructor to properly initialize `propertyName`,
`propertyColor`, `value`, and `rent`.\
**Commit(s):** Implemented working overloaded constructor.

------------------------------------------------------------------------

### Entry 2

**Date:** 2026-03-08\
**Entry Type:** Bug Fix\
**Task worked on:** Implementing the `isEqual()` method.\
**Issue or decision:** I was confused about why
`return propertyName == other.propertyName;` returned a boolean even
though it looked like a comparison of strings.\
**Error message / symptom (if applicable):** Conceptual confusion rather
than a compiler error.\
**What I tried:** I attempted returning different expressions and
questioned whether the comparison produced a boolean.\
**Fix / resolution (or final decision):** I learned that comparison
operators (`==`) return a boolean in C++. When comparing two strings,
the expression evaluates to `true` or `false`, which is exactly what the
function must return.\
**Commit(s):** Completed `isEqual()` method.

------------------------------------------------------------------------

### Entry 3

**Date:** 2026-03-08\
**Entry Type:** Engineering Decision\
**Task worked on:** Designing `addMany()` for adding multiple spaces to
the circular linked list.\
**Issue or decision:** I initially thought the function should prompt
the user for spaces or recursively call itself. I was confused about why
the function accepted a `vector<T>` as input.\
**Error message / symptom (if applicable):** Logical confusion about how
the vector was populated.\
**What I tried:** I tried writing loops that read input from the user
and attempted to manually increment `nodeCount`.\
**Fix / resolution (or final decision):** I decided to follow the
intended design: spaces are read from a file into a vector, then
`addMany()` iterates through the vector and calls `addSpace()` for each
element until the board reaches `MAX_SPACES`. This kept the logic simple
and avoided pointer corruption.\
**Commit(s):** Implemented vector-based insertion.

------------------------------------------------------------------------

### Entry 4

**Date:** 2026-03-08\
**Entry Type:** Bug Fix\
**Task worked on:** File input for loading Monopoly spaces.\
**Issue or decision:** My program could not open the file even though I
specified the path.\
**Error message / symptom (if applicable):** `Unable to open file`.\
**What I tried:** I attempted using both relative paths and absolute
paths. I also checked whether the filename matched the actual file.\
**Fix / resolution (or final decision):** I discovered the file name did
not match the one used in the code and that CLion sometimes runs
programs from a build directory. After correcting the file name and
ensuring the file was in the correct project folder, the file opened
successfully.\
**Commit(s):** Added file parsing for board initialization.

------------------------------------------------------------------------

### Entry 5

**Date:** 2026-03-08\
**Entry Type:** Bug Fix\
**Task worked on:** Implementing the playable traversal loop.\
**Issue or decision:** My loop jumped directly to Turn 10 or behaved
incorrectly.\
**Error message / symptom (if applicable):** Output skipped turns and
repeatedly printed Turn 10.\
**What I tried:** I inspected the loop and realized the condition used
assignment instead of comparison.\
**Fix / resolution (or final decision):** I corrected the loop condition
from `turn = 10` to `turn <= 10`. This allowed the loop to progress
normally from Turn 1 through Turn 10.\
**Commit(s):** Fixed traversal loop logic.

------------------------------------------------------------------------

### Entry 6

**Date:** 2026-03-08\
**Entry Type:** Edge Case / Testing\
**Task worked on:** Printing board spaces from the player position.\
**Issue or decision:** When implementing `printFromPlayer`, the
insertion operator `<<` caused a compile error.\
**Error message / symptom (if applicable):** The compiler reported that
`MonopolySpace` could not be sent to `cout` using `<<`.\
**What I tried:** I initially attempted to print the entire object
directly using `cout << playerNode->data`.\
**Fix / resolution (or final decision):** I realized that custom classes
do not automatically support the insertion operator. Instead, I called
the `print()` method defined in `MonopolySpace` to output the property
information.\
**Commit(s):** Implemented printing through class method.