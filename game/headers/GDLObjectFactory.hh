#ifndef			__GDLOBJECTFACTORY_HH__
#define			__GDLOBJECTFACTORY_HH__

#include		"IGDLObjectFactory.hh"

class			GDLObjectFactory : public IGDLObjectFactory
{
  static IGDLObjectFactory		*_instance;

  IPhysicalObject	*(GDLObjectFactory::*tab[2])(int, int, int, int, std::string &, ObjectType, APlayer *);
  APlayer		*(GDLObjectFactory::*tabPlay[2])(int, int, int, int, std::string &, ObjectType, int, int, int, int);
  IPhysicalObject	*(GDLObjectFactory::*tabObj[18])(int, int, int, int, std::string &, ObjectType);
  IPhysicalObject	*(GDLObjectFactory::*tabBomb[7])(int, int, int, int, std::string &, int, int, APlayer *);

  IPhysicalObject	*(GDLObjectFactory::*tabXmlIPhys[35])(TiXmlAttribute **);
  APlayer		*(GDLObjectFactory::*tabXmlAPlay[2])(TiXmlAttribute **);

  // Constructeur template des bombes
  template <class T>
  IPhysicalObject	*create(int x, int y, int scale, int angle, std::string &mesh, int puissance, int dispo, APlayer *player)
  {
    return (new T(x, y, scale, angle, mesh, puissance, dispo, player));
  }

  template <class T>
  IPhysicalObject	*create(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, APlayer *player)
  {
    return (new T(x, y, scale, angle, mesh, type, player));
  }
  // constructeur template des Players
  template <class T>
  APlayer	*create(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, int id, int life, int range, int start)
  {
    return (new T(x, y, scale, angle, mesh, type, id, life,range, start));
  }
  // constructeur template des objects
  template <class T>
  IPhysicalObject	*create(int x, int y, int scale, int angle, std::string &mesh, ObjectType type)
  {
    return (new T(x, y, scale, angle, mesh, type));
  }

  template <class T>
  IPhysicalObject	*create(TiXmlAttribute **attr)
  {
    return (new T(attr));
  }

  template <class T>
  APlayer		*create(TiXmlAttribute **attr)
  {
    return (new T(attr));
  }

public:
  GDLObjectFactory();
  virtual ~GDLObjectFactory();
  static  IGDLObjectFactory	*getInstance();
  static  void			deleteInstance();
  virtual IPhysicalObject	*createABomb(int, int, int, int, std::string &, ObjectType, int, int, APlayer *);
  virtual APlayer		*createAPlayer(int, int, int, int, std::string &, ObjectType, int, int, int, int);
  virtual IPhysicalObject	*createAObject(int, int, int, int, std::string &, ObjectType);
  virtual IPhysicalObject	*createObjSpec(int, int, int, int, std::string &, ObjectType, APlayer *);
  virtual APlayer		*createXmlAPlay(ObjectType, TiXmlAttribute **);
  virtual IPhysicalObject	*createXmlIPhys(ObjectType, TiXmlAttribute **);
};
#endif
