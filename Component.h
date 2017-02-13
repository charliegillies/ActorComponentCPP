// Charlie Gillies, 11-02-2017

#pragma once
class Actor;

/*
	A component is one of many pieces of 'Actor'
	Components tend to be composite objects, but in edge cases
	and places where it would make sense - they can be behavioural too.
*/
class Component
{
public:
	Component() { };
	virtual ~Component() { }
	
	/*
		Gets the id of the component that is usually set
		in a deriving const static member 'ID'.

		@return the id of the deriving component type.
	*/
	virtual const int getId() = 0;
};