#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c1c1c), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // panel_meteo_days
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_meteo_days = obj;
            lv_obj_set_pos(obj, 8, 95);
            lv_obj_set_size(obj, 224, 95);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff343434), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // temperatura_day_left_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.temperatura_day_left_2 = obj;
                    lv_obj_set_pos(obj, 6, 62);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "22°");
                }
                {
                    // label_day_left_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_day_left_2 = obj;
                    lv_obj_set_pos(obj, 9, -5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "29");
                }
                {
                    // label_day_left_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_day_left_1 = obj;
                    lv_obj_set_pos(obj, 64, -5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "30");
                }
                {
                    // label_day_right_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_day_right_1 = obj;
                    lv_obj_set_pos(obj, 123, -5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "31");
                }
                {
                    // umidita_day_left_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.umidita_day_left_2 = obj;
                    lv_obj_set_pos(obj, 4, 47);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0060ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "40%");
                }
                {
                    // icon_day_left_2
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_day_left_2 = obj;
                    lv_obj_set_pos(obj, 2, 14);
                    lv_obj_set_size(obj, 31, 30);
                    lv_image_set_src(obj, &img_icon_parzialmente_nuvoloso);
                    lv_image_set_scale(obj, 100);
                }
                {
                    // icon_day_left_1
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_day_left_1 = obj;
                    lv_obj_set_pos(obj, 57, 14);
                    lv_obj_set_size(obj, 31, 30);
                    lv_image_set_src(obj, &img_icon_coperto);
                    lv_image_set_scale(obj, 100);
                }
                {
                    // umidita_day_left_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.umidita_day_left_1 = obj;
                    lv_obj_set_pos(obj, 59, 47);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0060ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "40%");
                }
                {
                    // temperatura_day_left_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.temperatura_day_left_1 = obj;
                    lv_obj_set_pos(obj, 61, 62);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "22°");
                }
                {
                    // icon_day_right_1
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_day_right_1 = obj;
                    lv_obj_set_pos(obj, 114, 14);
                    lv_obj_set_size(obj, 31, 30);
                    lv_image_set_src(obj, &img_icon_temporale);
                    lv_image_set_scale(obj, 100);
                }
                {
                    // umidita_day_right_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.umidita_day_right_1 = obj;
                    lv_obj_set_pos(obj, 117, 47);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0060ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "40%");
                }
                {
                    // temperatura_day_right_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.temperatura_day_right_1 = obj;
                    lv_obj_set_pos(obj, 119, 62);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "22°");
                }
                {
                    // label_day_right_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_day_right_2 = obj;
                    lv_obj_set_pos(obj, 175, -5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "01");
                }
                {
                    // icon_day_right_2
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_day_right_2 = obj;
                    lv_obj_set_pos(obj, 167, 14);
                    lv_obj_set_size(obj, 31, 30);
                    lv_image_set_src(obj, &img_icon_pioviggine);
                    lv_image_set_scale(obj, 100);
                }
                {
                    // umidita_day_right_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.umidita_day_right_2 = obj;
                    lv_obj_set_pos(obj, 170, 47);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0060ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "40%");
                }
                {
                    // temperatura_day_right_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.temperatura_day_right_2 = obj;
                    lv_obj_set_pos(obj, 172, 62);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "22°");
                }
            }
        }
        {
            // panel_temp
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_temp = obj;
            lv_obj_set_pos(obj, 8, 194);
            lv_obj_set_size(obj, 110, 81);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff343434), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_temp_current
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_temp_current = obj;
                    lv_obj_set_pos(obj, 12, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffdfdfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-00.0°C");
                }
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, -8, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_icon_temp);
                }
                {
                    // label_temp_percepita
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_temp_percepita = obj;
                    lv_obj_set_pos(obj, -8, 23);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Percepita:");
                }
                {
                    // label_tempt_current_perc
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_tempt_current_perc = obj;
                    lv_obj_set_pos(obj, 61, 23);
                    lv_obj_set_size(obj, 35, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-00.0°C");
                }
                {
                    // icon_arrow_up
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_arrow_up = obj;
                    lv_obj_set_pos(obj, -7, 38);
                    lv_obj_set_size(obj, 11, 11);
                    lv_image_set_src(obj, &img_icon_arrow_up);
                    lv_image_set_scale(obj, 240);
                }
                {
                    // label_max
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_max = obj;
                    lv_obj_set_pos(obj, 6, 39);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Max:");
                }
                {
                    // label_temp_max
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_temp_max = obj;
                    lv_obj_set_pos(obj, 61, 39);
                    lv_obj_set_size(obj, 35, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-00.0°C");
                }
                {
                    // label_min
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_min = obj;
                    lv_obj_set_pos(obj, 6, 54);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Min:");
                }
                {
                    // label_temp_min
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_temp_min = obj;
                    lv_obj_set_pos(obj, 61, 55);
                    lv_obj_set_size(obj, 35, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-00.0°C");
                }
                {
                    // icon_arrow_up_1
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_arrow_up_1 = obj;
                    lv_obj_set_pos(obj, -7, 54);
                    lv_obj_set_size(obj, 11, 11);
                    lv_image_set_src(obj, &img_icon_arrow_down);
                    lv_image_set_scale(obj, 240);
                }
            }
        }
        {
            // panel_update
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_update = obj;
            lv_obj_set_pos(obj, 8, 279);
            lv_obj_set_size(obj, 224, 36);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff343434), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_temp_stanza
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_temp_stanza = obj;
                    lv_obj_set_pos(obj, 0, -5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffefefe), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Temp. Stanza:");
                }
                {
                    // label_temp_stanza_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_temp_stanza_value = obj;
                    lv_obj_set_pos(obj, 66, -5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffefefe), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "20°C");
                }
                {
                    // label_umid_stanza
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_umid_stanza = obj;
                    lv_obj_set_pos(obj, 113, -5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffefefe), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Umid. Stanza:");
                }
                {
                    // label_umid_stanza_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_umid_stanza_value = obj;
                    lv_obj_set_pos(obj, 178, -5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffefefe), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "000%");
                }
                {
                    // label_aggiornamento
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_aggiornamento = obj;
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffefefe), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Ultimo aggiornamento: 00:00:00 (Successo)");
                }
            }
        }
        {
            // panel_umid
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_umid = obj;
            lv_obj_set_pos(obj, 120, 194);
            lv_obj_set_size(obj, 112, 81);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff343434), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_umid_current
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_umid_current = obj;
                    lv_obj_set_pos(obj, 12, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffdfdfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "000%");
                }
                {
                    // icon_umid
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_umid = obj;
                    lv_obj_set_pos(obj, -8, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_icon_umid);
                }
                {
                    // label_vento
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_vento = obj;
                    lv_obj_set_pos(obj, 10, 23);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Vento:");
                }
                {
                    // label_vento_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_vento_value = obj;
                    lv_obj_set_pos(obj, 50, 24);
                    lv_obj_set_size(obj, 49, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "000.0 km/h");
                }
                {
                    // icon_pressione
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_pressione = obj;
                    lv_obj_set_pos(obj, -7, 40);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_icon_pressure);
                }
                {
                    // label_pressione
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_pressione = obj;
                    lv_obj_set_pos(obj, 9, 39);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Pressione:");
                }
                {
                    // label_pressione_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_pressione_value = obj;
                    lv_obj_set_pos(obj, 58, 39);
                    lv_obj_set_size(obj, 40, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "0000 hPa");
                }
                {
                    // label_visibilita
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_visibilita = obj;
                    lv_obj_set_pos(obj, 10, 55);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Visibilita':");
                }
                {
                    // label_visibilita_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_visibilita_value = obj;
                    lv_obj_set_pos(obj, 58, 55);
                    lv_obj_set_size(obj, 37, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00.0 km");
                }
                {
                    // icon_occhio
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_occhio = obj;
                    lv_obj_set_pos(obj, -7, 54);
                    lv_obj_set_size(obj, 11, 11);
                    lv_image_set_src(obj, &img_icon_eye);
                }
                {
                    // icon_vento
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_vento = obj;
                    lv_obj_set_pos(obj, -7, 23);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_icon_wind);
                }
            }
        }
        {
            // panel_date_time_meteo_today
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_date_time_meteo_today = obj;
            lv_obj_set_pos(obj, 8, 9);
            lv_obj_set_size(obj, 224, 82);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff343434), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_data
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_data = obj;
                    lv_obj_set_pos(obj, -8, 52);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffbfafa), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Venerdi', 00-Dic-2025");
                }
                {
                    // label_luogo
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_luogo = obj;
                    lv_obj_set_pos(obj, 6, -7);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Milano");
                }
                {
                    // label_orario
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_orario = obj;
                    lv_obj_set_pos(obj, -8, 12);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "10:10:10");
                }
                {
                    // labl_meteo_today
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.labl_meteo_today = obj;
                    lv_obj_set_pos(obj, 110, 52);
                    lv_obj_set_size(obj, 90, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Soleggiato");
                }
                {
                    // icon_meteo_today
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.icon_meteo_today = obj;
                    lv_obj_set_pos(obj, 141, -7);
                    lv_obj_set_size(obj, 63, 60);
                    lv_image_set_src(obj, &img_icon_sereno);
                    lv_image_set_scale(obj, 200);
                }
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, -8, -5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_icon_location);
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
