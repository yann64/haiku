/*
 * Copyright 2013, Ingo Weinhold, ingo_weinhold@gmx.de.
 * Distributed under the terms of the MIT License.
 */
#ifndef KERNEL_BOOT_PATH_BLOCKLIST_H
#define KERNEL_BOOT_PATH_BLOCKLIST_H


#include <string.h>

#include <util/SinglyLinkedList.h>


class BlockedPath : public SinglyLinkedListLinkImpl<BlockedPath> {
public:
								BlockedPath();
								~BlockedPath();

			bool				SetTo(const char* path);

			bool				Append(const char* component);

			const char*			Path() const
									{ return fPath != NULL ? fPath : ""; }

			size_t				Length() const
									{ return fLength; }

			bool				operator==(const char* path) const
									{ return strcmp(Path(), path) == 0; }

private:
			bool				_Resize(size_t length, bool keepData);

private:
			char*				fPath;
			size_t				fLength;
			size_t				fCapacity;
};


class PathBlocklist {
public:
			typedef SinglyLinkedList<BlockedPath>::Iterator Iterator;

public:
								PathBlocklist();
								~PathBlocklist();

			bool				Add(const char* path);
			void				Remove(const char* path);
			bool				Contains(const char* path) const;
			void				MakeEmpty();

			bool				IsEmpty() const
									{ return fPaths.IsEmpty(); }

			Iterator			GetIterator() const
									{ return fPaths.GetIterator(); }

private:
			BlockedPath*	_FindPath(const char* path) const;

private:
			typedef SinglyLinkedList<BlockedPath> PathList;

private:
			PathList			fPaths;
};


#endif	// KERNEL_BOOT_PATH_BLOCKLIST_H
