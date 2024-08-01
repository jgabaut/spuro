#ifndef SPURO_H_
#define SPURO_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>

#define SPURO_MAJOR 0
#define SPURO_MINOR 1
#define SPURO_PATCH 2

#define SPURO_VERSION_STRING "0.1.2"

typedef enum SpuroOut {
    SPR_PIT = 0,
    SPR_STDERR,
    SPR_STDOUT,
    SPR_FILE,
} SpuroOut;

typedef enum SpuroLevel {
    SPR_NOLVL = 0,
    SPR_INFO,
    SPR_ERROR,
    SPR_WARN,
    SPR_DEBUG,
    SPR_TRACE,
} SpuroLevel;

#define SPR_LVL_MAX SPR_TRACE

#define SPR_COLORSTR_RED "\033[1;31m"
#define SPR_COLORSTR_GREEN "\033[1;32m"
#define SPR_COLORSTR_YELLOW "\033[1;33m"
#define SPR_COLORSTR_BLUE "\033[1;34m"
#define SPR_COLORSTR_MAGENTA "\033[1;35m"
#define SPR_COLORSTR_CYAN "\033[1;36m"
#define SPR_COLORSTR_WHITE "\033[1;37m"

#define SPR_COLORSTR_RESET "\033[0m"

#define SPR_COLORSTR_ERROR SPR_COLORSTR_RED
#define SPR_COLORSTR_INFO SPR_COLORSTR_GREEN
#define SPR_COLORSTR_WARN SPR_COLORSTR_YELLOW
#define SPR_COLORSTR_DEBUG SPR_COLORSTR_BLUE
#define SPR_COLORSTR_TRACE SPR_COLORSTR_WHITE

typedef enum SpuroColor {
    SPR_COLOR_AUTO = 0,
    SPR_RED,
    SPR_GREEN,
    SPR_YELLOW,
    SPR_BLUE,
    SPR_MAGENTA,
    SPR_CYAN,
    SPR_WHITE,
} SpuroColor;

#define SPR_COLOR_MAX SPR_WHITE

const char* spr_lvl_string(SpuroLevel level);
const char* spr_lvl_color(SpuroLevel lvl);
const char* spr_color_string(SpuroColor color);

typedef struct Spuro {
    SpuroOut out;
    FILE* fp;
    SpuroLevel lvl;
    bool timed;
    bool colored;
    bool traced;
} Spuro;

typedef struct SpuroLoc {
    const char* file;
    const int line;
    const char* func;
} SpuroLoc;

#define SPR_LOC_NULL (SpuroLoc) { .file = NULL, \
    .line = -1, \
    .func = NULL, \
}

#define SPR_HERE (SpuroLoc) { \
    .file = __FILE__, \
    .line = __LINE__, \
    .func = __func__, \
}

#ifndef SPR_DEFAULT
#define SPR_DEFAULT (Spuro) { \
    .out = SPR_STDERR, \
    .fp = NULL, \
    .lvl = SPR_LVL_MAX, \
    .timed = false, \
    .colored = false, \
    .traced = false, \
}
#endif // SPR_DEFAULT

const char* spr_version_string(void);
Spuro spr_new_(FILE* fp, bool check_file, SpuroOut out, SpuroLevel level, bool timed, bool colored, bool traced);

#define spr_new(out) spr_new_(NULL, false, (out), SPR_DEFAULT.lvl, false, false, false)

// Utility new() macros

#define spr_new_conf(out, timed, colored, traced) spr_new_(NULL, false, (out), SPR_NOLVL, (timed), (colored), (traced))
#define spr_new_lvl_conf(out, level, timed, colored, traced) spr_new_(NULL, false, (out), (level), (timed), (colored), (traced))

// Utility new_file() macros

#define spr_new_file_conf(fp, timed, colored, traced) spr_new_((fp), true, SPR_FILE, SPR_NOLVL, (timed), (colored), (traced))
#define spr_new_file(fp) spr_new_file_conf((fp),false,false,false)
#define spr_new_file_timed(fp) spr_new_file_conf((fp),true,false,false)
#define spr_new_file_traced(fp) spr_new_file_conf((fp),false,false,true)
#define spr_new_file_tt(fp) spr_new_file_conf((fp),true,false,true)

