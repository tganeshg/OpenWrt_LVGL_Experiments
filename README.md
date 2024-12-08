# OpenWrt_LVGL_Experiments
This is for variant experiment with LVGL using Openwrt on Raspberrypi
### Note: Here i have used Raspberrypi b+ ###

## Do First : Steps to cross compile the lvgl source ##
## Export toolchain ##
```
PATH=$PATH:<Put_Path>/Raspi/openwrt/staging_dir/toolchain-arm_arm1176jzf-s+vfp_gcc-12.3.0_musl_eabi/bin
export PATH
STAGING_DIR=<Put_Path>/Raspi/openwrt/staging_dir
export STAGING_DIR
```

## Clone lvgl ##
### Note: Clone it outside of this repo ###
```
git clone https://github.com/lvgl/lvgl.git
cd lvgl
```

## Create lvgl config file ##
```
cp lv_conf_template.h lv_conf.h
```
And update this line 0 to 1
```
#if 1 /* Set this to "1" to enable content */
```
Other cnfiguration also


## Create cross compile cmake file ##
```
vi cross.cmake
```

```
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(TOOLCHAIN_PREFIX arm-openwrt-linux-)
execute_process(
  COMMAND which ${TOOLCHAIN_PREFIX}gcc
  OUTPUT_VARIABLE BINUTILS_PATH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

get_filename_component(ARM_TOOLCHAIN_DIR ${BINUTILS_PATH} DIRECTORY)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_SYSROOT ${ARM_TOOLCHAIN_DIR}/../arm-openwrt-linux)
set(CMAKE_FIND_ROOT_PATH ${BINUTILS_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```
save the file with above content.

## Create Install folder ##
```
mkdir install
```

## Cross Compile ##
```
cmake -DCMAKE_TOOLCHAIN_FILE="cross.cmake" .
make
cmake --install . --prefix "./install"
```

## Compile this repo ##
### Now we can compile this sample repo using cross compiled lvgl ###
```
make clean;make
```

The target binary will be in bin folder.
