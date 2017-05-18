

#include <assert.h>
#include "reactor.h"
#include "event_demultiplexer.h"

#define INITSIZE 100

class ReactorImplementation
{
public:
	ReactorImplementation();
	~ReactorImplementation();
	int RegisterHandler(EventHandler* handler,event_t evt);
	int RemoveHandler(EventHandler* handler);
	void HandleEvents();
	int RegisterTimerTask(heap_timer* timeevent);

private:
	EventDemultiplexer *m_demultiplexer;
	std::map<handle_t, EventHandler *>  m_handlers;
    time_heap* m_eventtimer;
};

Reactor::Reactor()
{
	m_reactor_impl = new ReactorImplementation();
}

Reactor::~Reactor()
{
	delete m_reactor_impl;
}

int  Reactor::RegisterHandler(EventHandler* handler,event_t evt)
{
	return m_reactor_impl->RegisterHandler(handler,evt);
}

int Reactor::RemoveHandler(EventHandler* handler)
{
	return m_reactor_impl->RemoveHandler(handler);
}

void Reactor::HandleEvents()
{
		m_reactor_impl->HandleEvents();
}

int Reactor::RegisterTimerTask(heap_timer* timeevent)
{
	return m_reactor_impl->RegisterTimerTask(timeevent);
}

//

ReactorImplementation::ReactorImplementation()
{
	m_demultiplexer =  new EpollDemultiplexer();
	m_eventtimer = new time_heap(INITSIZE);
}

ReactorImplementation::~ReactorImplementation()
{
	delete m_demultiplexer;
}


int  ReactorImplementation::RegisterHandler(EventHandler* handler,event_t evt)
{
	
	handle_t handle = handler->GetHandle();
	std
}

int ReactorImplementation::RemoveHandler(EventHandler* handler)
{
	return m_reactor_impl->RemoveHandler(handler);
}

void ReactorImplementation::HandleEvents()
{
		m_reactor_impl->HandleEvents();
}

int ReactorImplementation::RegisterTimerTask(heap_timer* timeevent)
{
	return m_reactor_impl->RegisterTimerTask(timeevent);
}

