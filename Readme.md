# Reference implementation for proposed SG14 `status_code` (`<system_error2>`) in C++ 11

(C) 2018 Niall Douglas [http://www.nedproductions.biz/](http://www.nedproductions.biz/)
Please send feedback to the SG14 study group mailing list at https://groups.google.com/a/isocpp.org/d/forum/sg14.

Docs: [https://ned14.github.io/status-code/](https://ned14.github.io/status-code/)
(reference API docs are at bottom of page)

Solves the problems for low latency/large code base users with `<system_error>`
as listed by [WG21 P0824](https://wg21.link/P0824). This proposed `<system_error2>`
library is EXPERIMENTAL and is subject to change as the committee evolves the design.

## Features:

- Portable to any C++ 11 compiler. These are known to work:
    - &gt;= GCC 4.9 (due to requiring libstdc++ 4.9 for sufficient C++ 11 type traits)
    - &gt;= clang 3.3 with a new enough libstdc++ (previous clangs don't implement inheriting constructors)
    - &gt;= Visual Studio 2015 (previous MSVC's don't implement inheriting constructors)
- Aims to cause zero code generated by the compiler most of the time.
- Never calls `malloc()`.
- Header-only library friendly.
- Type safe yet with type erasure in public interfaces so it can scale
across huge codebases.
- Minimum compile time load, making it suitable for use in the global headers of
multi-million line codebases.

## Problems with `<system_error>` listed by P0824 solved:

1. Does not cause `#include <string>`, and thus including the entire STL allocator and algorithm
machinery, thus preventing use in freestanding C++ as well as substantially
impacting compile times which can be a showstopper for very large C++ projects.
Only includes the following headers:
    - `<cassert>` to trap when misuse occurs.
    - `<cerrno>` for the generic POSIX error codes (`errno`) which is required to define `errc`.
    - `<cstddef>` for the definition of `size_t` and other types.
    - `<exception>` for the basic `std::exception` type so we can optionally throw STL exceptions.
    - `<new>` so we can perform placement new.
    - `<type_traits>` as we need to do some very limited metaprogramming.
    
    Compiling a file including `status_code.hpp` takes less than 150 ms with clang 3.3
as according to the `-ftime-report` diagnostic (a completely empty file takes 5 ms).

2. Unlike `std::error_code` which was designed before `constexpr`, this proposed
implementation has all-`constexpr` construction and destruction with as many operations
as possible being trivial or literal, with only those exact minimum operations which
require runtime code generation being non-trivial (note: requires C++ 14 for a complete
implementation of this).

3. This in turn means that we solve a long standing problem with `std::error_category`
in that it is not possible to define a safe custom C++ 11 error category in a header
only library where semantic comparisons would randomly break depending on the direction of wind
blowing when the linker ran. This proposed design is 100% safe to use in header only libraries.

4. `std::error_code`'s boolean conversion operator i.e. `if(ec) ...` has become
unfortunately ambiguous in real world C++ out there. Its correct meaning is
"if `ec` has a non-zero value". Unfortunately, much code out in the wild uses
it as if "if `ec` is errored". This is incorrect, though safe most of the time
where `ec`'s category is well known i.e. non-zero values are always an error.
For unknown categories supplied by third party code however, it is dangerous and leads
to unpleasant, hard-to-debug, surprise.

    The `status_code` proposed here suffers from no such ambiguity. It can be one of
exactly three meanings: (i) success (ii) failure (iii) empty (uninitialised). There
is no boolean conversion operator, so users must write out exactly what they mean
e.g. `if(sc.success()) ...`, `if(sc.failure()) ...`, `if(sc.empty()) ...`.

5. Relatedly, `status_code` can now represent successful (informational) codes as
well as failure codes. Unlike `std::error_code` where zero is given special meaning,
we impose no requirements at all on the choice of coding. This permits safe usage of more
complex C status coding such as the NT kernel's `NTSTATUS`, which is a `LONG` whereby bits
31 and 30 determine which of four categories the status is (success, informational, warning,
error), or the very commone case where negative numbers mean failure and positive numbers
mean success-with-information.

6. The relationship between `std::error_code` and `std::error_condition` is
confusing to many users reading code based on `<system_error>`, specifically when is
a comparison between codes *semantic* or *literal*? `status_code` makes all
comparisons *semantic*, **always**. If you want a literal comparison, you can do one
by hand by comparing domains and values directly.

7. `std::error_code` enforced its value to always be an `int`. This is problematic
for coding systems which might use a `long` and implement coding namespaces within
the extended number of bits, or for end users wishing to combine a code with a `void *`
in order to transmit payload or additional context. As a result, `status_code` is
templated to its domain, and the domain sets its type. A type erased edition of
`status_code<D>` is available as `status_code<void>`, this is for obvious reasons
non-copyable, non-movable and non-destructible.

    A more useful type erased edition is `status_code<erased<T>>` 
which is available if `D::value_type` is trivially copyable, `T` is an integral
type, and `sizeof(T) >= sizeof(D::value_type)`. This lets you use
`status_code<erased<T>>` in all your public interfaces without
restrictions. As a pointer to the original category is retained, and trivially
copyable types may be legally copied by `memcpy()`, type erased status codes
work exactly as normal, except that publicly it does not advertise its type.

