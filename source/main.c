#include "lvgl/lv_conf.h"
#include "lvgl/demos/lv_demos.h"
#include "menu.h"

#define LV_LINUX_FBDEV_DEVICE               "/dev/fb0"
#define LV_LINUX_EVDEV_POINTER_DEVICE       "/dev/input/event0"

/*** Private ***/
#if LV_USE_EVDEV
static void lv_linux_init_input_pointer(lv_display_t *disp)
{
    /* Enables a pointer (touchscreen/mouse) input device
     * Use 'evtest' to find the correct input device. /dev/input/by-id/ is recommended if possible
     * Use /dev/input/by-id/my-mouse-or-touchscreen or /dev/input/eventX
     */
    const char *input_device = LV_LINUX_EVDEV_POINTER_DEVICE;

    if (input_device == NULL) {
        fprintf(stderr, "please set the LV_LINUX_EVDEV_POINTER_DEVICE environment variable\n");
        exit(1);
    }

    lv_indev_t *touch = lv_evdev_create(LV_INDEV_TYPE_POINTER, input_device);
    lv_indev_set_display(touch, disp);
}
#endif

#if LV_USE_LINUX_FBDEV
static void lv_linux_disp_init(void)
{
    const char *device = LV_LINUX_FBDEV_DEVICE;
    lv_display_t * disp = lv_linux_fbdev_create();

#if LV_USE_EVDEV
    lv_linux_init_input_pointer(disp);
#endif

    lv_linux_fbdev_set_file(disp, device);
}
#else
    #error Unsupported configuration
#endif

/* Main */
int main(int argc, char **argv)
{
    /* Initialize LVGL. */
    lv_init();

    /* Initialize the configured backend SDL2, FBDEV, libDRM or wayland */
    lv_linux_disp_init();

    /*Create a Demo*/
    menu_create();

    menu_loop();

    return 0;
}

/* EOF */