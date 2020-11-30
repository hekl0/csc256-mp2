run_with_my_kernel:
	/usr/bin/qemu-system-x86_64 -enable-kvm -m 64M -L ./install/qemu/share/qemu/ -nographic -kernel linux-5.3.2/arch/x86_64/boot/bzImage -hda ./openwrt-15.05-x86-generic-combined-ext4.img -append "root=PARTUUID=076b2e55-02 rootfstype=ext4 rootwait console=tty0 console=ttyS0,38400n8 edd=off noinitrd" -hdb fat:rw:`pwd`/floppy

run_normal:
	/usr/bin/qemu-system-x86_64 -enable-kvm -m 64M -L ./install/qemu/share/qemu/ -nographic -hda ./openwrt-15.05-x86-generic-combined-ext4.img -hdb fat:rw:`pwd`/floppy

