
#include "auto_system.h"
String input_name()
{
  String name;
  name = "";
  Serial.println("Input the object name");
  print_input_guide();
   while (1)
   {
     if (Serial.available() >= 1)
    {
      name = Serial.readString();
      Serial.print("The name is :");
      Serial.println(name);
      return (name);
    }
  }
}

int input_delay_time()
{
  int delay_time;
  Serial.println("Input the delay Time (second)");
  print_input_guide();
   while (1)
   {
     if (Serial.available() >= 1)
    {
      delay_time = Serial.parseInt();
      Serial.print("The delay_time is :");
      Serial.print(delay_time);
      Serial.println("(second)");
      return (delay_time);
    }
    }
}

int input_quantity()
{
  int quantity;
  Serial.println("Input the quantity");
  print_input_guide();
   while (1)
   {
     if (Serial.available() >= 1)
    {
      quantity = Serial.parseInt();
      Serial.print("The quantity is :");
      Serial.println(quantity);
      return (quantity);
    }
    }
}


void print_obj_type_choice()
{
  char  temp;
  for(int i=0; i < strlen_P(obj_type_choice_meseage); i++){
    temp = pgm_read_byte_near(obj_type_choice_meseage+i);
    Serial.print(temp);
  }
}

t_object_type input_obj_type()
{
  int type;
  print_obj_type_choice();
   while (1)
   {if (Serial.available() >= 1)
    {
      type = Serial.parseInt();
      switch (type)
      {
        case 1 :  Serial.println("The type is : liquid ");
                return(liquid);
        case 2 :  Serial.println("The type is : solid ");
                return (solid);
        case 3 :  Serial.println("The type is : gas ");
                return (gas);
        default :
              Serial.println("please input right type");
              print_obj_type_choice();
    }
    }
  }
}

semiconductor  make_new_object(void)
{
  String name;
  int delay_time;
  int quantity;
  t_object_type obj_type;

  Serial.println("\n----------------------------------------------------");
  Serial.println("Now you can Create new object setting to produce");
  name = input_name();
  delay_time = input_delay_time();
  quantity = input_quantity();
  obj_type = input_obj_type();
  semiconductor obj(name, delay_time, quantity,obj_type);
  return (obj);
}