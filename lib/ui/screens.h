#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *panel_meteo_days;
    lv_obj_t *temperatura_day_left_2;
    lv_obj_t *label_day_left_2;
    lv_obj_t *label_day_left_1;
    lv_obj_t *label_day_right_1;
    lv_obj_t *umidita_day_left_2;
    lv_obj_t *icon_day_left_2;
    lv_obj_t *icon_day_left_1;
    lv_obj_t *umidita_day_left_1;
    lv_obj_t *temperatura_day_left_1;
    lv_obj_t *icon_day_right_1;
    lv_obj_t *umidita_day_right_1;
    lv_obj_t *temperatura_day_right_1;
    lv_obj_t *label_day_right_2;
    lv_obj_t *icon_day_right_2;
    lv_obj_t *umidita_day_right_2;
    lv_obj_t *temperatura_day_right_2;
    lv_obj_t *panel_temp;
    lv_obj_t *label_temp_current;
    lv_obj_t *label_temp_percepita;
    lv_obj_t *label_tempt_current_perc;
    lv_obj_t *icon_arrow_up;
    lv_obj_t *label_max;
    lv_obj_t *label_temp_max;
    lv_obj_t *label_min;
    lv_obj_t *label_temp_min;
    lv_obj_t *icon_arrow_up_1;
    lv_obj_t *panel_update;
    lv_obj_t *label_temp_stanza;
    lv_obj_t *label_temp_stanza_value;
    lv_obj_t *label_umid_stanza;
    lv_obj_t *label_umid_stanza_value;
    lv_obj_t *label_aggiornamento;
    lv_obj_t *panel_umid;
    lv_obj_t *label_umid_current;
    lv_obj_t *icon_umid;
    lv_obj_t *label_vento;
    lv_obj_t *label_vento_value;
    lv_obj_t *icon_pressione;
    lv_obj_t *label_pressione;
    lv_obj_t *label_pressione_value;
    lv_obj_t *label_visibilita;
    lv_obj_t *label_visibilita_value;
    lv_obj_t *icon_occhio;
    lv_obj_t *icon_vento;
    lv_obj_t *panel_date_time_meteo_today;
    lv_obj_t *label_data;
    lv_obj_t *label_luogo;
    lv_obj_t *label_orario;
    lv_obj_t *labl_meteo_today;
    lv_obj_t *icon_meteo_today;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/