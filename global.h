


#ifndef GLOBAL_H__
#define GLOBAL_H__
#include "reactor.h"
#include "singleton.h"
class Reactor;

class Global:public Singleton<Global>
{
public:
	Global(void);
	~Global(void);
	Reactor* g_reactor_ptr;
};

#define sGlobal Global::instance()
#endif