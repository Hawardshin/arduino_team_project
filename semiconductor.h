#ifndef SEMICONDUCTOR_H
# define SEMICONDUCTOR_H
typedef enum e_object_type
{
  liquid = 1,
  solid ,
  gas,
} t_object_type;

class semiconductor
{
  public :
          semiconductor();
          semiconductor(String _name, int _delay_time, int _quantity, t_object_type _obj_type);
          void  print_obj_type(void);
          void  print_info(void);
          String ret_name();
          int    ret_quantity();
          int    ret_delay_time();

  private : String name;// to_make_things name
            int delay_time;//to make one object spend time
            int quantity; //the number of to make_object
            t_object_type obj_type; //type of object
};

#endif