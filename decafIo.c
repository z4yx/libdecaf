#include <stdio.h>
#include <ulib.h>
#include <string.h>
#include <file.h>

#define printf cprintf
#define putc(c) printf("%c", c)

#define MEMSIZE 1024*1024
#define BUFSIZE 4096

static int mem[MEMSIZE/4];
static int used = 0;

void __decaf_printInt(int i){
  printf("%d", i);
}

void __decaf_printString(char *s){
  printf("%s", s);
}

void *__decaf_alloc(int size){
  size = (size + 3)&(~0x03);
  if(used + size >= MEMSIZE){
    return (void *)NULL;
  }
  void *ret = (void *)(((char *)mem) + used);
  used += size;
  return ret;
}

void __decaf_printBool(int b){
  printf("%s", b? "true" : "false");
}

void __decaf_halt(void){
  exit(0);
}

char *__decaf_readLine(void) {
    static char buffer[BUFSIZE];
    int ret, i = 0;
    while (1) {
        char c;
        if ((ret = read(STDIN_FILENO, &c, sizeof(char))) < 0) {
            return NULL;
        }
        else if (ret == 0) {
            if (i > 0) {
                buffer[i] = '\0';
                break;
            }
            return NULL;
        }

        if (c == 3) {
            return NULL;
        }
        else if (c >= ' ' && i < BUFSIZE - 1) {
            putc(c);
            buffer[i ++] = c;
        }
        else if (c == '\n' || c == '\r') {
            printf("\n");
            buffer[i] = '\0';
            break;
        }
    }
    int length = strlen(buffer);
    char *result = (char *)__decaf_alloc(length + 1);
    strncpy(result, buffer, length);
    return result;
}
