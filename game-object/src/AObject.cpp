#include	"AObject.hh"

AObject::AObject(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, ObjectType globalType) : APhysicalObject(x, y, scale, angle, mesh, type, globalType)
{

}

AObject::AObject(TiXmlAttribute **attrib) : APhysicalObject(attrib)
{

}

AObject::~AObject()
{

}

TiXmlElement *AObject::serialize()
{
  TiXmlElement	*ret;

  ret = APhysicalObject::serialize();
  return (ret);
}
