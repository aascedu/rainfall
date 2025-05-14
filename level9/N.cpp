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

