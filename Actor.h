// Charlie Gillies, 11-02-2017

#pragma once
#include <map>
#include "Component.h"
#include <memory>

typedef std::map<int, std::shared_ptr<Component>> ComponentMap;

/*
	An actor is a bag of components.
*/
class Actor
{
private:
	ComponentMap _componentMap;
	std::string _id;

public:
	Actor(std::string id) : _id(id) { }
	Actor() : _id("") { }
	~Actor() { }

	/*
		Checks if the internal id of the actor matches the given id.

		@param id a string id to be compared internally to the _id string member.
		@return boolean indicating if the two ids match or not.
	*/
	bool idMatches(std::string id)
	{
		return _id == id;
	}
	
	/*
		Checks if this Actor owns a particular component.

		@param T must be a type that derives from 'Component'
		@return boolean value indicating if this actor has that component.
	*/
	template <class T>
	bool hasComponent()
	{
		// ensure the given type derives from Component
		if (!std::is_base_of<Component, T>::value) {}

		// get the id of the component type, this is is a static const field
		const int id = T::ID;
		std::shared_ptr<Component> ptr = _componentMap[id];
		return ptr != nullptr;
	}

	/*
		Gets a component from a specific template type.
		The component must contain a public const static field 'ID'
		which is unique to the type of the component.

		@param T must be a type that derives from 'Component'
		@return a shared_ptr holding the desired component.
	*/
	template <class T>
	std::shared_ptr<T> getComponent()
	{
		// ensure the given type derives from Component
		if (!std::is_base_of<Component, T>::value) { }

		// get the id of the component type, this is is a static const field
		const int id = T::ID;

		std::shared_ptr<Component> ptr = _componentMap[id];

		return ptr == nullptr ? nullptr : std::dynamic_pointer_cast<T, Component>(ptr);
	}

	/*
		Creates a component inside of the actor with the given type T.

		@param T must be a type that derives from 'Component'.
		@return a shared_ptr referencing the desired component.
	*/
	template <class T>
	std::shared_ptr<T> createComponent()
	{
		// ensure the given type derives from Component
		if (!std::is_base_of<Component, T>::value) {}

		// get the id of the component type, this is is a static const field
		const int id = T::ID;

		// ensure we don't already have a component of this type, throw an exception if we do.
		std::shared_ptr<Component> existingPtr = _componentMap[id];
		if (existingPtr != nullptr)
			throw("createComponent<T>() called where a component of type T already exists.");

		// create a pointer with our base type, 
		std::shared_ptr<Component> basePtr = std::make_shared<T>();
		_componentMap[id] = basePtr;

		return std::dynamic_pointer_cast<T, Component>(basePtr);
	}
};