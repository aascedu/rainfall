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

