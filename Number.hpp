#ifndef NUMBER_HPP
#define NUMBER_HPP
class Number {
private:
  int num;
public:
  Number() {
    num = 0;
  }
  Number(bool space) {
    if (space)
      num = 0;
    else
      num = 2;
  }
  Number(const Number* n) {
    num = n->getVal();
  }
  void doubleVal() {
    num*=2;
  }
  int getVal() const {
    return num;
  }
  bool isNum() {return num>0;}
  bool blank() {return num<2;}
  void initNum() {num = 0; return;}
};

#endif
