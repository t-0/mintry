#ifndef MINTRY_H_
#define MINTRY_H_

#include <setjmp.h>
#include <stdlib.h>

enum {
    Exception_None = 0,
    Exception_Allocation = 1,
};

struct Exception {
    int code;
    jmp_buf j;
    struct Exception* parent;
};

extern __thread struct Exception* mintry_current;

#define TRY(CONTEXT) \
    struct Exception (CONTEXT); \
    ((CONTEXT).code) = Exception_None; \
    ((CONTEXT).parent) = mintry_current; \
    mintry_current = (&(CONTEXT)); \
    ((CONTEXT).code) = (setjmp ((CONTEXT).j)); \
    if (Exception_None != (CONTEXT.code)) { \
    } else

#define CATCH(CONTEXT, CODE) \
    if (((&(CONTEXT)) != mintry_current) || ((mintry_current->code) != (CODE))) { \
    } else

#define CATCHALL(CONTEXT) \
    if ((&(CONTEXT)) == mintry_current) {\
    } else

#define FINALLY(CONTEXT) \
    while (mintry_current != (&(CONTEXT))) { \
        mintry_current = (mintry_current->parent); \
    } \
    if (0) { \
    } else

#define THROW(CODE) \
    { \
        longjmp (mintry_current->j, CODE); \
    }

#endif
