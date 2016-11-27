#pragma once

#include <boost\function.hpp>

template <class Product>
class ObjectFactory
{
	typedef Product* (*FactoryMethod)(IHWMCSIMechanism&, EHWMCSIDimension, std::map<std::string, std::string>&);
	typedef std::map<std::string, FactoryMethod> FactoryMap;

private:
	ObjectFactory(void) {}
	~ObjectFactory(void) {}
	FactoryMap factoryMap;

	FactoryMethod* getFactoryMethod(const std::string& name)
	{
		FactoryMethod* factoryMethod = 0;

		FactoryMap::iterator iter = factoryMap.find(name);

		if (factoryMap.end() != iter)
		{
			factoryMethod = iter->second;
		}

		return factoryMethod;
	}

public:
	bool RegisterFactoryMethod(const std::string& name, FactoryMethod factoryMethod)
	{
		bool result = false;

		FactoryMap::iterator iter = factoryMap.lower_bound(name);

		if ((factoryMap.end() == iter)  || (factoryMap.key_comp()(name, iter->first)))
		{
			factoryMap.insert(iter, make_pair(name, creator));
		
			result = true;
		}
	
		return result;
	}

	Product* create(const std::string& name, IHWMCSIMechanism& mechanism_, EHWMCSIDimension dimension_, std::map<std::string, std::string>& parameters)
	{
		Product* product = 0;

		FactoryMethod* factoryMethod = getFactoryMethod(name);

		if (0 != factoryMethod)
		{
			product = factoryMethod();
		}

		return product;
	}


	static ObjectFactory* Instance()
	{
		static ObjectFactory* myInstance = 0;

		if (0 == myInstance)
		{
			myInstance = new ObjectFactory;
		}

		return myInstance;
	}
};
