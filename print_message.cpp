#include "auto_system.h"

void print_input_guide(void)
{
  char temp;
   for(int i=0; i < strlen_P(input_guide); i++){
    temp = pgm_read_byte_near(input_guide+i);
    Serial.print(temp);
  }
}

void  off_machine(void)
{
  char temp;
   for(int i=0; i < strlen_P(turn_off_meseage); i++){
    temp = pgm_read_byte_near(turn_off_meseage+i);
    Serial.print(temp);
  }
}

void  print_aline()
{
  char  temp;
   for(int i=0; i < strlen_P(a_line); i++){
    temp = pgm_read_byte_near(a_line+i);
    Serial.print(temp);
  }
}

void  start_opt_print()
{
  char  temp;
   for(int i=0; i < strlen_P(start_opt_meseage); i++){
    temp = pgm_read_byte_near(start_opt_meseage+i);
    Serial.print(temp);
  }
}

void  try_again(int &cnt)
{
  cnt++;
  Serial.print("!!!!!!!!!plese input the right number(try: ");
  Serial.print(cnt);
  Serial.println(")!!!!!!!!!!");
}

void  start_first_print()
{
  char  temp;
  for(int i=0; i < strlen_P(start_first_meseage); i++){
    temp = pgm_read_byte_near(start_first_meseage+i);
    Serial.print(temp);
  }
  start_opt_print();
 print_aline();
}

void  default_print()
{
  char  temp;
  for(int i=0; i < strlen_P(default_meseage); i++){
    temp = pgm_read_byte_near(default_meseage+i);
    Serial.print(temp);
  }
}
