cmd_/media/rootfs_backup/haolong/modules/MCBSP_MODULE/rd_gpio_i2c.o := arm-none-linux-gnueabi-gcc -Wp,-MD,/media/rootfs_backup/haolong/modules/MCBSP_MODULE/.rd_gpio_i2c.o.d  -nostdinc -isystem /root/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-linux-gnueabi/4.3.3/include -Iinclude  -I/usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include -include include/linux/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-omap2/include -Iarch/arm/plat-omap/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -fno-stack-protector -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow  -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(rd_gpio_i2c)"  -D"KBUILD_MODNAME=KBUILD_STR(mcbsp_module)"  -c -o /media/rootfs_backup/haolong/modules/MCBSP_MODULE/.tmp_rd_gpio_i2c.o /media/rootfs_backup/haolong/modules/MCBSP_MODULE/rd_gpio_i2c.c

deps_/media/rootfs_backup/haolong/modules/MCBSP_MODULE/rd_gpio_i2c.o := \
  /media/rootfs_backup/haolong/modules/MCBSP_MODULE/rd_gpio_i2c.c \
  include/asm-generic/gpio.h \
    $(wildcard include/config/gpiolib.h) \
    $(wildcard include/config/gpio/sysfs.h) \
    $(wildcard include/config/have/gpio/lib.h) \
  include/linux/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /root/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-linux-gnueabi/4.3.3/include/stdarg.h \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/linkage.h \
  include/linux/stddef.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/posix_types.h \
  include/linux/bitops.h \
    $(wildcard include/config/generic/find/first/bit.h) \
    $(wildcard include/config/generic/find/last/bit.h) \
    $(wildcard include/config/generic/find/next/bit.h) \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/bitops.h \
    $(wildcard include/config/smp.h) \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/system.h \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/32v6k.h) \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/linux/typecheck.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/irqflags.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/hwcap.h \
  include/asm-generic/cmpxchg-local.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/lock.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/dynamic_debug.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/swab.h \
  include/linux/byteorder/generic.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/div64.h \
  include/linux/errno.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/delay.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/delay.h \
  /usr/local/dvsdk/psp/linux-2.6.32-psp03.00.01.06.sdk/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  /media/rootfs_backup/haolong/modules/MCBSP_MODULE/rd_gpio_i2c.h \

/media/rootfs_backup/haolong/modules/MCBSP_MODULE/rd_gpio_i2c.o: $(deps_/media/rootfs_backup/haolong/modules/MCBSP_MODULE/rd_gpio_i2c.o)

$(deps_/media/rootfs_backup/haolong/modules/MCBSP_MODULE/rd_gpio_i2c.o):
