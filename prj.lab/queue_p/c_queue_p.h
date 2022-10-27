#ifdef __cplusplus

#include <cstdint>
using std::uint64_t;
using std::int32_t;

#else

#include <stdint.h>

#endif

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum {
        kGood = 0,   // all right
        kHandlerError, // bad handler
        kOutOfRange    // queue is empty
    } ErrorCode;

    typedef uint64_t QueueHandler;
    const QueueHandler EMPTY_QUEUE_HANDLER = 0;

    ErrorCode CreateQueue(QueueHandler* queue);

    ErrorCode CloneQueue(QueueHandler source, QueueHandler* queue);

    ErrorCode DestroyQueue(QueueHandler* queue);

    ErrorCode Pop(QueueHandler queue);

    ErrorCode Push(QueueHandler queue, int32_t value);

    ErrorCode IsEmpty(QueueHandler queue, int32_t* result);

    ErrorCode Top(QueueHandler queue, int32_t* result);

    const char* WhatIs(ErrorCode err);

#ifdef __cplusplus
};
#endif
