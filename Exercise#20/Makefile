obj-m += first_module.o second_module.o

all:
	make -C /lib/modules/6.16.10-arch1-1/build M=$(PWD) modules

clean:
	make -C /lib/modules/6.16.10-arch1-1/build M=$(PWD) clean