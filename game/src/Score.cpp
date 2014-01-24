
#include "Score.hh"

Score	*Score::_instance = NULL;

Score::Score()
{
  TiXmlDocument		doc("Score.xml");
  bool			loadOkay = doc.LoadFile();
  std::string		fich("Score.xml");
  
  if (loadOkay != true)
    return ;
  if (BUtils::checkMd5(fich) != true)
    throw new BombermanException("Fichiers de sauvegardes erronés ou données corrompues.");
  if (doc.FirstChild()->NextSibling() == NULL
      || doc.FirstChild()->NextSibling()->FirstChild() == NULL)
    throw new BombermanException("Fichiers de sauvegardes erronés ou données corrompues.");
  for (TiXmlNode *Child = doc.FirstChild()->NextSibling()->FirstChild(); Child != 0; Child = Child->NextSibling())
    {
      if (Child->ToElement() == NULL)
	throw new BombermanException("Fichiers de sauvegardes erronés ou données corrompues.");
      this->_score.push_back(Child->ToElement()->FirstAttribute()->IntValue());
      this->_player.push_back(Child->ToElement()->FirstAttribute()->Next()->Value());
    }
}

Score::~Score()
{
  
}

void Score::setFich()
{
  TiXmlDocument		doc;
  TiXmlElement		*main;
  TiXmlDeclaration	*decl = new TiXmlDeclaration("1.0", "", "");
  TiXmlElement		*ret;
  int			i;

  i = 0;
  if (this->_score.empty() == true)
    return ;
  doc.LinkEndChild(decl);
  main = new TiXmlElement("SCORE");
  for (std::list<int>::iterator it = this->_score.begin(); it != this->_score.end() && i < 5 ; ++it)
    {
      ret = new TiXmlElement("Score");
      ret->SetAttribute("point", (*it));
      ret->SetAttribute("player", this->_player[i].c_str());
      main->LinkEndChild(ret);
      i++;
    }
  doc.LinkEndChild(main);
  doc.SaveFile("Score.xml");
  BUtils::createMd5("Score.xml");
}

Score	*Score::getInstance()
{
  if (_instance == NULL)
    _instance = new Score();
  return (_instance);
}

void			Score::deleteInstance()
{
  if (_instance != NULL)
    delete _instance;
  _instance = NULL;
}

std::vector<std::string> Score::getScore()
{
  return (this->_player);
}

void		Score::setScore(int nb, int play)
{
  bool		push = false;
  std::list<int> new_list;
  std::vector<std::string> new_vector;
  std::string	tmp;
  int		i = 0;
  int		j = -1;
  std::stringstream	a;

  if (nb == 0)
    return ;
  for (std::list<int>::iterator it = this->_score.begin(); it != this->_score.end(); ++it)
    {
      if ((*it) <= nb && push == false)
  	{
	  new_list.push_back(nb);
  	  push = true;
  	}
      if (push == false)
	{
	  i++;
	}
      new_list.push_back((*it));
    }
  tmp = (play == 1)?("Player 1"):("Player 2");
  a << nb;
  tmp = tmp + ": " + a.str();
  for (std::vector<std::string>::iterator it = this->_player.begin(); it != this->_player.end(); it++)
    {
      if (j == i)
	new_vector.push_back(tmp);
      new_vector.push_back((*it));
      j++;
    }
  if (push == false)
    {
      new_list.push_back(nb);
      new_vector.push_back(tmp);
    }
  this->_score = new_list;
  this->_player = new_vector;
}