// Utility new_file() level + conf macros
#define spr_new_file_lvl_conf(fp, level, timed, colored, traced) spr_new_((fp), true, SPR_FILE, (level), (timed), (colored), (traced))
#define spr_new_file_timed_to(fp, level) spr_new_lvl_conf((fp), (level), true,false,false)
#define spr_new_file_traced_to(fp, level) spr_new_lvl_conf((fp), (level), false,false,true)
#define spr_new_file_tt_to(fp, level) spr_new_lvl_conf((fp), (level),true,false,true)

// Utility new() conf macros

#define spr_new_colored(out) spr_new_conf((out),false,true,false)
#define spr_new_timed(out) spr_new_conf((out),true,false,false)
#define spr_new_tc(out) spr_new_conf((out),true,true,false)
#define spr_new_traced(out) spr_new_conf((out),false,false,true)
#define spr_new_ttraced(out) spr_new_conf((out),true,false,true)
#define spr_new_ctraced(out) spr_new_conf((out),false,true,true)
#define spr_new_tctraced(out) spr_newconf((out),true,true,true)

// Utility new() level + conf macros

#define spr_new_level(out, level) spr_new_lvl_conf((out),(level),false,false,false)
#define spr_new_level_timed(out, level) spr_new_lvl_conf((out),(level),true,false,false)
#define spr_new_level_colored(out, level) spr_new_lvl_conf((out),(level),false,true,false)
#define spr_new_level_tc(out, level) spr_new_lvl_conf((out),(level),true,true,false)
#define spr_new_traced_level(out, level) spr_new_lvl_conf((out),(level),false,false,true)
#define spr_new_ttraced_level(out, level) spr_new_lvl_conf((out),(level),true,false,true)
#define spr_new_ctraced_level(out, level) spr_new_lvl_conf((out),(level),false,true,true)
#define spr_new_tctraced_level(out, level) spr_new_lvl_conf((out),(level),true,true,true)

bool spr_setfile(Spuro *spr, FILE *file);

void spr_logf_(const Spuro spr, SpuroLevel level, SpuroColor color, SpuroLoc loc, bool traced, bool timed, const char *format, ...);
void spr_print_progress_bar_(const Spuro spr, SpuroColor color, SpuroLoc loc, int progress, int total);

// Utility log macros

#define spr_logf(spr, ...) spr_logf_((spr), SPR_NOLVL, SPR_COLOR_AUTO, SPR_HERE, false, false, __VA_ARGS__)
#define spr_tlogf(spr, ...) spr_logf_((spr), SPR_NOLVL, SPR_COLOR_AUTO, SPR_HERE, false, true, __VA_ARGS__)
#define spr_clogf(spr, color, ...) spr_logf_((spr), SPR_NOLVL, (color), SPR_HERE, false, false, __VA_ARGS__)
#define spr_tclogf(spr, color, ...) spr_logf_((spr), SPR_NOLVL, (color), SPR_HERE, false, true, __VA_ARGS__)
#define spr_logf_to(spr, level, ...) spr_logf_((spr), (level), SPR_COLOR_AUTO, SPR_HERE, false, false, __VA_ARGS__)
#define spr_tlogf_to(spr, level, ...) spr_logf_((spr), (level), SPR_COLOR_AUTO, SPR_HERE, false, true, __VA_ARGS__)
#define spr_clogf_to(spr, color, level, ...) spr_logf_((spr), (level), (color), SPR_HERE, false, false, __VA_ARGS__)
#define spr_tclogf_to(spr, color, level, ...) spr_logf_((spr), (level), (color), SPR_HERE, false, true, __VA_ARGS__)

