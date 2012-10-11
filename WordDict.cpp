#include "WordDict.h"

bool operator==(const WordDict &left, const WordDict &right) {
  return (left.get_key() == right.get_key()) &&
          (left.get_index() == right.get_index());
}
bool operator!=(const WordDict &left, const WordDict &right) {
  return !(left == right);
}
bool operator<(const WordDict &left, const WordDict &right) {
  if (left.get_key() < right.get_key())
    return true;
  else if(left.get_key() == right.get_key())
    return left.get_index() < right.get_index();
  return false;
}
