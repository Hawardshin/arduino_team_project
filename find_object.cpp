#include "auto_system.h"

int  find_obj(semiconductor *obj, String find_name, int obj_num)
{
  int i;

  i = 1;
  while (i <= obj_num)
  {
    if (obj[i].ret_name() == find_name)
      return (i);
    i++;
  }
  return (-1);
}

void  print_choose_message()
{
  char  temp;
   for(int i=0; i < strlen_P(choice_meseage); i++){
    temp = pgm_read_byte_near(choice_meseage+i);
    Serial.print(temp);
  }
}

void  choose_object(semiconductor *obj,int obj_num)
{
  String find_name = "";

 print_choose_message();
   while (1)
   {
     if (Serial.available() >= 1)
      {
        find_name = Serial.readString();
        Serial.print("you input :: ");
        Serial.println(find_name);
        if (find_name == "back")
        {
            Serial.println("--------------go_back menu---------------------");
            return (0);
        }
        if (find_name == "default")
        {
          obj[0].print_info();
          print_choose_message();
          continue ;
        }
        int idx = find_obj(obj, find_name,obj_num);
        if (idx == -1)
            Serial.println("--------there is no match obj that name--------");
        else
        {
           Serial.println("--------!!!!! find !!!! -----------");
           obj[idx].print_info();
        }
        print_choose_message();
    }
  }
}

void  print_obj_list_name(semiconductor *obj,int obj_num)
{
  Serial.println("\n----the object list----");
  for (int i=0; i < obj_num; i++)
  {
    Serial.print("idx : ");
    Serial.println(i);
    if (i != 0)
      Serial.println(obj[i].ret_name());
    else 
        Serial.println("default");
  }
  Serial.println("choose the idx what you want to opperate");
}