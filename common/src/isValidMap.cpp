#include	"isValidMap.hh"
#include	"utils.hh"
#include	"enum.hh"

namespace 	GameMap
{
	bool		isValidMap(const std::string &file, int nbPlayers)
	{
		std::ifstream fichier(file.c_str(), std::ios::in);
		std::string	data;
		std::vector<std::vector <std::string> > save;
		std::vector<std::string> objs;
		int		plays = 0;

		if(fichier)
		{
			while (getline(fichier, data))
			{
				data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());
				objs = BUtils::split(' ', data);
				for (std::vector<std::string>::iterator it = objs.begin() ; it != objs.end() ; ++it)
				{
					if (BUtils::isNum((*it)) == false)
					{
						return (false);
					}
					if (BUtils::stringToInt((*it)) > MAXOBJ)
					{
						return (false);
					}
					if (BUtils::stringToInt((*it)) == PLAYER)
						plays++;
				}
				save.push_back(objs);
			}

			for (std::vector<std::vector<std::string> >::const_iterator it = save.begin() ; it != save.end() ; ++it)
			{
				if (save.size() != (*it).size())
				{
					return (false);
				}
			}
			fichier.close();
		}
		if (plays < nbPlayers)
			return (false);
		return (true);
	}
}
