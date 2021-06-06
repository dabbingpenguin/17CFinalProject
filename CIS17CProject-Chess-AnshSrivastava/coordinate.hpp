#ifndef COORDINATE_HPP
#define COORDINATE_HPP

namespace chess
{
enum { BLANK, A, B, C, D, E, F, G, H};

struct coordinate
{
  int rank;
  int file;
  coordinate()
  {
   file = 0;
   rank = 0;
  }
  inline int getNum()
  {
    return 8*(rank-1) + file - 1;
  }
};

inline coordinate getCoordinate(int num)
{
 coordinate ret;
 ret.file = (num + 9) % 8;
 ret.rank = (num + 9 - ret.file)/8;
 return ret;
}
}

#endif
