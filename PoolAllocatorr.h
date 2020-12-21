#pragma once
#include <vector>

template <typename T> 
class PoolAllocator
{
	std::vector<T*> m_chunks;
	T* m_insertPoint;
	T* m_endPoint;
	const size_t m_chunkSize;

	void AllocateChunk() {
		T* chunk = new T[m_chunkSize];
		m_insertPoint = chunk;
		m_endPoint = chunk + m_chunkSize;
		m_chunks.push_back(chunk);
	}


	public:
		PoolAllocator(size_t chunnksize = 340) : m_chunkSize(chunnksize) {};
		~PoolAllocator() {
			clear();
		}

		T* alloc() {
			if (m_insertPoint >= m_endPoint) {
				AllocateChunk();
			}

			return m_insertPoint++;
		}

		template <typename ...Args>
		T* alloc(Args...args) {
			if (m_insertPoint >= m_endPoint) {
				AllocateChunk();
			}
			
			new (m_insertPoint) T(args...);
			T* old_insert = m_insertPoint;
			m_insertPoint++;
			return old_insert;
		}


		void clear() {
			for (T* ptr : m_chunks) {
				delete[] ptr;
			}
			m_insertPoint = nullptr;
			m_endPoint = nullptr;
			m_chunks.clear();

		}

};


