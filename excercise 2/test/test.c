#include <stdio.h>
int main() {
   FILE *f = fopen("serverfile.txt", "r");
   int c = getc(f);
   //int a = 0;
   while (c != EOF) {
   	  printf("%c", c);
      //putchar(c);
      c = getc(f);
      //a++;
   }
   printf("%d\n", a);
   fclose(f);
   //getchar();
   return 0;
}
