#include <stdio.h>
#include <libssh/libssh.h>
#include <string.h>
#include <memory.h>
int kbdauth(ssh_session s)
{

    int rc = ssh_userauth_kbdint(s, "root", 0);
    while (rc == SSH_AUTH_INFO)
    {
        const char *name = ssh_userauth_kbdint_getname(s);
        const char *instruction = ssh_userauth_kbdint_getinstruction(s);
        printf("\n%s \n%s", name, instruction);
        int i;
        int count = ssh_userauth_kbdint_getnprompts(s);
        for (i = 0; i < count; i++)
        {
            char echo;
            const char *promt = ssh_userauth_kbdint_getprompt(s, i, &echo);
            if (echo)
            {
                printf("\necho\n%s", promt);
                char buffer[124];
                fgets(buffer, 124, stdin);
                buffer[sizeof(buffer) - 1] = '\0';
                ssh_userauth_kbdint_setanswer(s, i, buffer);
                memset(buffer, 0, sizeof(buffer));
            }
            else
            {
                char *ptr;
                ptr = getpass(promt);
                if (ssh_userauth_kbdint_setanswer(s, i, ptr) < 0)
                    return SSH_AUTH_ERROR;
            }
        }
                int rc = ssh_userauth_kbdint(s, "darshan", 0);
    }
    return 0;
}
int authenticate_kbdint(ssh_session session)
{
  int rc;
  rc = ssh_userauth_kbdint(session,"demo", NULL);
 
    printf("\nrc detected");
    const char *name, *instruction;
    int nprompts, iprompt;
    name = ssh_userauth_kbdint_getname(session);
    instruction = ssh_userauth_kbdint_getinstruction(session);
    nprompts = ssh_userauth_kbdint_getnprompts(session);
    if (strlen(name) > 0)
      printf("name %s\n", name);
    if (strlen(instruction) > 0)
      printf("instruction %s\n", instruction);
      printf("num %d",nprompts);
  
      const char *prompt;//,*buffer;
      char *echo;
      char bufferx[120];
      prompt = ssh_userauth_kbdint_getprompt(session, 0, echo);
  
     // const char buf[30];
         printf("%s", prompt);
      // if (fgets(buffer,20, stdin) == NULL)
       scanf("%s",bufferx);
         // return SSH_AUTH_ERROR;
         // printf("%s",bufferx);
     // scanf("%s",buf);
      //  buffer[sizeof(buffer) - 1] = '\0';
    //     if ((ptr = strchr(buffer, '\n')) != NULL)
    //       *ptr = '\0';
         if (ssh_userauth_kbdint_setanswer(session,0, bufferx) < 0)
          // return SSH_AUTH_ERROR;
          printf("error");
    //     memset(buffer, 0, strlen(buffer));
      //}

  return 1;
}