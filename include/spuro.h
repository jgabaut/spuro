#ifndef SPURO_H_
#define SPURO_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#define SPURO_MAJOR 0
#define SPURO_MINOR 1
#define SPURO_PATCH 0


#define SPURO_VERSION_STRING "0.1.0"

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

extern const Spuro spr_glbl;

const char* spr_version_string(void);
Spuro spr_new(SpuroOut out);
Spuro spr_from_file(FILE* fp);
Spuro spr_new_level_(SpuroOut out, SpuroLevel level, bool timed, bool colored, bool traced);


// Utility new() macros

#define spr_new_conf(out, timed, colored, traced) spr_new_level_((out), SPR_NOLVL, (timed), (colored), (traced))
#define spr_new_lvl_conf(out, level, timed, colored, traced) spr_new_level_((out), (level), (timed), (colored), (traced))

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


void spr_logf_(const Spuro *spr, SpuroLevel level, SpuroColor color, SpuroLoc loc, bool traced, bool timed, const char *format, ...);

// Utility log macros

#define spr_logf(spr, format, ...) spr_logf_((spr), SPR_NOLVL, SPR_COLOR_AUTO, SPR_LOC_NULL, false, false, (format), ## __VA_ARGS__)
#define spr_tlogf(spr, format, ...) spr_logf_((spr), SPR_NOLVL, SPR_COLOR_AUTO, SPR_LOC_NULL, false, true, (format), ## __VA_ARGS__)
#define spr_clogf(spr, color, format, ...) spr_logf_((spr), SPR_NOLVL, (color), SPR_LOC_NULL, false, false, (format), ## __VA_ARGS__)
#define spr_tclogf(spr, color, format, ...) spr_logf_((spr), SPR_NOLVL, (color), SPR_LOC_NULL, false, true, (format), ## __VA_ARGS__)
#define spr_logf_to(spr, level, format, ...) spr_logf_((spr), (level), SPR_COLOR_AUTO, SPR_LOC_NULL, false, false, (format), ## __VA_ARGS__)
#define spr_tlogf_to(spr, level, format, ...) spr_logf_((spr), (level), SPR_COLOR_AUTO, SPR_LOC_NULL, false, true, (format), ## __VA_ARGS__)
#define spr_clogf_to(spr, color, level, format, ...) spr_logf_((spr), (level), (color), SPR_LOC_NULL, false, false, (format), ## __VA_ARGS__)
#define spr_tclogf_to(spr, color, level, format, ...) spr_logf_((spr), (level), (color), SPR_LOC_NULL, false, true, (format), ## __VA_ARGS__)


// Utility trace macros
#define spr_logtf(spr, format, ...) spr_logf_((spr), SPR_NOLVL, SPR_COLOR_AUTO, SPR_HERE, true, false, (format), ## __VA_ARGS__)
#define spr_tlogtf(spr, format, ...) spr_logf_((spr), SPR_NOLVL, SPR_COLOR_AUTO, SPR_HERE, true, true, (format), ## __VA_ARGS__)
#define spr_clogtf(spr, color, format, ...) spr_logf_((spr), SPR_NOLVL, (color), SPR_HERE, true, false, (format), ## __VA_ARGS__)
#define spr_tclogtf(spr, color, format, ...) spr_logf_((spr), SPR_NOLVL, (color), SPR_HERE, true, true, (format), ## __VA_ARGS__)
#define spr_logtf_to(spr, level, format, ...) spr_logf_((spr), (level), SPR_COLOR_AUTO, SPR_HERE, true, false, (format), ## __VA_ARGS__)
#define spr_tlogtf_to(spr, level, format, ...) spr_logf_((spr), (level), SPR_COLOR_AUTO, SPR_HERE, true, true, (format), ## __VA_ARGS__)
#define spr_clogtf_to(spr, color, level, format, ...) spr_logf_((spr), (level), (color), SPR_HERE, true, false, (format), ## __VA_ARGS__)
#define spr_tclogtf_to(spr, color, level, format, ...) spr_logf_((spr), (level), (color), SPR_HERE, true, true, (format), ## __VA_ARGS__)

// spr_glbl log macros

#define spr_printf(format, ...) spr_logf(&spr_glbl, (format), ## __VA_ARGS__)
#define spr_tprintf(format, ...) spr_tlogf(&spr_glbl, (format), ## __VA_ARGS__)
#define spr_cprintf(color, format, ...) spr_clogf(&spr_glbl, (color), (format), ## __VA_ARGS__)
#define spr_tcprintf(color, format, ...) spr_tclogf(&spr_glbl, (color), (format), ## __VA_ARGS__)
#define spr_lprintf(level, format, ...) spr_logf_to(&spr_glbl, (level), (format), ## __VA_ARGS__)
#define spr_tlprintf(level, format, ...) spr_tlogf_to(&spr_glbl, (level), (format), ## __VA_ARGS__)
#define spr_clprintf(color, level, format, ...) spr_clogf_to(&spr_glbl, (color), (level), (format), ## __VA_ARGS__)
#define spr_lcprintf(level, color, format, ...) spr_clogf_to(&spr_glbl, (color), (level), (format), ## __VA_ARGS__)
#define spr_tclprintf(color, level, format, ...) spr_tclogf_to(&spr_glbl, (color), (level), (format), ## __VA_ARGS__)
#define spr_tlcprintf(level, color, format, ...) spr_tclogf_to(&spr_glbl, (color), (level), (format), ## __VA_ARGS__)

