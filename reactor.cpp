

#include <assert.h>
#include "reactor.h"
#include <stdio.h>
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
	//printf("RegisterHandler\n");
	handle_t handle = handler->GetHandle();
	std::map<handle_t,EventHandler *>::iterator it = m_handlers.find(handle);
	if(it == m_handlers.end())
	{
		m_handlers[handle] = handler;
	}

	return m_demultiplexer->RequestEvent(handle,evt);
}

int ReactorImplementation::RemoveHandler(EventHandler* handler)
{
	handle_t handle = handler->GetHandle();
	m_handlers.erase(handle);
	return m_demultiplexer->UnrequestEvent(handle);


}

void ReactorImplementation::HandleEvents()
{
		//printf("HandleEvents\n");
		int timeout = 0;
		if(m_eventtimer->top() == NULL)
		{
			timeout = 0;
		}
		else
		{
			timeout = ((m_eventtimer->top()->expire - time(NULL)) * 1000);
		}

		m_demultiplexer->WaitEvents(&m_handlers,timeout,m_eventtimer);
		//m_demultiplexer->WaitEvents(&m_handlers,5000,m_eventtimer);

}

int ReactorImplementation::RegisterTimerTask(heap_timer* timeevent)
{
	if(timeevent == NULL)
		return -1;
	m_eventtimer->add_timer(timeevent);
	return 0;
}