// Utility trace macros
#define spr_logtf(spr, ...) spr_logf_((spr), SPR_NOLVL, SPR_COLOR_AUTO, SPR_HERE, true, false, __VA_ARGS__)
#define spr_tlogtf(spr, ...) spr_logf_((spr), SPR_NOLVL, SPR_COLOR_AUTO, SPR_HERE, true, true, __VA_ARGS__)
#define spr_clogtf(spr, color, ...) spr_logf_((spr), SPR_NOLVL, (color), SPR_HERE, true, false, __VA_ARGS__)
#define spr_tclogtf(spr, color, ...) spr_logf_((spr), SPR_NOLVL, (color), SPR_HERE, true, true, __VA_ARGS__)
#define spr_logtf_to(spr, level, ...) spr_logf_((spr), (level), SPR_COLOR_AUTO, SPR_HERE, true, false, __VA_ARGS__)
#define spr_tlogtf_to(spr, level, ...) spr_logf_((spr), (level), SPR_COLOR_AUTO, SPR_HERE, true, true, __VA_ARGS__)
#define spr_clogtf_to(spr, color, level, ...) spr_logf_((spr), (level), (color), SPR_HERE, true, false, __VA_ARGS__)
#define spr_tclogtf_to(spr, color, level, ...) spr_logf_((spr), (level), (color), SPR_HERE, true, true, __VA_ARGS__)

// Utility file macros

#define spr_fprintf_lvl(fp, level, traced, timed, ...) spr_logf_(spr_new_file((fp)), (level), SPR_COLOR_AUTO, SPR_HERE, (traced), (timed), __VA_ARGS__)
#define spr_fprintf_(fp, traced, timed, ...) spr_fprintf_lvl((fp), SPR_NOLVL, (traced), (timed), __VA_ARGS__)

// File macros, no level argument
#define spr_fprintf(fp, ...) spr_fprintf_((fp), false, false, __VA_ARGS__)
#define spr_ftracef(fp, ...) spr_fprintf_((fp), true, false, __VA_ARGS__)
#define spr_ftimef(fp, ...) spr_fprintf_((fp), false, true, __VA_ARGS__)
#define spr_fttracef(fp, ...) spr_fprintf_((fp), true, true, __VA_ARGS__)

// File macros with level argument
#define spr_fprintf_to(fp, level, ...) spr_fprintf_lvl((fp), (level), false, false, __VA_ARGS__)
#define spr_ftracef_to(fp, level, ...) spr_fprintf_lvl((fp), (level), true, false, __VA_ARGS__)
#define spr_ftimef_to(fp, level, ...) spr_fprintf_lvl((fp), (level), false, true, __VA_ARGS__)
#define spr_fttracef_to(fp, level, ...) spr_fprintf_lvl((fp), (level), true, true, __VA_ARGS__)

// Utility filepath macros

#define spr_fp_printf_lvl(path, level, traced, timed, ...) do { \
    FILE* spr_inner_file = fopen((path), "a"); \
    spr_fprintf_lvl(spr_inner_file, (level), (traced), (timed), __VA_ARGS__); \
    fclose(spr_inner_file); \
} while (0);

#define spr_fp_printf_(path, traced, timed, ...) spr_fp_printf_lvl((path), SPR_NOLVL, (traced), (timed), __VA_ARGS__)
#define spr_fp_printf(path, ...) spr_fp_printf_((path), false, false, __VA_ARGS__)
#define spr_fp_tracef(path, ...) spr_fp_printf_((path), true, false, __VA_ARGS__)
#define spr_fp_timef(path, ...) spr_fp_printf_((path), false, true, __VA_ARGS__)
#define spr_fp_ttracef(path, ...) spr_fp_printf_((path), true, true, __VA_ARGS__)

// SPR_DEFAULT log macros

#define spr_printf(...) spr_logf(SPR_DEFAULT,  __VA_ARGS__)
#define spr_tprintf(...) spr_tlogf(SPR_DEFAULT, __VA_ARGS__)
#define spr_cprintf(color, ...) spr_clogf(SPR_DEFAULT, (color), __VA_ARGS__)
#define spr_tcprintf(color, ...) spr_tclogf(SPR_DEFAULT, (color), __VA_ARGS__)
#define spr_lprintf(level, ...) spr_logf_to(SPR_DEFAULT, (level), __VA_ARGS__)
#define spr_tlprintf(level, ...) spr_tlogf_to(SPR_DEFAULT, (level), __VA_ARGS__)
#define spr_clprintf(color, level, ...) spr_clogf_to(SPR_DEFAULT, (color), (level), __VA_ARGS__)
#define spr_lcprintf(level, color, ...) spr_clogf_to(SPR_DEFAULT, (color), (level), __VA_ARGS__)
#define spr_tclprintf(color, level, ...) spr_tclogf_to(SPR_DEFAULT, (color), (level), __VA_ARGS__)
#define spr_tlcprintf(level, color, ...) spr_tclogf_to(SPR_DEFAULT, (color), (level), __VA_ARGS__)

