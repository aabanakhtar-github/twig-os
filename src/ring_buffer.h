#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "types.h"
#include "stdbool.h"

struct RingBuffer;

/*
#define CREATE_RING_BUFFER(name, len) \
    Byte* __buffer_##name[len]; \
    static RingBuffer buffer = { \
        .buffer = __buffer_##name, \
        .buffer_size = sizeof(__buffer_##name), \
        .x = 0 \ 
        .y = 0 \
    }; \
*/

typedef struct RingBuffer 
{
    Byte* buffer;
    size_t buffer_size; 
    size_t head;  
    size_t tail; 
} RingBuffer;

typedef struct PopResult 
{
    bool success; 
    Byte data;
} PopResult;

// false if failed
bool RingBuffer_push(RingBuffer* buf, Byte data); 
PopResult RingBuffer_pop(RingBuffer* buf);
inline bool RingBuffer_isEmpty(RingBuffer* buf) { return buf->head == buf->tail; }

inline size_t RingBuffer_length(RingBuffer* buf) { 
    if (RingBuffer_isEmpty(buf)) 
    { 
       return 0; 
    }
    else if (buf->head > buf->tail) 
    {
        return buf->head - buf->tail + 1;
    }
    else 
    {
        return buf->head + (buf->buffer_size - buf->tail + 1);
    }
}

#endif