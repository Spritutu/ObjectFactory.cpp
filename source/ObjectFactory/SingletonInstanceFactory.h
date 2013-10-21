#pragma once

#include <tchar.h>
#include <string>
#include <map>

#include "IInstanceFactory.h"

class IContainer;
class IInstantiator;

class SingletonInstanceFactory : public IInstanceFactory
{
public:
	SingletonInstanceFactory();

	_Acquires_exclusive_lock_(this->_mutex)
	_Releases_exclusive_lock_(this->_mutex)
	virtual ~SingletonInstanceFactory();

	virtual void SetCreationStrategy(_In_z_ LPCSTR interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator);

	_Acquires_exclusive_lock_(this->_mutex)
	_Releases_exclusive_lock_(this->_mutex)
	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_z_ LPCSTR interfaceTypeName);

	_Acquires_exclusive_lock_(this->_mutex)
	_Releases_exclusive_lock_(this->_mutex)
	virtual void Remove(_In_z_ LPCSTR interfaceTypeName);

	int GetNumberOfInstances() const;

private:
	std::recursive_mutex _mutex;

	_Guarded_by_(_mutex)
	std::map<std::string, std::shared_ptr<void>> _instances;
	std::map<std::string, std::shared_ptr<IInstantiator>> _instantiators;
};
