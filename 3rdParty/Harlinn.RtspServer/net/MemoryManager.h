#ifndef XOP_MEMMORY_MANAGER_H
#define XOP_MEMMORY_MANAGER_H

#include <xop/RtspServerDef.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mutex>

namespace xop
{

void* Alloc(uint32_t size);
void Free(void *ptr);

class MemoryPool;

struct MemoryBlock
{
	uint32_t block_id = 0;
	MemoryPool *pool = nullptr;
	MemoryBlock *next = nullptr;
};

class MemoryPool
{
public:
	HW_RTSPSERVER_EXPORT MemoryPool();
	HW_RTSPSERVER_EXPORT virtual ~MemoryPool();

	HW_RTSPSERVER_EXPORT void  Init(uint32_t size, uint32_t n);
	HW_RTSPSERVER_EXPORT void* Alloc(uint32_t size);
	HW_RTSPSERVER_EXPORT void  Free(void* ptr);

	size_t BolckSize() const
	{ return block_size_; }

//private:
	char* memory_ = nullptr;
	uint32_t block_size_ = 0;
	uint32_t num_blocks_ = 0;
	MemoryBlock* head_ = nullptr;
	std::mutex mutex_;
};

class MemoryManager
{
public:
	HW_RTSPSERVER_EXPORT static MemoryManager& Instance();
	HW_RTSPSERVER_EXPORT ~MemoryManager();

	HW_RTSPSERVER_EXPORT void* Alloc(uint32_t size);
	HW_RTSPSERVER_EXPORT void  Free(void* ptr);

private:
	HW_RTSPSERVER_EXPORT MemoryManager();

	static const int kMaxMemoryPool = 3;
	MemoryPool memory_pools_[kMaxMemoryPool];
};

}
#endif
