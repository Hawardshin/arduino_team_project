#include "auto_system.h"

String semiconductor ::ret_name() {
  return (name);
}

int semiconductor ::ret_quantity() {
  return (quantity);
}
int semiconductor ::ret_delay_time() {
  return (delay_time);
}

void semiconductor ::print_obj_type(void) {
  switch (obj_type) {
    case liquid:
      Serial.println("The obj_type is: liquid");
      break;
    case solid:
      Serial.println("The obj_type is: solid");
      break;
    case gas:
      Serial.println("The obj_type is: gas");
      break;
    default: Serial.println("obj type EROOR");
  }
}

void semiconductor ::print_info(void) {
   char temp;
   for(int i=0; i < strlen_P(info_and_name); i++){
    temp = pgm_read_byte_near(info_and_name+i);
    Serial.print(temp);
  }
  Serial.println(name);
  Serial.print("The delay_time is: ");
  Serial.println(delay_time);
  Serial.print("The quantity is: ");
  Serial.println(quantity);
  print_obj_type();
  print_aline();
}
semiconductor ::semiconductor() {
  // Serial.println("you make default object");
  name = "default";
  delay_time = 1;    // default work delay :  1s
  quantity = 10;     //default make_thing :10
  obj_type = solid;  // default object type :solid
}

semiconductor ::semiconductor(String _name, int _delay_time, int _quantity, t_object_type _obj_type) {
  name = _name;
  delay_time = _delay_time;
  quantity = _quantity;
  obj_type = _obj_type;
  Serial.println("---you make object----");
  print_info();
}