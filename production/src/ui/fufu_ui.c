#include "fufu_ui.h"

#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>

#include "fufu_cook.h"
#include "assets/img_lv_demo_music_btn_play.c"
#include "assets/img_lv_demo_music_btn_pause.c"
#include "assets/BW_logo.c"
#include "assets/L_logo.c"
#include "assets/hot_pot_icon.c"
#include "assets/done_logo.c"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
// lv_scr_act() is the screen object (the parent of everything)
#define SCREEN lv_scr_act()
#define BTN_CHK_W 303
#define BTN_CHK_H 35
#define ORANGE 0xFB8C00
#define WHITE 0xFFFFFF
#define BLACK 0x000000

// global variables
lv_obj_t *logo;
LV_IMG_DECLARE( L_logo );
static uint32_t active_index;

// repeated button styles
static lv_style_t def_style; // default style
static lv_style_t chk_btn_style; // checkbox and button style
static lv_style_t chk_obj_style; // checkbox object style

// timer objects
static lv_timer_t * timer;
static lv_obj_t * btn_label;
static lv_anim_t a;
static lv_obj_t * arc;

// timer variables
uint8_t pos;
uint8_t bufpos;
uint32_t TIME_SET;
char buf[10];

static void start_btn_cb();
void fufu_ui();

static void remove_padding( lv_obj_t *obj ) {

  lv_obj_set_style_pad_left( obj, 0 , 0 );
  lv_obj_set_style_pad_right( obj, 0 , 0 );
  lv_obj_set_style_pad_top( obj, 0 , 0 );
  lv_obj_set_style_pad_bottom( obj, 0 , 0 );

}

static void go_home( lv_event_t * e ) {

  lv_event_code_t code = lv_event_get_code( e );

  if (code == LV_EVENT_CLICKED){
    fufu_ui();
  }

}

void complete_screen() {

  // page for when cooking is finished

  // clear screen and make it white
  lv_obj_clean( SCREEN );
  lv_obj_add_style( SCREEN, &def_style, LV_PART_MAIN );

  // background fufupot logo
  LV_IMG_DECLARE( done_logo );
  logo = lv_img_create( SCREEN );
  lv_img_set_src( logo, &done_logo );
  lv_obj_align( logo, LV_ALIGN_TOP_MID, 0, 0 );

  // pot is hot icon
  LV_IMG_DECLARE( hot_pot_icon );
  lv_obj_t *hot_pot = lv_img_create( SCREEN );
  lv_img_set_src( hot_pot, &hot_pot_icon );
  lv_obj_center( hot_pot );

  // caution text
  lv_obj_t *hot_label = lv_label_create( SCREEN );
  lv_label_set_text( hot_label, "caution: hot");
  lv_obj_set_style_text_font( hot_label, &lv_font_montserrat_20, LV_PART_MAIN );
  lv_obj_set_style_text_color( hot_label, lv_color_hex( 0x60666e ), LV_PART_MAIN);
  lv_obj_align( hot_label, LV_ALIGN_CENTER, 0, 60);

  lv_obj_t *hot_sublabel = lv_label_create( SCREEN );
  lv_label_set_text( hot_sublabel, "please be care when touching the pot");
  lv_obj_set_style_text_color( hot_sublabel, lv_color_hex( 0x60666e ), LV_PART_MAIN);
  lv_obj_align( hot_sublabel, LV_ALIGN_CENTER, 0, 80);

  // go home button
  lv_obj_t * home_btn = lv_btn_create( SCREEN );
  lv_obj_add_style( home_btn, &chk_obj_style, LV_PART_MAIN );
  lv_obj_add_event_cb( home_btn, go_home, LV_EVENT_ALL, NULL);
  lv_obj_set_size( home_btn, BTN_CHK_W, BTN_CHK_H );
  lv_obj_align( home_btn, LV_ALIGN_BOTTOM_MID, 0, -15 );
  lv_obj_set_style_bg_color( home_btn, lv_color_hex( WHITE ), LV_STATE_PRESSED);

  remove_padding( home_btn );

  lv_obj_t *home_btn_txt = lv_label_create( home_btn );
  lv_label_set_text( home_btn_txt, "go home");
  lv_obj_center( home_btn_txt );
  
}

