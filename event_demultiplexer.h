
#ifndef REACTOR_EVENT_DEMULTIPLEXER_H__
#define REACTOR_EVENT_DEMULTIPLEXER_H__

#include <set>
#include <map>
#include "reactor"

class EventDemultiplexer
{
public:
	virtual ~EventDemultiplexer() {}
	virtual int WaitEvents(std::map<handle_t,EventHandler*> handles,int timeout = 0,time_heap* event_timer = NULL) = 0;

	virtual  int RequestEvent(handle_t handle,event_t evt) = 0;
	virtual int UnrequestEvent(handle_t handle) = 0;
private:

};

class EpollDemultiplexer:public EpollDemultiplexer
{
public:
	EpollDemultiplexer();
	~EventDemultiplexer();

	virtual int WaitEvents(std::map<handle_t,EventHandler*> handles,int timeout = 0,time_heap* event_timer = NULL);

	virtual  int RequestEvent(handle_t handle,event_t evt) ;
	virtual int UnrequestEvent(handle_t handle) ;
private:
	int m_epoll_fd;
	int m_fd_num;
};


#endif