// SPR_DEFAULT trace macros
#define spr_tracef(...) spr_logtf(SPR_DEFAULT, __VA_ARGS__)
#define spr_ttracef(...) spr_tlogtf(SPR_DEFAULT, __VA_ARGS__)
#define spr_ctracef(color, ...) spr_clogtf(SPR_DEFAULT, (color), __VA_ARGS__)
#define spr_tctracef(color, ...) spr_tclogtf(SPR_DEFAULT, (color), SPR_HERE, __VA_ARGS__)
#define spr_ltracef(level, ...) spr_logtf_to(SPR_DEFAULT, (level), __VA_ARGS__)
#define spr_tltracef(level, ...) spr_tlogtf_to(SPR_DEFAULT, (level), __VA_ARGS__)
#define spr_cltracef(color, level, ...) spr_clogtf_to(SPR_DEFAULT, (color), (level), __VA_ARGS__)
#define spr_lctracef(level, color, ...) spr_clogtf_to(SPR_DEFAULT, (color), (level), __VA_ARGS__)
#define spr_tcltracef(color, level, ...) spr_tclogtf_to(SPR_DEFAULT, (color), (level), (color), __VA_ARGS__)
#define spr_tlctracef(level, color, ...) spr_tclogtf_to(SPR_DEFAULT, (color), (level), (color), __VA_ARGS__)

#endif // SPURO_H_

#ifdef SPURO_IMPLEMENTATION

const char* spr_version_string(void)
{
    return SPURO_VERSION_STRING;
}

const char* spr_lvl_string(SpuroLevel lvl)
{
    if (lvl <= SPR_LVL_MAX && lvl >= SPR_NOLVL) {
        switch (lvl) {
        case SPR_NOLVL: {
            return "";
        }
        break;
        case SPR_ERROR: {
            return "ERROR";
        }
        break;
        case SPR_INFO: {
            return "INFO";
        }
        break;
        case SPR_WARN: {
            return "WARN";
        }
        break;
        case SPR_DEBUG: {
            return "DEBUG";
        }
        break;
        case SPR_TRACE: {
            return "TRACE";
        }
        break;
        default: {
            fprintf(stderr, "%s():    unexpected lvl -> {%i}.\n", __func__, lvl);
            return NULL;
        }
        break;
        }
    } else {
        fprintf(stderr, "%s():    invalid lvl -> {%i}.\n", __func__, lvl);
        return NULL;
    }
}

const char* spr_lvl_color(SpuroLevel lvl)
{
    if (lvl <= SPR_LVL_MAX && lvl >= SPR_NOLVL) {
        switch (lvl) {
        case SPR_NOLVL: {
            return "";
        }
        break;
        case SPR_ERROR: {
            return SPR_COLORSTR_ERROR;
        }
        break;
        case SPR_INFO: {
            return SPR_COLORSTR_INFO;
        }
        break;
        case SPR_WARN: {
            return SPR_COLORSTR_WARN;
        }
        break;
        case SPR_DEBUG: {
            return SPR_COLORSTR_DEBUG;
        }
        break;
        case SPR_TRACE: {
            return SPR_COLORSTR_TRACE;
        }
        break;
        default: {
            fprintf(stderr, "%s():    unexpected lvl -> {%i}.\n", __func__, lvl);
            return NULL;
        }
        break;
        }
    } else {
        fprintf(stderr, "%s():    invalid lvl -> {%i}.\n", __func__, lvl);
        return NULL;
    }
}

