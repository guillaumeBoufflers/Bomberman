
#include "Serialize.hh"

void			Serialize::serialize(std::vector<std::vector<std::list<IPhysicalObject *> > > &_map, std::vector<APlayer*> &_alivePlayers, std::vector<APlayer *> &_deadPlayers, char *name)
{
  TiXmlDocument		doc;
  TiXmlElement		*main;
  TiXmlDeclaration	*decl = new TiXmlDeclaration("1.0", "", "");
  std::string		pathname(name);

  pathname = pathname + ".xml";
  doc.LinkEndChild(decl);
  main = new TiXmlElement("SAVE");
  for (std::vector<APlayer *>::iterator it = _alivePlayers.begin(); it != _alivePlayers.end(); ++it)
    main->LinkEndChild((*it)->serialize());
  for (std::vector<APlayer *>::iterator it = _deadPlayers.begin(); it != _deadPlayers.end(); ++it)
    main->LinkEndChild((*it)->serialize());
  for (unsigned int y = 0 ; y < _map.size() ; ++y)
    for (unsigned int x = 0 ; x < _map[y].size() ; ++x)
      for (std::list<IPhysicalObject *>::iterator it = _map[y][x].begin(); it != _map[y][x].end(); ++it)
	main->LinkEndChild((*it)->serialize());
  doc.LinkEndChild(main);
  doc.SaveFile(pathname.c_str());
  BUtils::createMd5(pathname);
}

void			Serialize::deserialize(std::vector<std::vector<std::list<IPhysicalObject *> > > &_map, std::vector<APlayer*> &_alivePlayers, std::vector<APlayer *>&_deadPlayers, const char *fich)
{
  TiXmlDocument		doc(fich);
  ObjectType		type;
  TiXmlAttribute	*attr;
  bool			loadOkay = doc.LoadFile();
  APlayer		*tmp1;
  IPhysicalObject	*tmp2;
  std::vector<std::list<IPhysicalObject *> > tmp5;
  std::list<IPhysicalObject *> tmp6;
  int			tmpY = 0;
  int			tmpX = 0;
  std::string		path(fich);

  if (loadOkay != true)
    throw new BombermanException("Fichiers de sauvegardes erronés ou données corrompues.");
  if (BUtils::checkMd5(fich) != true)
    throw new BombermanException("Fichiers de sauvegardes erronés ou données corrompues.");
  for (TiXmlNode *Child = doc.FirstChild()->NextSibling()->FirstChild(); Child != 0; Child = Child->NextSibling())
    {
      if (Child->ToElement() == NULL)
	throw new BombermanException("Fichiers de sauvegardes erronés ou données corrompues.");
      attr = Child->ToElement()->FirstAttribute();
      attr->QueryIntValue(reinterpret_cast<int*>(&type));
      if ( type > PLAYER  && type < BOMB)
	{
	  tmp1 = GDLObjectFactory::getInstance()->createXmlAPlay(type, &attr);
	  for (TiXmlNode *bomb = Child->FirstChild(); bomb != NULL ; bomb = bomb->NextSibling())
	    {
	      tmp1->addToStock(static_cast<ObjectType>(bomb->ToElement()->FirstAttribute()->IntValue()),
			       bomb->ToElement()->FirstAttribute()->Next()->IntValue(),
			       bomb->ToElement()->FirstAttribute()->Next()->Next()->IntValue(),
			       bomb->ToElement()->FirstAttribute()->Next()->Next()->Next()->IntValue());
	    }
	  if (tmp1->getStatus() == DEAD)
	    _deadPlayers.push_back(tmp1);
	  else
	    _alivePlayers.push_back(tmp1);
	}
      else
	{
	  tmp2 = GDLObjectFactory::getInstance()->createXmlIPhys(type, &attr);
	  if (type == EXPLOSION || type > BOMB)
	    {
	      for (std::vector<APlayer *>::iterator it = _alivePlayers.begin(); it != _alivePlayers.end(); it++)
		{
		  if (attr->IntValue() == (*it)->getId())
		    this->setOwner((*it), tmp2);
		}
	      for (std::vector<APlayer *>::iterator it = _deadPlayers.begin(); it != _deadPlayers.end(); it++)
		{
		  if (attr->IntValue() == (*it)->getId())
		    this->setOwner((*it), tmp2);
		}
	    }	
	  if (tmp2->getPosCaseX() == tmpX && tmp2->getPosCaseY() == tmpY)
	    tmp6.push_back(tmp2);
	  else if (tmp2->getPosCaseX() != tmpX && tmp2->getPosCaseY() == tmpY)
	    {
	      tmp5.push_back(tmp6);
	      tmp6.clear();
	      tmp6.push_back(tmp2);
	      tmpX = tmp2->getPosCaseX();
	    }
	  else
	    {
	      _map.push_back(tmp5);
	      tmp5.clear();
	      tmp6.clear();
	      tmp6.push_back(tmp2);
	      tmpY = tmp2->getPosCaseY();
	      tmpX = tmp2->getPosCaseX();
	    }
	}
    }
  tmp5.push_back(tmp6);
  _map.push_back(tmp5);
}

void	Serialize::setOwner(APlayer *play, IPhysicalObject *obj)
{
  Explosion		*exp;
  ABomb			*bomb;
  ToxicCloud		*gaz;

  if (obj->getType() == EXPLOSION)
    {
      exp = static_cast<Explosion *>(obj);
      exp->setPlayer(play);
    }
  if (obj->getType() == TOXICCLOUD)
    {
      gaz = static_cast<ToxicCloud *>(obj);
      gaz->setPlayer(play);
    }
  else
    {
      bomb = static_cast<ABomb *>(obj);
      bomb->setPlayer(play);
    }
}
