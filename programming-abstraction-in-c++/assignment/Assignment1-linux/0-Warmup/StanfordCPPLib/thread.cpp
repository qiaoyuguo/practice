/*
 * File: thread.cpp
 * ----------------
 * This file implements the platform-independent parts of the thread package.
 */

#include <iostream>
#include <sstream>
#include <string>
#include "thread.h"
#include "private/tplatform.h"
using namespace std;

Thread::Thread() {
    id = -1;
}

Thread::~Thread() {
    /* Empty */
}

string Thread::toString() {
   ostringstream stream;
   stream << "Thread" << id;
   return stream.str();
}

static void forkWithVoid(void *arg);

Thread fork(void (*fn)()) {
   Thread thread;
   StartWithVoid startup = { fn };
   thread.id = forkForPlatform(forkWithVoid, &startup);
   return thread;
}

void join(Thread & thread) {
   joinForPlatform(thread.id);
}

void yield() {
   yieldForPlatform();
}

Thread getCurrentThread() {
   Thread thread;
   thread.id = getCurrentThreadForPlatform();
   return thread;
}

Lock::Lock() {
   id = initLockForPlatform();
}

Lock::~Lock() {
   decLockRefCountForPlatform(id);
}

void Lock::wait() {
   waitForPlatform(id);
}

void Lock::signal() {
   signalForPlatform(id);
}

static void forkWithVoid(void *arg) {
   StartWithVoid *startup = (StartWithVoid *) arg;
   startup->fn();
}