typedef struct {
  uint32_t seconds;           // Stores the remaining seconds
  lv_obj_t* label;
}countdown_t;

void set_angle(void * obj, int32_t v){

  lv_arc_set_value(obj, v);

}

void stop_timer( lv_event_t * e ){

  lv_obj_t * obj = lv_event_get_target( e );
  lv_event_code_t code = lv_event_get_code( e );

  countdown_t * countdown = malloc(sizeof(countdown_t)); 

  // check if button is set to pause
  if(lv_obj_has_state( obj, LV_STATE_CHECKED )){

    lv_timer_pause( timer );
    pos = lv_arc_get_value( arc );
    lv_anim_del( arc, set_angle );

    // go home button
    lv_obj_t * home_btn = lv_btn_create( SCREEN );
    lv_obj_add_style( home_btn, &chk_obj_style, LV_PART_MAIN );
    lv_obj_add_event_cb( home_btn, go_home, LV_EVENT_ALL, NULL);
    lv_obj_set_size( home_btn, BTN_CHK_W, BTN_CHK_H );
    lv_obj_align( home_btn, LV_ALIGN_BOTTOM_MID, 0, -15 );
    lv_obj_set_style_bg_color( home_btn, lv_color_hex( WHITE ), LV_STATE_PRESSED);

    lv_obj_t *home_btn_txt = lv_label_create( home_btn );
    lv_label_set_text( home_btn_txt, "go home" );
    lv_obj_center( home_btn_txt );

    // TO DO: bring all gpio pins low to pause fufupot functions

  } else {

    lv_timer_resume( timer );
    lv_anim_set_var( &a, arc );
    lv_anim_set_exec_cb( &a, set_angle );
    lv_anim_set_time( &a, countdown->seconds * 1000 );
    lv_arc_set_value( arc, pos );
    lv_anim_set_values( &a, 100, 0 );
    lv_anim_start( &a );

  }

  free( countdown );
}

static void countdown_timer(lv_timer_t * timer) {

  countdown_t * countdown = timer->user_data;

  if (countdown->seconds > 0) {
    countdown->seconds--;

    // Update the label text
    snprintf(buf, sizeof(buf), "%02u:%02u", countdown->seconds / 60, countdown->seconds % 60);
    lv_label_set_text(countdown->label, buf);

  } else {

    lv_timer_del(timer); 

    // TO DO: bring all gpio pins low to pause fufupot functions 

    complete_screen();
    
  }
}

static void start_countdown(uint32_t seconds, lv_obj_t* label) {

  countdown_t * countdown = malloc(sizeof(countdown_t));

  countdown->seconds = seconds;
  countdown->label = label;
  
  snprintf(buf, sizeof(buf), "%02u:%02u", countdown->seconds / 60, countdown->seconds % 60);
  lv_label_set_text(countdown->label, buf);

  // Create a timer that calls countdown_timer every 1000 ms (1 second)
  timer = lv_timer_create(countdown_timer, 1000, countdown);
  free(countdown);

}

