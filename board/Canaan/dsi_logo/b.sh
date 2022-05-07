export ARCH=riscv
export CROSS_COMPILE=riscv64-linux-
export PATH=/opt/Andestech/AndeSight_STD_v323/toolchains/nds64le-elf-mculib-v5d/bin:$PATH

#make TARGET=test/hello_world MODE=evblp3
#make TARGET=test/video_chip_test  MODE=evblp3 EXDIR=test/device_driver/pcal6416
make TARGET=test/log  MODE=evblp3 EXDIR=test/device_driver/pcal6416

