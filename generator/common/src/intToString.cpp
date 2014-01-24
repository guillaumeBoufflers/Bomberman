#include		<sstream>
#include		<string>

std::string		intToString(int a)
{
  std::stringstream convert;

  convert << a;
  return (convert.str());
}
