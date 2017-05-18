
#include <errno.h>
#include <assert.h>
#include <vector>
#include "event_demultiplexer.h"

EpollDemultiplexer:EpollDemultiplexer()
{
	m_epoll_fd = ::epoll_create(FD_SETSIZE);
	assert(m_epoll_fd != -1);
	m_fd_num = 0;
}

EpollDemultiplexer::~EpollDemultiplexer()
{
	::close(m_epoll_fd);
}

int EpollDemultiplexer::WaitEvents(std::map<handle_t,EventHandler*> handles,int timeout = 0,time_heap* event_timer = NULL)
{

}

int EpollDemultiplexer::RequestEvent(handle_t handle,event_t evt)
{
	epoll_event ep_evt;
	ep_evt.data.fd = handle;
	
}

int EpollDemultiplexer::UnrequestEvent(handle_t handle)
{

}

