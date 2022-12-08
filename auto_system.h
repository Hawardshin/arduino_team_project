#ifndef AUTO_SYSTEM_H
# define AUTO_SYSTEM_H
#include "Arduino.h"
#include <Servo.h>
#include <avr/pgmspace.h>
#include "semiconductor.h"

#define pen_servo 5
#define rotate_servo 6
#define interruptPin 2
#define LED_DANGER 13
#define LED_OPERATE 12

/*the message box*/
const PROGMEM char turn_off_meseage[] = "\n----------------------------------------------------\n----------!!!!!!!! TURN OFF machine!!!!!!!!!!!-------\n----------------------------------------------------\n\n";
const PROGMEM char start_opt_meseage[] ="\n----------------------------------------------------\n--------------you can choose action-----------------\nwhat do you want to do (you must write number + ctrl + enter)\n1. make_new_object\n2. choose_object and see object info\n3. operate_the_machine\n4. off machine\n----------------------------------------------------\n\n";
const PROGMEM char start_first_meseage[] ="\n----------------------------------------------------\n----------HI this is automatic controller-----------\n";
const PROGMEM char default_meseage[] ="\n----------------------------------------------------\nTHE MACHINE IS NOT ON\nYou can input 'ON' then the Machine start to begin\n\n----------------------------------------------------\n";
const PROGMEM char choice_meseage[] ="\n----------------------------------------------------\nNow you can Choose object to see information\nIf you want default information input 'default'\nIf you want to see object information input object name\nIf you want to go back menu 'back'\n\n\n----------------------------------------------------\n";
const PROGMEM char opperate_messege[] = "\n----------------------------------------------------\n-----------------opperate section-------------------\nYou can choose the object name to opperate\n";
const PROGMEM char obj_type_choice_meseage[] = "Input the object type(please input number + ctrl + enter)\n1. liquid\n2. solid\n3. gas\n";
const PROGMEM char input_guide[] = " (please input + ctrl + enter) \n";
/*main_page.cpp*/
void  main_page(void);
void  off_machine(void);

/*print_message.cpp */
void print_input_guide(void);
void  start_opt_print();
void  try_again(int &cnt);
void  start_first_print();
void  default_print();

/* find_object.cpp*/
int  find_obj(semiconductor *obj, String find_name, int obj_num);
void  print_choose_message();
void  choose_object(semiconductor *obj,int obj_num);
void  print_obj_list_name(semiconductor *obj,int obj_num);

/*make_object.cpp*/
String input_name();
int input_delay_time();
int input_quantity();
void print_obj_type_choice();
t_object_type input_obj_type();
semiconductor  make_new_object(void);


/*operate.cpp*/
void emergency();
void  move_rotate(int i);
void  move_pen();
int main_opperate(semiconductor obj);
int  operate_machine(semiconductor *obj,int obj_num);


#endif
