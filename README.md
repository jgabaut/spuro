# spuro

## A stb-style C library for logging.

## Table of Contents

+ [What is this thing?](#witt)
  + [Basic example](#basic_example)
  + [Windows VT mode](#win_vt_mode)
  + [Documentation](#docs)
  + [Prerequisites](#prerequisites)
  + [Configuration](#config)
  + [Building](#building)
  + [Supported platforms](#support)
+ [Todo](#todo)

## What is this thing? <a name = "witt"></a>

  This is a C library that offers a variety of log macros.
  Check out `src/spuro.h` and `src/main.c` for more details.

  ```
  -------------------------------------------------------------------------------
  Language                     files          blank        comment           code
  -------------------------------------------------------------------------------
  C/C++ Header                     1             63             27            478
  -------------------------------------------------------------------------------
  ```

## Basic example <a name = "basic_example"></a>

```c

#define SPURO_IMPLEMENTATION
#include "spuro.h"

int main(void)
{
    spr_tracef("Hello, trace!\n");
    return 0;
}
```

## Windows VT mode <a name = "win_vt_mode"></a>

  When `_WIN32` is defined, a check for `ENABLE_VIRTUAL_TERMINAL_PROCESSING` is done once, on `spr_new()`.

  If, for some reason, usercode needs to change its console mode dynamically, you can build with

  `-DSPR_CHECK_VT_EACH_LOG`

  to check for every `spr_log()` call, but only if it was set at `spr_new()` check's time.

  The library never sets the flag itself, it only checks it.

  - [Docs](https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences)

  Windows VT support:
  - Introduced in `Windows 10 1607`
  - Enable via `GetConsoleMode` + `SetConsoleMode` `ENABLE_VIRTUAL_TERMINAL_PROCESSING`
  - `cmd.exe`:
    - VT supported since `1607`
    - Often pre-enabled in practice since `~1909` (not guaranteed)
  - `Windows Terminal`:
    - Always VT-enabled by default

## Documentation <a name = "docs"></a>

## Prerequisites <a name = "prerequisites"></a>

  To build the `spuro-demo` binary, you need:
  * `automake` and `autoconf` to generate the needed `Makefile`
  * `make` to build the binary
  * `gcc` or `clang`, for building `spuro-demo`

## Configuration <a name = "config"></a>

  To prepare the files needed by `autotools`, run:

  ```sh
  aclocal
  autoconf
  automake --add-missing
  ./configure # Optionally, with --enable-debug=yes or --host
  make
  ```

  You will get a `./configure` script, which you can use to enable debug mode or other features.

  - Run `./configure --host x86-64-w64-mingw32` to setup the `Makefile` appropriately for a `x86_64-w64-mingw32` build.

## Building <a name = "building"></a>

  To build both the `libspuro.so` lib and `spuro-demo` binary, run:
  * `./configure`, which should generate the `Makefile`. See [Configuration](#config) section.
  * `make`, to build all target

## Supported platforms <a name = "support"></a>

  ATM the code should build for:
  - `x86_64-Linux`
  - `x86_64-w64-mingw32` to target `Windows`

## Todo <a name = "todo"></a>
