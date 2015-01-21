/* gcc -Wall hsrex-char.c -o hsrex-char -L. -lhsrex */
/* LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./hsrex-char */

#include <stdio.h>
#include <stdlib.h>

#include "regalone.h"
#include "regex.h"

static void print_error (regex_t *cre, int status)
{
  size_t msg_size = regerror (status, cre, NULL, 0);
  char *msg = malloc (msg_size);
  
  if (msg) {
    regerror (status, cre, msg, msg_size);
    fputs (msg, stderr);
    fputc ('\n', stderr);
    free (msg);
  }
  else {
    fputs ("Out of heap space\n", stderr);
  }
}

int main (int argc, char *argv[])
{
  regex_t cre;
  const unsigned char rx[] = "ab*c";

  int status = re_comp (&cre, rx, (sizeof rx) - 1, REG_ADVANCED | REG_NOSUB);

  if (status != REG_OKAY) {
    print_error (&cre, status);
  }
  else {
    unsigned char s[] = "abbbc";
      
    status = re_exec (&cre, s, (sizeof s) - 1, NULL, 0, NULL, 0);
    if (status == REG_OKAY) {
      puts ("matched");
    }
    else if (status == REG_NOMATCH) {
      puts ("no match");
    }
    else {
      print_error (&cre, status);
    }
    regfree (&cre);
  }
  return 0;
}
