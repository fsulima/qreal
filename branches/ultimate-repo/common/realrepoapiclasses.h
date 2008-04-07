#ifndef __REAL_REPO_API_CLASSES_H__
#define __REAL_REPO_API_CLASSES_H__

#include <QList>
#include <QMap>
#include <QString>

namespace QRealTypes
{
	typedef QList<int> QIntList;

	// common stuff for all classes
	class RealNamedEntity
	{
	public:
		RealNamedEntity() 
		{
			m_name = "noname";
			m_description = "noname";
			m_properties.clear();
		}

		int getId();
		void setId( const int id ); // to be removed soon

		QString getName() const;
		void setName( const QString& );

		QString getDescription() const;
		void setDescription( const QString& );

		void setProperty( const QString& name, const QString& val );
		QString getProperty( const QString& name ) const; // returns "" in case of empty property value
		int getPropertiesCount() const; 

	protected:
		int m_id;
		QString m_name;
		QString m_description;
		QMap<QString, QString> m_properties;	
	};

	// Metatype description
	enum MetaType
	{
		object, // types of diagram objects (e.g. invoke, exit, if, foreach, throw, reply)
		link, // edges
		dataType, // all common data types: basic (int, double, string, char) and
			// defined by user ( records/structs, xsd etc.)
		rawType, // 'raw' string data types (e.g. wsdl, xsd, project configuration stuff etc.)
	};

	typedef enum MetaType MetaType;

	// Type description
	class RealType : public RealNamedEntity
	{
	public:
		RealType() { m_objects.clear(); }

		MetaType getMetaType() const; 
		void setMetaType( const MetaType );

		QIntList getObjects() const; // returns all objects of this particular type
		
		void addObject( int id );

		QString toString() const;
		void loadFromString( const QString& );
	
	private:

		MetaType m_metatype;
		QIntList m_objects;
	};

	// Node elements
	class RealObject : public RealNamedEntity
	{
 	public:
		int getTypeId() const;
		void setTypeId( const int );

		bool getVisibility() const; // is it visible on the diagrams or not
		void setVisibility( const bool );

		int getContainerId() const; 
		void setContainerId( const int );

		QString getConfiguration() const;
		void setConfiguration( const QString& );

		QIntList getChildElements() const;
		void addChildElement( const int );
		void deleteChildElement( const int );

		QIntList getAllLinks() const;
		void addLink( const int id );
		
		QIntList getIncomingLinks() const { return QIntList(); };
 		QIntList getOutcomingLinks() const { return QIntList(); };
		void addIncomingLink( const int ) {};
		void addOutcomingLink( const int ) {};

	private:
		int m_typeId;
		bool m_visibility;
		int m_containerId;
		QString m_configuration;

		QIntList m_children;
		QIntList m_links;
	};

	// Edge elements
	class RealLink : public RealNamedEntity
	{
	public:
		int getTypeId() const;
		void setTypeId( const int );

		int getFromId() const;  // source node
		void setFromId( const int );

		int getToId() const;    // target node
		void setToId( const int );
	
	private:
		int m_type;

		int m_fromId;
		int m_toId;
	};
}

#endif // __REAL_REPO_API_CLASSES_H__