// spr_glbl trace macros
#define spr_tracef(format, ...) spr_logtf(&spr_glbl, (format), ## __VA_ARGS__)
#define spr_ttracef(format, ...) spr_tlogtf(&spr_glbl, (format), ## __VA_ARGS__)
#define spr_ctracef(color, format, ...) spr_clogtf(&spr_glbl, (color), (format), ## __VA_ARGS__)
#define spr_tctracef(color, format, ...) spr_tclogtf(&spr_glbl, (color), SPR_HERE, (format), ## __VA_ARGS__)
#define spr_ltracef(level, format, ...) spr_logtf_to(&spr_glbl, (level), (format), ## __VA_ARGS__)
#define spr_tltracef(level, format, ...) spr_tlogtf_to(&spr_glbl, (level), (format), ## __VA_ARGS__)
#define spr_cltracef(color, level, format, ...) spr_clogtf_to(&spr_glbl, (color), (level), (format), ## __VA_ARGS__)
#define spr_lctracef(level, color, format, ...) spr_clogtf_to(&spr_glbl, (color), (level), (format), ## __VA_ARGS__)
#define spr_tcltracef(color, level, format, ...) spr_tclogtf_to(&spr_glbl, (color), (level), (color), (format), ## __VA_ARGS__)
#define spr_tlctracef(level, color, format, ...) spr_tclogtf_to(&spr_glbl, (color), (level), (color), (format), ## __VA_ARGS__)

#endif // SPURO_H_

#ifdef SPURO_IMPLEMENTATION

const Spuro spr_glbl = {
    .out = SPR_STDERR,
    .fp = NULL,
    .lvl = SPR_NOLVL,
    .timed = false,
    .colored = false,
};

const char* spr_version_string(void) {
    return SPURO_VERSION_STRING;
}

const char* spr_lvl_string(SpuroLevel lvl) {
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

const char* spr_lvl_color(SpuroLevel lvl) {
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

const char* spr_color_string(SpuroColor color) {
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

Spuro spr_new(SpuroOut out) {
    return (Spuro){ .out = out };
}

Spuro spr_from_file(FILE* fp) {
    if (!fp) {
        fprintf(stderr,"%s():    FILE was NULL.\n", __func__);
        return (Spuro){0};
    }
    return (Spuro){ .out = SPR_FILE, .fp = fp};
}

Spuro spr_new_level_(SpuroOut out, SpuroLevel level, bool timed, bool colored, bool traced) {
    return (Spuro) {
        .out = out,
        .lvl = level,
        .timed = (timed ? true : (level == SPR_TRACE ? true : false)),
        .colored = colored,
    };
}

bool spr_setfile(struct Spuro *spr, FILE *file) {
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
void spr_logf_(const Spuro *spr, SpuroLevel level, SpuroColor color, SpuroLoc loc, bool traced, bool timed, const char *format, ...)
{
    if (!spr) {
        fprintf(stderr,
                "%s():    Spuro was NULL.\n", __func__);
        return;
    }

    const char* lvl_tag;
    char lvl_str[50] = "";

    const char* color_fmt;
    char color_str[50] = "";

    char trace_str[200] = "";

    if (level > spr->lvl) {
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

    va_list args;
    va_start(args, format);

    bool do_timestamp = false;
    if (!timed) {
        do_timestamp = spr->timed;
    } else {
        do_timestamp = true;
    }

    bool do_color = false;
    if (color == SPR_COLOR_AUTO) {
        do_color = spr->colored;
    } else {
        do_color = (spr->out != SPR_FILE);
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
    do_trace = traced;

    if (do_trace) {
        if (loc.file == NULL) {
            fprintf(stderr, "%s():    loc.file was NULL.\n", __func__);
            va_end(args);
            return;
        }
        if (loc.func == NULL) {
            fprintf(stderr, "%s():    loc.func was NULL.\n", __func__);
            va_end(args);
            return;
        }
        if (loc.line < 0) {
            fprintf(stderr, "%s():    loc.line was < 0.\n", __func__);
            va_end(args);
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
            va_end(args);
            return;
        }
    }
    if (do_color) {
        switch (color) {
            case SPR_COLOR_AUTO: {
                color_fmt = spr_lvl_color(level);
                if (!color_fmt) {
                    fprintf(stderr,"%s():    Color format string was NULL.\n", __func__);
                    va_end(args);
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
                    va_end(args);
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
    switch (spr->out) {
            case SPR_STDERR: {
                out = stderr;
            }
            break;
            case SPR_STDOUT: {
                out = stdout;
            }
            break;
            case SPR_FILE: {
                if (!spr->fp) {
                    fprintf(stderr,"%s():    spr->fp was NULL.\n", __func__);
                    va_end(args);
                    return;
                }
                out = spr->fp;
            }
            break;
            case SPR_PIT: {
                va_end(args);
                return;
            }
            break;
            default: {
            }
    }
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

#endif // SPURO_IMPLEMENTATION
