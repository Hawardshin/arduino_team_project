#include "auto_system.h"

void  main_page(void)
{
 semiconductor obj[11];
 semiconductor default_obj;
 obj[0] = default_obj;
  int cnt = 1;
  start_first_print();
  int obj_num = 1;
  while (1)
  {
    if (Serial.available() >= 1)
    {
      int num = Serial.parseInt();
      Serial.print("You choose ::::  ");
      Serial.println(num);
      switch(num)
      {
        case 1 :
                if (obj_num == 10)
                {
                  Serial.println("TOO many object you can't add more object");
                  break;
                }
                obj[obj_num] = make_new_object();
                cnt = 0;
                obj_num++;
                break;
        case 2 :
                if (obj_num == 1)
                {
                  Serial.println("there is no object");
                  continue ;
                }
                choose_object(obj, obj_num);
                cnt = 0;
                break;
        case 3 : operate_machine(obj, obj_num);
                cnt =0;
                break;
        case 4 : off_machine();
                return (1);
        default : try_again(cnt); //if not available input 5times off it
                  cnt++;
                  break;
      }
      start_first_print();
      if (cnt == 5)
      {
        char temp;
          for(int i=0; i < strlen_P(try_five); i++){
          temp = pgm_read_byte_near(try_five+i);
          Serial.print(temp);
        }
          break;
      }
    }
  }
}