all:
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin
	qemu-system-x86_64 -hda ./bin/boot.bin

clean:
	rm ./bin/boot.bin