#include "detection.h"

detection::detection()
{

}

int detection::Hextoi(QString s,int len)
{
  int i;
  int n = 0;

  if(s.length()<len) return 0;

  for (i=0;i<len;++i)
  {
        if (s.at(i) > '9')
        {
            n = 16 * n + (10 + s.at(i).toLatin1() - 'A');
        }
        else
        {
            n = 16 * n +( s.at(i).toLatin1() - '0');
        }
   }
   return n;
}
