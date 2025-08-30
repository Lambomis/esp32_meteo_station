#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_icon_location;
extern const lv_img_dsc_t img_icon_sun;
extern const lv_img_dsc_t img_icon_nebbia;
extern const lv_img_dsc_t img_icon_sun_cloud;
extern const lv_img_dsc_t img_icon_nebbia_cloud;
extern const lv_img_dsc_t img_icon_temp;
extern const lv_img_dsc_t img_icon_arrow_up;
extern const lv_img_dsc_t img_icon_arrow_down;
extern const lv_img_dsc_t img_icon_umid;
extern const lv_img_dsc_t img_icon_wind;
extern const lv_img_dsc_t img_icon_pressure;
extern const lv_img_dsc_t img_icon_eye;
extern const lv_img_dsc_t img_icon_cloud;
extern const lv_img_dsc_t img_icon_cloud_black;
extern const lv_img_dsc_t img_icon_rain;
extern const lv_img_dsc_t img_icon_rain_sun;
extern const lv_img_dsc_t img_icon_rain_moon;
extern const lv_img_dsc_t img_icon_tempesta;
extern const lv_img_dsc_t img_icon_neve;
extern const lv_img_dsc_t img_icon_cloud_onde;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[20];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/