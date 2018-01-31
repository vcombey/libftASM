nasm -f macho64 hello_world.asm &&  ld hello_world.o -macosx_version_min 10.8 -lSystem && ./a.out
