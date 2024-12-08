ROOT_DIR := /media/ganesh/New
export PATH := $ROOT_DIR/Raspi/openwrt/staging_dir/toolchain-arm_arm1176jzf-s+vfp_gcc-12.3.0_musl_eabi/bin:$(PATH)
export STAGING_DIR := $ROOT_DIR/Raspi/openwrt/staging_dir/

# project name (generate executable with this name)
TARGET   = lvgl_sample

CC       = arm-openwrt-linux-gcc
# compiling flags here
CFLAGS   = -Wall -I$ROOT_DIR/LVGL/lvgl/install/include

LINKER   = $(CC) -o
# linking flags here
LFLAGS   = -lm -static -L$ROOT_DIR/LVGL/lvgl/install/lib -llvgl_demos -llvgl_examples -llvgl_thorvg -llvgl

# change these to set the proper directories where each files shoould be
SRCDIR   = source
OBJDIR   = objects
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Cleanup complete!" 
	@echo $(OBJECTS)
