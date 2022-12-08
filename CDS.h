#ifndef CDS_H
# define CDS_H
class CDS{
  int PIN;
  int INTEN;
  int cds;
  
public: 
  CDS(int pin, int intensity, int state);
  void update();
  int STATE;
};

#endif 