void timer_screen() {
  // default timer length  
  TIME_SET = reg_cook_time;

  countdown_t * countdown = malloc(sizeof(countdown_t)); 

  // clear screen and make white
  lv_obj_clean( SCREEN );
  lv_obj_add_style( SCREEN, &def_style, LV_PART_MAIN );

  // logo at the top
  logo = lv_img_create( SCREEN );
  lv_img_set_src( logo, &L_logo );
  lv_obj_align( logo, LV_ALIGN_TOP_MID, 0, 10 );

  // timer is a label
  countdown->label = lv_label_create( SCREEN );
  lv_obj_set_style_text_font( countdown->label, &lv_font_montserrat_36, LV_PART_MAIN );
  lv_label_set_text( countdown->label, "" );
  lv_obj_align( countdown->label, LV_ALIGN_CENTER, 0, 0 );

  // pause and resume timer button
  lv_obj_t * stop_btn = lv_btn_create( SCREEN );
  lv_obj_add_style( stop_btn, &chk_btn_style, LV_PART_MAIN );
  lv_obj_set_size( stop_btn, 80, 26);
  lv_obj_align( stop_btn, LV_ALIGN_BOTTOM_MID, 0, -75 );
  lv_obj_add_event_cb(stop_btn, stop_timer, LV_EVENT_CLICKED, NULL);
  lv_obj_add_flag(stop_btn, LV_OBJ_FLAG_CHECKABLE);
  
  btn_label = lv_label_create( stop_btn );
  lv_label_set_text( btn_label, "stop" );
  lv_obj_center( btn_label );

  // timer arc
  arc = lv_arc_create( SCREEN );
  lv_obj_set_size( arc, 250, 250 );
  lv_arc_set_rotation(arc, 90);
  lv_obj_set_style_arc_color( arc, lv_color_hex( ORANGE ), LV_PART_INDICATOR | LV_STATE_DEFAULT );
  lv_arc_set_bg_angles(arc, 0, 360);
  lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
  lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
  lv_obj_center(arc);

  // TO DO: figure out why timer behavior is not correct
  lv_anim_init(&a);
  lv_anim_set_var(&a, arc);
  lv_anim_set_exec_cb(&a, set_angle);
  lv_anim_set_time(&a, TIME_SET * 1000);
  lv_anim_set_repeat_count(&a, 0);
  lv_anim_set_values(&a, 100, 0);

  lv_anim_start(&a);

  start_countdown(TIME_SET, countdown->label);

  free(countdown);
}

static void cook_handler( lv_event_t *e ) {

  // cooking selection handler

  uint32_t * active_id = lv_event_get_user_data(e);
  lv_obj_t * cont = lv_event_get_current_target(e);
  lv_obj_t * parent = lv_obj_get_parent( cont );
  lv_obj_t * act_cb = lv_event_get_target(e);
  lv_obj_t * old_cb = lv_obj_get_child(parent, *active_id);

  /*Do nothing if the container was clicked*/
  if(act_cb == parent) return;

  // lv obj get text/child # to determine cook mode
  uint8_t idx = lv_obj_get_index( act_cb );

  // set cook setting based on index (selected button)
  // TO DO: move calling cook function out of this function
  switch( idx ) {
    case 0:
      cook( soft );
      TIME_SET = soft_cook_time;
      break;
    case 1:
      cook( regular );
      TIME_SET = reg_cook_time;
      break;
    case 2:
      cook( firm );
      TIME_SET = firm_cook_time;
      break; 
  }

  lv_obj_clear_state(old_cb, LV_STATE_CHECKED);
  lv_obj_add_state(act_cb, LV_STATE_CHECKED);     

  *active_id = lv_obj_get_index(act_cb);

}

static void cook_btn_cb( lv_event_t *e ) {
  
  lv_event_code_t code = lv_event_get_code( e );
  lv_obj_t *btn = lv_event_get_target( e );

  if (code == LV_EVENT_CLICKED) {
    timer_screen();
  }

}

void create_chk( lv_obj_t *parent, const char *txt ){

  lv_obj_t *obj = lv_checkbox_create( parent );
  lv_checkbox_set_text( obj, txt );
  lv_obj_set_style_border_color( obj, lv_color_hex( ORANGE ), LV_PART_INDICATOR | LV_STATE_DEFAULT & LV_STATE_CHECKED );
	lv_obj_set_style_bg_color( obj, lv_color_hex( ORANGE ), LV_PART_INDICATOR | LV_STATE_CHECKED );  
  lv_obj_set_style_pad_column( obj, 8, 0 );
  lv_obj_align( obj, LV_ALIGN_LEFT_MID, -4, 0 );
  lv_obj_set_style_radius( obj, 50, LV_PART_INDICATOR | LV_STATE_DEFAULT );
  lv_obj_set_style_radius( obj, 50, LV_PART_INDICATOR | LV_STATE_CHECKED );
  remove_padding( obj );

}

