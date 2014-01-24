#ifndef			__SERIALIZE_HH__
#define			__SERIALIZE_HH__

#include		"utils.hh"
#include		"GDLObjectFactory.hh"

class			Serialize
{
public:
  void			serialize(std::vector<std::vector<std::list<IPhysicalObject *> > > &, std::vector<APlayer*> &, std::vector<APlayer*> &, char *);
  void			deserialize(std::vector<std::vector<std::list<IPhysicalObject *> > > &, std::vector<APlayer*> &, std::vector<APlayer *>&, const char *);
  void			setOwner(APlayer *, IPhysicalObject *);
};

#endif
