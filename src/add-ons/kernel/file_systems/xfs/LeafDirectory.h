/*
 * Copyright 2020, Shubham Bhagat, shubhambhagat111@yahoo.com
 * All rights reserved. Distributed under the terms of the MIT License.
 */
#ifndef _LEAFDIRECTORY_H_
#define _LEAFDIRECTORY_H_


#include "Extent.h"
#include "Inode.h"
#include "system_dependencies.h"


#define HEADER_MAGIC 0x58443244


enum ContentType { DATA, LEAF };


//xfs_dir2_leaf_hdr_t
struct ExtentLeafHeader {
			BlockInfo			info;
			uint16				count;
			uint16				stale;
};


// xfs_dir2_leaf_tail_t
struct ExtentLeafTail {
			uint32				bestcount;
				// # of best free entries
};


class LeafDirectory {
public:
								LeafDirectory(Inode* inode);
								~LeafDirectory();
			status_t			Init();
			bool				IsLeafType();
			void				FillMapEntry(int num, ExtentMapEntry* map);
			status_t			FillBuffer(int type, char* buffer,
									int howManyBlocksFurthur);
			void				SearchAndFillDataMap(int blockNo);
			ExtentLeafEntry*	FirstLeaf();
			xfs_ino_t			GetIno();
			uint32				GetOffsetFromAddress(uint32 address);
			int					EntrySize(int len) const;
			status_t			GetNext(char* name, size_t* length,
									xfs_ino_t* ino);
			status_t			Lookup(const char* name, size_t length,
									xfs_ino_t* id);
private:
			Inode*				fInode;
			ExtentMapEntry*		fDataMap;
			ExtentMapEntry*		fLeafMap;
			uint32				fOffset;
			char*				fDataBuffer;
				// This isn't inode data. It holds the directory block.
			char*				fLeafBuffer;
			uint32				fCurBlockNumber;
};


#endif
