
#pragma once

#include "AttributeDefinition.h"

namespace dbcppp
{
	class AttributeDefinitionImpl
		: public AttributeDefinition
	{
	public:
		AttributeDefinitionImpl(std::string&& name, ObjectType object_type, value_type_t value_type);
		AttributeDefinitionImpl(AttributeDefinitionImpl&&) = default;
		AttributeDefinitionImpl& operator=(AttributeDefinitionImpl&&) = default;
		virtual ObjectType getObjectType() const override;
		virtual const std::string& getName() const override;
		virtual const value_type_t& getValueType() const override;

		std::string _name;
		ObjectType _object_type;
		value_type_t _value_type;
	};
}
