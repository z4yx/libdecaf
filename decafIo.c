#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEBUFSIZE 64
#define READBUFSIZE 1

void __decaf_main(void);

void __decaf_printInt(int i){
  printf("%d", i);
}

void __decaf_printString(char *s){
  printf("%s", s);
}

void *__decaf_alloc(int size){
  return malloc(size);
}

void __decaf_printBool(int b){
  printf("%s", b? "true" : "false");
}

void __decaf_halt(void){
  exit(0);
}

int __decaf_readInt(void) {
  int t;
  scanf("%d", &t);
  return t;
}

char *__decaf_readLine(void) {
    static char buffer[LINEBUFSIZE];
    fgets(buffer, LINEBUFSIZE, stdin);
    buffer[LINEBUFSIZE-1] = 0;
    int length = strlen(buffer);
    char *result = (char *)__decaf_alloc(length + 1);
    strncpy(result, buffer, length);
    return result;
}

int __decaf_stringEqual(char *s1, char *s2){
  int ret = strcmp(s1, s2);
  // printf("%s: len1=%d\n", __func__, strlen(s1));
  // printf("%s: len2=%d\n", __func__, strlen(s2));
  // printf("%s: cmp=%d\n", __func__, ret);
  return ret == 0;
}

int main(int argc, char *argv[]){
  __decaf_main();
  return 0;
}