const char* spr_color_string(SpuroColor color)
{
    if (color <= SPR_COLOR_MAX && color >= SPR_COLOR_AUTO) {
        switch (color) {
        case SPR_COLOR_AUTO: {
            return "";
        }
        break;
        case SPR_RED: {
            return SPR_COLORSTR_RED;
        }
        break;
        case SPR_GREEN: {
            return SPR_COLORSTR_GREEN;
        }
        break;
        case SPR_YELLOW: {
            return SPR_COLORSTR_YELLOW;
        }
        break;
        case SPR_BLUE: {
            return SPR_COLORSTR_BLUE;
        }
        break;
        case SPR_MAGENTA: {
            return SPR_COLORSTR_MAGENTA;
        }
        break;
        case SPR_CYAN: {
            return SPR_COLORSTR_CYAN;
        }
        break;
        case SPR_WHITE: {
            return SPR_COLORSTR_WHITE;
        }
        break;
        default: {
            fprintf(stderr, "%s():    unexpected color -> {%i}.\n", __func__, color);
            return NULL;
        }
        break;
        }
    } else {
        fprintf(stderr, "%s():    invalid color -> {%i}.\n", __func__, color);
        return NULL;
    }
}

Spuro spr_new_(FILE* fp, bool check_file, SpuroOut out, SpuroLevel level, bool timed, bool colored, bool traced)
{
    if (check_file) {
        if (!fp) {
            fprintf(stderr,"%s():    FILE was NULL.\n", __func__);
            return (Spuro) {
                0
            };
        }
    }
    return (Spuro) {
        .fp = fp,
        .out = out,
        .lvl = level,
        .timed = (timed ? true : (level == SPR_TRACE ? true : false)),
        .colored = colored,
        .traced = (traced ? true : (level == SPR_TRACE ? true : false)),
    };
}

bool spr_setfile(struct Spuro *spr, FILE *file)
{
    if (!spr) {
        fprintf(stderr,"%s():    Spuro was NULL.\n", __func__);
        return false;
    }
    if (!file) {
        fprintf(stderr,"%s():    FILE was NULL.\n", __func__);
        return false;
    }
    spr->fp = file;
    return true;
}

/**
 * Takes a Spuro, a format string, and variadic arguments.
 * @param spr The Spuro to log with.
 * @param level The SpuroLevel for the message.
 * @param color The SpuroColor for the message.
 * @param loc The SpuroLoc for the message.
 * @param traced Print location for message when true.
 * @param timed Timestamp message when true.
 * @param format The format string for message.
 */
