#include "ring_buffer.h"

bool RingBuffer_push(RingBuffer *buf, Byte data)
{
    size_t next = (buf->head + 1) % buf->buffer_size;

    // no space
    if (next == buf->tail)
    {
        return false;
    }
    
    buf->buffer[buf->head] = data; 
    buf->head = next; 
    return true;
}

PopResult RingBuffer_pop(RingBuffer *buf)
{
    if (buf->head == buf->tail) 
    {
        // empty
        return (PopResult){ .data = 0, .success = false };
    }

    Byte data = buf->buffer[buf->tail]; 
    buf->tail = (buf->tail + 1) % buf->buffer_size; // wraparound lol
    // C is cool
    return (PopResult){ .data = data, .success = true };
}

