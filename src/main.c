#define SPURO_IMPLEMENTATION
#include "spuro.h"
#include <unistd.h> // for usleep
#include <assert.h>

int main(void)
{
    spr_printf("Hello, World!\n");
    spr_tracef("v%s\n", spr_version_string());
    spr_cprintf(SPR_RED, "RED\n");
    spr_lprintf(SPR_INFO, "Messages with a level get automatic newline.");
    spr_clprintf(SPR_RED, SPR_INFO, "RED INFO");
    spr_tprintf("Timed\n");
    Spuro s = spr_new_level_colored(SPR_STDOUT, SPR_TRACE);
    spr_logf_to(s, SPR_INFO, "This gets automatic timestamp and trace, given that the passed level to the spr_new_level_() function is SPR_TRACE.");
    spr_logf_to(s, SPR_TRACE, "YO");
    spr_clogf(s, SPR_CYAN, "Colored!\n");
    Spuro s2 = spr_new(SPR_STDOUT);
    s2.lvl = SPR_TRACE;
    s2.colored = SPR_COLORED_HEADER;
    spr_logf_to(s2, SPR_DEBUG, "OH? This does not get automated timestamp NOR the automated trace, since the Spuro level was set to SPR_TRACE manually.");
    spr_tlogf_to(s2, SPR_INFO, "We can always call spr_tlogf_to() and get a timestamp.");
    spr_clogf_to(s2, SPR_CYAN, SPR_WARN, "Manually passing location -> {file: %s, line: %i, func: %s()}", __FILE__, __LINE__, __func__);
    Spuro s3 = spr_new_file(stdout);
    s3.timed = true;
    s3.lvl = SPR_DEBUG;
    spr_tclogf_to(s3, SPR_RED, SPR_DEBUG, "Color is ignored since this Spuro is outputting with SPR_FILE. This Spuro is timed.");

    spr_fprintf(stdout, "This macro can be used with a file pointer.\n");
    spr_ftimef(stdout, "This is timed.\n");
    spr_ftracef(stdout, "This is traced.\n");
    spr_fttracef(stdout, "This is both timed and traced.\n");
    spr_fp_printf("anvil.log", "This can log to a file by passing its runtime path as a string.");

    Spuro s4 = spr_new_file(stdout);
    s4.lvl = SPR_DEBUG;

    spr_add_tee(&s3, &s4);

    assert(s3.tee_count == 1);

    spr_logf_to(s3, SPR_DEBUG, "This logs to s3 and s4");

    printf("\n\n\n\n\n");
    int total = 123; // Example total value (not 100)

    printf("\033[?25l"); // Hide cursor
    fflush(stdout);

    for (int i = 0; i <= total; ++i) {
        spr_print_progress_bar_(SPR_DEFAULT, SPR_RED, SPR_HERE, i, total);
        usleep(100000); // Sleep for 100 milliseconds
    }
    printf("\033[?25h"); // Hide cursor
    fflush(stdout);
    printf("\n");
    return 0;
}
