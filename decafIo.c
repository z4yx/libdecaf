#include <stdio.h>
#include <ulib.h>
#include <string.h>
#include <file.h>

#define printf cprintf
#define putc(c) printf("%c", c)

#define MEMSIZE 1024*1024
#define LINEBUFSIZE 4096
#define READBUFSIZE 1

static int mem[MEMSIZE/4];
static int used = 0;
static char readbuf[READBUFSIZE];
static int readbuf_cnt;

static int _refill_readbuf()
{
  int ret = read(STDIN_FILENO, readbuf, READBUFSIZE);
  // printf("%s: ret=%d\n", __func__, ret);
  if(ret < 0)
    return ret;
  readbuf_cnt = ret;
  return 0;
}

static int __getchar()
{
  if(readbuf_cnt==0 && _refill_readbuf()<0)
    return -1; //Error
  if(readbuf_cnt==0)
    return -1; //EOF
  return readbuf[--readbuf_cnt];
}

static int __ungetc(int c)
{
  if(readbuf_cnt == LINEBUFSIZE)
    return -1; //Error
  return readbuf[readbuf_cnt++] = c;
}

static int __getint(){
  int c, ret = 0, sym = 1;
  while(c = __getchar(), c > 0 && c <= ' ')
    putc(c);
  if(c < 0 || c != '-' && c < '0' && c > '9')
    goto nan;
  if(c == '-'){
    sym = -1;
    putc(c);
    c = __getchar();
  }
  while(c >= '0' && c <= '9'){
    ret = ret*10+(c-'0');
    putc(c);
    c = __getchar();
  }
nan:
  if(c >= 0)
    __ungetc(c);
  return ret*sym;
}

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

int __decaf_readInt(void) {
  return __getint();
}

char *__decaf_readLine(void) {
    static char buffer[LINEBUFSIZE];
    int ret, i = 0;
    while (1) {
        char c;
        ret = __getchar();
        if (ret <= 0) {
            if (i > 0) {
                buffer[i] = '\0';
                break;
            }
            return NULL;
        }
        c = ret;

        if (c == 3) {
            return NULL;
        }
        else if (c >= ' ' && i < LINEBUFSIZE - 1) {
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
