#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_icon_location;
extern const lv_img_dsc_t img_icon_temp;
extern const lv_img_dsc_t img_icon_arrow_up;
extern const lv_img_dsc_t img_icon_arrow_down;
extern const lv_img_dsc_t img_icon_umid;
extern const lv_img_dsc_t img_icon_wind;
extern const lv_img_dsc_t img_icon_pressure;
extern const lv_img_dsc_t img_icon_eye;
extern const lv_img_dsc_t img_icon_sereno;
extern const lv_img_dsc_t img_icon_sereno_notte;
extern const lv_img_dsc_t img_icon_parzialmente_nuvoloso;
extern const lv_img_dsc_t img_icon_parzialmente_nuvoloso_notte;
extern const lv_img_dsc_t img_icon_coperto;
extern const lv_img_dsc_t img_icon_nebbia;
extern const lv_img_dsc_t img_icon_nebbia_notte;
extern const lv_img_dsc_t img_icon_pioviggine;
extern const lv_img_dsc_t img_icon_pioviggine_congelante;
extern const lv_img_dsc_t img_icon_pioggia;
extern const lv_img_dsc_t img_icon_pioggia_congelante;
extern const lv_img_dsc_t img_icon_neve;
extern const lv_img_dsc_t img_icon_granelli_neve;
extern const lv_img_dsc_t img_icon_temporale;
extern const lv_img_dsc_t img_icon_temporale_grandine;
extern const lv_img_dsc_t img_icon_sconosciuto;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[24];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/