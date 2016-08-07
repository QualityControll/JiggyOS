PROJECT_ROOT="$HOME/JiggyOS"
ISO_DIR_PATH="$PROJECT_ROOT/isodir"
BOOT_DIR_PATH="$PROJECT_ROOT/isodir/boot"
GRUB_DIR_PATH="$BOOT_DIR_PATH/grub"

OS_BIN_NAME="JiggyOS.bin"
ISO_IMAGE_NAME="JiggyOS.iso"
GRUB_CONF_NAME="grub.cfg"


i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

i686-elf-gcc -T linker.ld -o $OS_BIN_NAME -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

if grub-file --is-x86-multiboot $OS_BIN_NAME; then
	echo multiboot confirmed - success!
	echo OS product - $OS_BIN_NAME created.
else
	echo the file is NOT multiboot - fail!
fi

cp $OS_BIN_NAME $BOOT_DIR_PATH
cp $GRUB_CONF_NAME $GRUB_DIR_PATH
grub-mkrescue -o $ISO_IMAGE_NAME $ISO_DIR_PATH


