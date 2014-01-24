#include		"Save.hh"

Save::Save(std::map<int, Object *> list, std::string name, int size, int players, int rate)
{
  this->_list = list;
  this->_name = name;
  this->_size = size;
  this->_players = players;
  this->_rate = rate;
}

Save::~Save()
{

}

bool		Save::isExisting(std::string &name)
{
  std::string	error;
  DIR		*d;
  struct dirent *dr;

  if ((d = opendir("../maps")) == NULL)
    return (true);
  while ((dr = readdir(d)) != NULL)
    if (dr->d_name == (name + ".map"))
      {
	error = "file ";
	error += name;
	error += " already exists";
	errorWindow(error, "error");
	return (true);
      }
  closedir(d);
  return (false);
}

void		Save::run()
{
  std::ofstream objetfichier;
  std::string	name;
  ObjectType	t;
  int		iter = 1;
  int		i = 1;
  
  name = "../maps/";
  name = name + this->_name + ".map";
  if (isExisting(this->_name) == false)
    {
      if (this->_list.size() != 0)
	{
	  objetfichier.open(name.data(), std::ios::app);
	  for (std::map<int, Object *>::iterator it = this->_list.begin(); it != this->_list.end(); ++it)
	    {
	      t = (*it).second->getType();
	      if (t == BONUS)
		t = BONUSRANDOM;
	      else if (t == BONUSCLAYMORE)
		t = BONUSRANDOM;
	      std::string s = intToString(t);
	      objetfichier.write(reinterpret_cast<const char *>(s.data()), s.size());
	      if (iter == this->_size)
		{
		  i++;
		  iter = 0;
		  objetfichier.write(reinterpret_cast<const char *>("\n"), 1);
		}
	      else
		objetfichier.write(reinterpret_cast<const char *>(" "), 1);
	      iter++;
	    }
	  objetfichier.close();
	  errorWindow("Your map is now saved", "information");
	}
      else
	errorWindow("Your map is not generated", "Save error");
    }
}
