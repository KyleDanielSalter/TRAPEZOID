#pragma once

#include "SpaceFighter_client.h"
#include "Map.h"
#include "handle.h"

class HandleManager {
public:
	HandleManager() : nextAvailableKey(0) {}

	//Clears the entries container
	void reset();
	/*
	Adds the sent pointer to the container
	@param dataPtr a pointer to the data to be stored
	@param type an uint32 as a identifier of the type
	@return the handle containing the the key value of the pointer
	*/
	Handle add(void* dataPtr, const HandleType type);
	/*
	Updates the pointer at denoted by param handle. can not change types
	@param handle the handle containing the key value of the pointer
	@param dataPtr a pointer to the data to be stored
	@return whether the update was successful. fails if handle is invalid
	*/
	bool update(const Handle handle, void* dataPtr);
	/*
	Erases the index denoted by the handle
	@param handle the handle containing the key value of the pointer
	@return whether the update was successful. false if handle is invalid
	*/
	bool remove(const Handle handle);
	/*
	Returns the data pointer denoted by handle.
	@param handle the handle containing the key value of the pointer
	@return the stored pointer. NULL if handle is invalid
	*/
	void* get(const Handle handle);
	/*
	Assigns the data pointer denoted by handle to out
	@param handle the handle containing the key value of the pointer
	@param out a NULL pointer to be assign to a data pointer if handle is valid
	@return whether the get was successful. false is handle is invalid
	*/
	bool get(const Handle handle, void*& out);

private:
	uint32 nextAvailableKey;
	uint32 generateKey();

	struct HandleEntry {
		HandleEntry(const HandleType newType, void* dataPtr) : type(newType), entry(dataPtr) {}
		HandleType type;
		void* entry;
	};
	//Hash table of entries. No duplicate keys
	TMap<uint32, HandleEntry> entries;
};
