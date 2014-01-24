#include	<string>

bool		isNum(std::string str)
{
  int     i;

  i = -1;
  while (str[++i])
    if (!(str[i] <= '9' && str[i] >= '0'))
      return (false);
  return (true);
}