void spr_logf_(const Spuro spr, SpuroLevel level, SpuroColor color, SpuroLoc loc, bool traced, bool timed, const char *format, ...)
{
    const char* lvl_tag;
    char lvl_str[50] = "";

    const char* color_fmt;
    char color_str[50] = "";

    char trace_str[200] = "";

    if (level > spr.lvl) {
        return;
    } else {
        lvl_tag = spr_lvl_string(level);
        if (!lvl_tag) {
            fprintf(stderr,"%s():    Level string was NULL.\n", __func__);
            return;
        }
        if (strcmp(lvl_tag, "") != 0) {
            sprintf(lvl_str, "[ %s ] ", lvl_tag);
        }
    }

    bool do_timestamp = false;
    if (!timed) {
        do_timestamp = spr.timed;
    } else {
        do_timestamp = true;
    }

    bool do_color = false;
    if (color == SPR_COLOR_AUTO) {
        do_color = spr.colored;
    } else {
        do_color = (spr.out != SPR_FILE);
    }
#ifdef _WIN32
    /**
     * We check for an existing WT_SESSION env var. Otherwise, we don't bother trying to color.
     * https://github.com/microsoft/terminal/pull/897
     */
    const char* wt_session = getenv("WT_SESSION");
    if (!wt_session) do_color = false;
#endif

    bool do_trace = false;

    if (!traced) {
        do_trace = spr.traced;
    } else {
        do_trace = traced;
    }

    if (do_trace) {
        if (loc.file == NULL) {
            fprintf(stderr, "%s():    loc.file was NULL.\n", __func__);
            return;
        }
        if (loc.func == NULL) {
            fprintf(stderr, "%s():    loc.func was NULL.\n", __func__);
            return;
        }
        if (loc.line < 0) {
            fprintf(stderr, "%s():    loc.line was < 0.\n", __func__);
            return;
        }
        snprintf(trace_str, 200, "[ %s:%i at %s() ] ", loc.file, loc.line, loc.func);
    }

    time_t now;
    struct tm *mytime;
    char timeheader[50];
    char time_tag[60] = "";
    if (do_timestamp) {
        now = time(0);
        mytime = localtime(&now);
        if (strftime(timeheader, sizeof timeheader, "%X", mytime)) {
            sprintf(time_tag,"[ %s ] ", timeheader);
        } else {
            fprintf(stderr,"%s():    Failed time string format.\n", __func__);
            return;
        }
    }
    if (do_color) {
        switch (color) {
        case SPR_COLOR_AUTO: {
            color_fmt = spr_lvl_color(level);
            if (!color_fmt) {
                fprintf(stderr,"%s():    Color format string was NULL.\n", __func__);
                return;
            }
            if (strcmp(color_fmt, "") != 0) {
                sprintf(color_str, "%s", color_fmt);
            }
        }
        break;
        default: {
            color_fmt = spr_color_string(color);
            if (!color_fmt) {
                fprintf(stderr,"%s():    Color format string was NULL.\n", __func__);
                fprintf(stderr,"%s():    Unexpected SpuroColor -> {%i}.\n", __func__, color);
                return;
            }
            if (strcmp(color_fmt, "") != 0) {
                sprintf(color_str, "%s", color_fmt);
            }
        }
        break;
        }
    }
    FILE* out = NULL;
    switch (spr.out) {
    case SPR_STDERR: {
        out = stderr;
    }
    break;
    case SPR_STDOUT: {
        out = stdout;
    }
    break;
    case SPR_FILE: {
        if (!spr.fp) {
            fprintf(stderr,"%s():    spr.fp was NULL.\n", __func__);
            return;
        }
        out = spr.fp;
    }
    break;
    case SPR_PIT: {
        return;
    }
    break;
    default: {
    }
    }

    va_list args;
    va_start(args, format);

    if (level == SPR_NOLVL) {
        if (!do_color) {
            fprintf(out, "%s%s%s", trace_str, time_tag, lvl_str);
            vfprintf(out, format, args);
        } else {
            fprintf(out, "%s%s%s%s", color_str, trace_str, time_tag, lvl_str);
            vfprintf(out, format, args);
            fprintf(out, "%s", SPR_COLORSTR_RESET);
        }
    } else {
        if (!do_color) {
            fprintf(out, "%s%s%s[", trace_str, time_tag, lvl_str);
            vfprintf(out, format, args);
            fprintf(out, "]\n");
        } else {
            fprintf(out, "%s%s%s%s[", color_str, trace_str, time_tag, lvl_str);
            vfprintf(out, format, args);
            fprintf(out, "]%s\n", SPR_COLORSTR_RESET);
        }
    }
    va_end(args);
}

void spr_print_progress_bar_(const Spuro spr, SpuroColor color, SpuroLoc loc, int progress, int total) {
    if (spr.out != SPR_STDERR && spr.out != SPR_STDOUT && spr.out != SPR_FILE) return; // Return early since there's no point in printing
    if (total <= 0) {
        fprintf(stderr,"%s():    Error: Total must be greater than zero.\n", __func__);
        return;
    }

    if (progress < 0) {
        progress = 0;
    } else if (progress > total) {
        progress = total;
    }

    int bar_width = 70; // Width of the progress bar
    double percentage = (double)progress / total;
    int pos = bar_width * percentage;

    spr_logf_(spr, SPR_NOLVL, color, loc,
            false, //traced,
            false, //timed,
            "[");
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) {
            spr_logf_(spr, SPR_NOLVL, color, loc,
                    false, //traced,
                    false, //timed,
                    "=");
        } else if (i == pos) {
            spr_logf_(spr, SPR_NOLVL, color, loc,
                    false, //traced,
                    false, //timed,
                    ">");
        } else {
            spr_logf_(spr, SPR_NOLVL, color, loc,
                    false, //traced,
                    false, //timed,
                    " ");
        }
    }
    spr_logf_(spr, SPR_NOLVL, color, loc,
            false, //traced,
            false, //timed,
            "] %3.0f %% [%i/%i]\r", percentage * 100, progress, total);
    switch(spr.out) {
        case SPR_PIT: {
            return;
        }
        break;
        case SPR_STDERR: {
            fflush(stderr);
        }
        break;
        case SPR_STDOUT: {
            fflush(stdout);
        }
        break;
        case SPR_FILE: {
            fflush(spr.fp);
        }
        break;
    }
}

#endif // SPURO_IMPLEMENTATION
