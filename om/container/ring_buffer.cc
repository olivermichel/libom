
#include "ring_buffer.h"

template<class T>
bool om::container::RingBuffer<T>::_available(uint64_t head, uint64_t tail)
{
	if(head > tail)
		return (tail + _size) - head > 0;
	else if(tail > head)
		return (tail - head) > _size;
	else // head == tail
		return true;
}
