We decompiled the code in the Ghidra application then we saw that if argv[1] == 0x1a7 the code spawned a shell so we converted 0x1a7 hex value to decimal
after a whoami command we know we are level1 user so we are able to cat the .pass file of level1