void create_cook( lv_obj_t *parent, const char *txt ){

  lv_obj_t *obj = lv_btn_create( parent );
  lv_obj_add_flag( obj, LV_OBJ_FLAG_CHECKABLE );
  lv_obj_set_size( obj, 80, 26 );
  lv_obj_add_style( obj, &def_style, LV_PART_MAIN );
  lv_obj_set_style_text_color( obj, lv_color_hex( BLACK ), LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_obj_set_style_text_color( obj, lv_color_hex( WHITE ), LV_PART_MAIN | LV_STATE_CHECKED );
	lv_obj_set_style_bg_color( obj, lv_color_hex( ORANGE ), LV_PART_MAIN | LV_STATE_CHECKED );
  lv_obj_set_style_radius( obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT );
  remove_padding( obj );

  lv_obj_t *text = lv_label_create( obj );
  lv_label_set_text( text, txt );
  lv_obj_center( text );  

  lv_obj_add_event_cb( obj, cook_handler, LV_EVENT_CLICKED, &active_index);
}

void setup_screen() {

  lv_obj_clean( SCREEN );

  lv_style_init( &def_style );
  lv_style_set_bg_color( &def_style, lv_color_hex( WHITE ) );
  lv_style_set_border_width( &def_style, 0 );
  lv_style_set_shadow_width( &def_style, 0 );
  remove_padding( SCREEN );

  lv_obj_add_style( SCREEN, &def_style, LV_PART_MAIN );

  logo = lv_img_create( SCREEN );
  lv_img_set_src( logo, &L_logo );
  lv_obj_align( logo, LV_ALIGN_TOP_MID, 0, 12 );

  lv_style_init( &chk_btn_style );
  lv_style_set_bg_color( &chk_btn_style, lv_color_hex( ORANGE ) );
  lv_style_set_border_width( &chk_btn_style, 0 );
  lv_style_set_radius( &chk_btn_style, 25);
  lv_style_set_text_color( &chk_btn_style, lv_color_hex( BLACK ) );
  lv_style_set_shadow_width( &chk_btn_style, 0 );
  lv_style_set_pad_all( &chk_btn_style, 0 );

  lv_obj_t *rot_btn = lv_btn_create( SCREEN );
  lv_obj_set_size( rot_btn, BTN_CHK_W, BTN_CHK_H );
  lv_obj_add_style( rot_btn, &chk_btn_style, LV_PART_MAIN );
  lv_obj_align( rot_btn , LV_ALIGN_CENTER, 0, -90 );
  
  lv_obj_t *rot_txt = lv_label_create( rot_btn );
  lv_label_set_text( rot_txt, "hold to rotate mixing attachment");
  lv_obj_center( rot_txt );

  lv_obj_t *strt_btn = lv_btn_create( SCREEN );
  lv_obj_set_size( strt_btn, BTN_CHK_W, BTN_CHK_H );
  lv_obj_add_style( strt_btn, &chk_btn_style, LV_PART_MAIN );
  lv_obj_align( strt_btn, LV_ALIGN_BOTTOM_MID, 0, -15 );
  lv_obj_add_event_cb( strt_btn, cook_btn_cb, LV_EVENT_ALL, NULL );
  lv_obj_t *strt_txt = lv_label_create( strt_btn );
  lv_label_set_text( strt_txt, "start cooking");
  lv_obj_center( strt_txt );

  lv_style_init( &chk_obj_style );
  lv_style_set_bg_color( &chk_obj_style, lv_color_hex( WHITE ) );
  lv_style_set_border_color( &chk_obj_style, lv_color_hex( BLACK ) );
  lv_style_set_border_width( &chk_obj_style, 2 );
  lv_style_set_radius( &chk_obj_style, 25 );
  lv_style_set_text_color( &chk_obj_style, lv_color_hex( BLACK ) );
  lv_style_set_shadow_width( &chk_obj_style, 0) ;
  lv_style_set_pad_top( &chk_obj_style, 0 );
  lv_style_set_pad_bottom( &chk_obj_style, 0 );
  
  lv_obj_t *fufu_obj = lv_obj_create( SCREEN );
  lv_obj_add_style( fufu_obj, &chk_obj_style, LV_PART_MAIN);
  lv_obj_set_size( fufu_obj, BTN_CHK_W, BTN_CHK_H );
  lv_obj_align( fufu_obj, LV_ALIGN_CENTER, 0, 0 );

  lv_obj_t *wtr_obj = lv_obj_create( SCREEN );
  lv_obj_add_style( wtr_obj, &chk_obj_style, LV_PART_MAIN);
  lv_obj_set_size( wtr_obj, BTN_CHK_W, BTN_CHK_H );
  lv_obj_align( wtr_obj, LV_ALIGN_CENTER, 0, 48 );

  create_chk( fufu_obj, "add 1 box (6 cups) fufu powder" );

  create_chk( wtr_obj, "fill water tank" );

  lv_obj_t *cook_obj = lv_obj_create( SCREEN );
  lv_obj_add_style( cook_obj, &chk_obj_style, LV_PART_MAIN);
  lv_obj_set_size( cook_obj, BTN_CHK_W, BTN_CHK_H );
  lv_obj_align( cook_obj, LV_ALIGN_CENTER, 0, 144 );
  lv_obj_set_flex_align( cook_obj, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY );
  remove_padding( cook_obj );

  active_index = 1;
  create_cook( cook_obj, "soft" );
  create_cook( cook_obj, "regular" );
  create_cook( cook_obj, "firm" );

  lv_obj_add_state( lv_obj_get_child( cook_obj, 1 ), LV_STATE_CHECKED );

}

static void start_btn_cb( lv_event_t *e ) {
  lv_event_code_t code = lv_event_get_code( e );
  lv_obj_t *btn = lv_event_get_target( e );
  if (code == LV_EVENT_CLICKED) {
    setup_screen();
  }
}

void fufu_ui() {
  lv_obj_clean( SCREEN );

// start button
  static lv_style_t start_btn_style;
  lv_style_init( &start_btn_style );

  lv_style_set_text_color( &start_btn_style, lv_color_hex(0xFFFFFF) );
  lv_style_set_bg_color( &start_btn_style, lv_color_hex( BLACK ) );
  lv_style_set_text_font( &start_btn_style, &lv_font_montserrat_20 );
  lv_style_set_border_width( &start_btn_style, 0 );
  lv_style_set_radius( &start_btn_style, 0 );


  /* calling the button "start_button" because the button is defined as the start_button
  to all objects in the home screen. This enables the entire home screen to be 
  touched to enable start */
  lv_obj_t *start_button = lv_btn_create( SCREEN );
  lv_obj_add_style( start_button, &start_btn_style, LV_PART_MAIN );
  lv_obj_set_size( start_button, 320, 480 );
  lv_obj_align( start_button, LV_ALIGN_CENTER, 0, 0 );
  remove_padding( start_button );

  lv_obj_t *start_btn_label = lv_label_create( start_button );
  lv_label_set_text( start_btn_label, "touch to start");
  lv_obj_align( start_btn_label, LV_ALIGN_BOTTOM_MID, 0, -5 );

// fufu logo
  LV_IMG_DECLARE( BW_logo );
  lv_obj_t* home_logo = lv_img_create( start_button );
  lv_img_set_src( home_logo, &BW_logo );
  lv_obj_align( home_logo, LV_ALIGN_TOP_MID, 0, 12 );

// clock 
  static lv_style_t home_text_style;
  lv_style_init( &home_text_style );

  lv_style_set_text_color( &home_text_style, lv_color_hex( WHITE ) );
  lv_style_set_bg_color( &home_text_style, lv_color_hex( BLACK ) );
  lv_style_set_text_font( &home_text_style, &lv_font_montserrat_48 );

  lv_obj_t *label = lv_label_create( start_button );
  lv_label_set_text(label, "6:00 pm");
  lv_obj_add_style( label, &home_text_style, LV_PART_MAIN );
  lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
  lv_obj_add_event_cb( start_button, start_btn_cb, LV_EVENT_ALL, NULL);
}