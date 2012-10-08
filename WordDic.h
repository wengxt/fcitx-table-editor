#ifndef WORDDIC_H
#define WORDDIC_H

#include <QString>
class WordDic {
public:
  // Constructors
  WordDic(QString inKey, QString inValue) {
      key = inKey;
      value = inValue;
  }
  // Accessor Methods
  QString get_key ( ) {
    return key;
  }
  void set_key (QString value ) {
    key = value;
  }
  QString get_value ( ) {
    return value;
  }
  void set_value (QString value ) {
    value = value;
  }
private:
   QString key;
   QString value;
};
#endif //WORDDIC_H
