# Rainfall

This project serves as an introduction to exploiting ELF-like binaries through a series of progressively challenging levels. The **goal** of this project is to gain understanding of why small bad practices can lead to vulnerabilities in your code.

## How to run the project
You need to download the [rainfall .iso](https://cdn.intra.42.fr/isos/RainFall.iso) and then run it.  
In order to connect with `ssh` or copy file to your host machine with `scp`, you need to add a bridged network to the VM so that it can communicate with the host.  
- For VirtualBox :
1. Go to the VM Settings -> Network
2. Enable Network Adapter
3. Choose Bridged Adapter
<img src="https://github.com/user-attachments/assets/b2977c28-469d-4afa-9b4c-a7da910ac24a" alt="Screenshot of Bridged Network in VirtualBox" width="600"/>
  
  
Now you can run commands like these :
```
ssh -p 4242 level0@<ip address>
scp -P 4242 level0@<ip address>:~/level0 ./level0
```
  
## Table of Contents

- [Level 0](./level0/)
- [Level 1](./level1/)
- [Level 2](./level2/)
- [Level 3](./level3/)
- [Level 4](./level4/)
- [Level 5](./level5/)
- [Level 6](./level6/)
- [Level 7](./level7/)
- [Level 8](./level8/)
- [Level 9](./level9/)

## Collaborators
- [Basile JEANNOT](https://github.com/fan2bolide)
- [Arthur ASCEDU](https://github.com/aascedu)