#include "realrepoapiclasses.h"
#include <QDebug>

using namespace QRealTypes;

int RealNamedEntity::getId() 
{
	return m_id;
}

void RealNamedEntity::setId( const int id )
{
	m_id = id;
}

QString RealNamedEntity::getName() const
{
	return m_name;
}

void RealNamedEntity::setName( const QString& arg ) 
{
	m_name = arg;
}

QString RealNamedEntity::getDescription() const
{
	return m_description;
}

void RealNamedEntity::setDescription( const QString& arg ) 
{
	m_description = arg;
}

void RealNamedEntity::setProperty( const QString& name, const QString& val )
{
	m_properties[name] = val;
}

QString RealNamedEntity::getProperty( const QString& name ) const
{
	return m_properties[name];
}

int RealNamedEntity::getPropertiesCount() const
{
	return m_properties.count();
}

// ================================================== //

MetaType RealType::getMetaType() const
{
	return m_metatype;
}

void RealType::setMetaType( const MetaType arg )
{
	m_metatype = arg;
}

QIntList RealType::getObjects() const 
{
	return m_objects;
}

void RealType::addObject( const int id ) 
{
	if( !m_objects.contains(id) )
		m_objects << id;
}

QString RealType::toString() const
{
qDebug() << 1;
	QString res = QString("%1\t%2\t%3\t%4\t").arg(m_id).arg(m_name).arg(m_description).arg(m_metatype);
qDebug() << 2;

	res += QString("%1\t").arg(m_objects.size());
qDebug() << 3;
	for( int i=0; i<m_objects.size(); i++)
		res += QString("%1\t").arg(m_objects.at(i));

qDebug() << 4;
	res += QString("%1\t").arg(m_properties.size());
qDebug() << 5;
	for( int i=0; i<m_properties.keys().size(); i++){
		 res += QString("%1;%2\t").arg(m_properties.keys().at(i)).arg(m_properties.value(m_properties.keys().at(i)));
	}
qDebug() << 6;
	return res;
}
	
void RealType::loadFromString( const QString& data )
{
	m_id = data.section("\t",0,0).toInt();
	m_name = data.section("\t",1,1);
	m_description = data.section("\t",2,2);
	m_metatype = (MetaType) data.section("\t",3,3).toInt();
	
	int objCounter = data.section("\t",4,4).toInt();
	int counter = 5;
	for( int i=0; i<objCounter; i++ ){
		m_objects << data.section("\t",counter, counter).toInt();
		counter++;
	}	
	
	int propsCount = data.section("\t",counter,counter).toInt();
	counter++;
	for( int i=0; i<propsCount; i++ ){
		QString pair = data.section("\t",counter,counter);
		setProperty(pair.section(";",0,0), pair.section(";",1,1));
		counter++;
	}	

}

// ================================================== //

int RealObject::getTypeId() const
{
	return m_typeId;
}

void RealObject::setTypeId( const int arg )
{
	m_typeId = arg;
}

bool RealObject::getVisibility() const 
{
	return m_visibility;
}

void RealObject::setVisibility( const bool arg )
{
	m_visibility = arg;
}

int RealObject::getContainerId() const
{
	return m_containerId;
}

void RealObject::setContainerId( const int arg )
{
	m_containerId = arg;
}

QString RealObject::getConfiguration() const 
{
	return m_configuration;
}

void RealObject::setConfiguration( const QString& arg )
{
	m_configuration = arg;
}

QIntList RealObject::getChildElements() const 
{
	return m_children;
}

void RealObject::addChildElement( const int arg )
{
	if( !m_children.contains(arg) )
		m_children << arg;
}

void RealObject::deleteChildElement( const int arg )
{
	if( m_children.contains(arg) )
		m_children.removeAll(arg);
}

QIntList RealObject::getAllLinks() const 
{
	return m_links;
}

void RealObject::addLink( const int id )
{
	if( !m_links.contains(id) )
		m_links << id;
}

// ================================================== //

int RealLink::getTypeId() const
{
	return m_type;
}

void RealLink::setTypeId( const int arg )
{
	m_type = arg;
}

int RealLink::getFromId() const 
{
	return m_fromId;
}

int RealLink::getToId() const 
{
	return m_toId;
}

void RealLink::setFromId( const int arg )
{
	m_fromId = arg;
}

void RealLink::setToId( const int arg )
{
	m_toId = arg;
}
