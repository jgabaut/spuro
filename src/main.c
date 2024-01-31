#define SPURO_IMPLEMENTATION
#include "spuro.h"

int main(void) {
    spr_printf("Hello, World!\n");
    spr_tracef("v%s\n", spr_version_string());
    spr_cprintf(SPR_RED, "RED\n");
    spr_lprintf(SPR_NOLVL, "INFO\n");
    spr_clprintf(SPR_RED, SPR_NOLVL, "RED INFO\n");
    spr_tprintf("Timed\n");
    Spuro s = spr_new_level_colored(SPR_STDOUT, SPR_TRACE);
    spr_logf_to(s, SPR_INFO, "This gets automatic timestamp and trace, given that the passed level to the spr_new_level_() function is SPR_TRACE.");
    spr_logf_to(s, SPR_TRACE, "YO");
    spr_clogf(s, SPR_CYAN, "Colored!\n");
    Spuro s2 = spr_new(SPR_STDOUT);
    s2.lvl = SPR_TRACE;
    spr_logf_to(s2, SPR_DEBUG, "OH? This does not get automated timestamp NOR the automated trace, since the Spuro level was set to SPR_TRACE manually.");
    spr_tlogf_to(s2, SPR_INFO, "We can always call spr_tlogf_to() and get a timestamp.");
    spr_clogf_to(s2, SPR_MAGENTA, SPR_WARN, "Manually passing location -> {file: %s, line: %i, func: %s()}", __FILE__, __LINE__, __func__);
    Spuro s3 = spr_from_file(stdout);
    s3.timed = true;
    s3.lvl = SPR_DEBUG;
    spr_tclogf_to(s3, SPR_RED, SPR_DEBUG, "Color is ignored since this Spuro is outputting with SPR_FILE. This Spuro is timed.");

    spr_fprintf(stdout, "This macro can be used with a file pointer.\n");
    spr_ftimef(stdout, "This is timed.\n");
    spr_ftracef(stdout, "This is traced.\n");
    spr_fttracef(stdout, "This is both timed and traced.\n");
    return 0;
}
