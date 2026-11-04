/* LC 71 Simplify Path, C version (practice only: CoderPad has no C for Meta)
 * Date: 2026-11-03 · AI: reviewed
 * Pattern: stack of token pointers · Time O(n) · Space O(n)
 * Miss: original used a fixed char* stack[1000] (overflows: a 3000-char path has
 *       up to 1500 components) and strcat in a loop (O(n^2), Schlemiel the
 *       painter). Both fixed below; see tracker/error-log.md.
 *
 * Note: strtok overwrites `path` with '\0' and keeps hidden static state
 * (not reentrant; strtok_r fixes that). The tokens point into `path`, which is
 * safe because they are copied into `result` before returning.
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

char* simplifyPath(char* path) {
    size_t n = strlen(path);
    char** stack = malloc((n / 2 + 1) * sizeof *stack);  /* max components = n/2 */
    char* result = malloc(n + 2);  /* output never longer than input; +2 covers "/" */
    if (!stack || !result) {
        free(stack);
        free(result);
        return NULL;
    }
    int top = -1;

    for (char* tok = strtok(path, "/"); tok; tok = strtok(NULL, "/")) {
        if (!strcmp(tok, ".")) {
            continue;
        } else if (!strcmp(tok, "..")) {
            if (top >= 0) top--;
        } else {
            stack[++top] = tok;
        }
    }

    char* w = result;                     /* write pointer: no rescanning */
    for (int i = 0; i <= top; i++) {
        *w++ = '/';
        size_t len = strlen(stack[i]);
        memcpy(w, stack[i], len);
        w += len;
    }
    if (w == result) *w++ = '/';          /* empty stack means root */
    *w = '\0';

    free(stack);
    return result;                        /* caller frees */
}

int main(void) {
    struct { const char* in; const char* want; } cases[] = {
        {"/home/", "/home"},
        {"/../", "/"},
        {"/home//foo/", "/home/foo"},
        {"/a/./b/../../c/", "/c"},
        {"/.../a/../b/c/../d/./", "/.../b/d"},
    };
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; i++) {
        char buf[64];
        strcpy(buf, cases[i].in);         /* writable copy: strtok modifies it */
        char* got = simplifyPath(buf);
        assert(got && strcmp(got, cases[i].want) == 0);
        free(got);
    }
    return 0;
}
