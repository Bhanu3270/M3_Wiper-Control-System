
cc = arm-none-eabi-gcc
MACH-Cortex-m4
CFLAGS_-c -mcpu-$(MACH) -mthumb -std=gnu11 -wall -O0
         //  target     Dependency

main.o:main.c
    $(cc) $(CFLAGS)  main.c  -o main.O
           */ $(cc)  $(CFLAGS)  $^ -o $@  */


    clean:

    rm -rf  *.o *.elf

