#ifndef WORDDICT_H
#define WORDDICT_H

#include <QString>
class WordDict {
public:
  // Constructors
  WordDict() { index = 0; }
  WordDict(const QString &inKey, const int &inIndex) {
      key = inKey;
      index = inIndex;
  }
  // Accessor Methods
  QString get_key ( ) const {
    return key;
  }
  void set_key (const QString &inKey ) {
    key = inKey;
  }
  int get_index( ) const {
    return index;
  }
  void set_index (const int &inIndex ) {
    index = inIndex;
  }
private:
   QString key;
   int index;
};

bool operator==(const WordDict &left, const WordDict &right);
bool operator!=(const WordDict &left, const WordDict &right);
bool operator<(const WordDict &left, const WordDict &right);

#endif //WORDDICT_H
