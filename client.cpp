

#include "common.h"

Reactor g_reactor;
const size_t BUFF_SIZE = 1024;
char g_read_buffer[BUFF_SIZE];
char g_write_buffer[BUFF_SIZE];

class TimeClient:public EventHandler
{
public:
				TimeClient():EventHandler()
				{ 
				  m_handle = socket(AF_INET,SOCK_STREAM,0);
					assert(IsValidHandle(m_handle));
				}
				~TimeClient()
				{
				  close(m_handle);
				}
				bool ConnectServer(const char* ip,unsigned short port)
				{
				   struct sockaddr_in addr;
					 addr.sin_family =  AF_INET;
					 addr.sin_port  = htons(port);
					 addr.sin_addr.s_addr = inet_addr(ip);
					 if(connect(m_handle,(struct sockaddr*)&addr,sizeof(addr)) < 0)
					 {
					    ReportSocketError("connect error");
							return false;
					 }
					 return true;
				}

				virtual handle_t GetHandle() const
				{
				  return m_handle;
				}

				virtual void HandleError()
				{
				  fprintf(stderr,"server closed\n");
					close(m_handle);
					exit(0);
				}

				virtual void HandleWrite()
				{
				    memset(g_write_buffer,0,BUFF_SIZE);
						int len  = sprintf(g_write_buffer,"time\r\n");
						len  = send(m_handle,g_write_buffer,len,0);
						if(len > 0)
						{
						  fprintf(stderr,"%s\n",g_write_buffer);
							g_reactor.RegisterHandler(this,kReadEvent);
						}
						else
						{
						   ReportSocketError("send error");
						}

				}

				virtual void HandleRead()
				{
								memset(g_read_buffer,0,BUFF_SIZE);
				        //int len  = sprintf(g_read_buffer,"time\r\n");
				       int  len  =recv(m_handle,g_read_buffer,BUFF_SIZE,0);
				        if(len > 0)
				        {     
								    printf("read from sever:%s\n",g_read_buffer);
								     g_reactor.RegisterHandler(this,kWriteEvent);
				         }    
						     else 
                {     
		                 ReportSocketError("recv error");
								}

				}
private:
				handle_t m_handle;

				
};



int main(int argc,char* argv[])
{

   if(argc < 3)
	 {
	     
			 fprintf(stderr,"usage:%s ip port\n",argv[0]);
			 return EXIT_FAILURE;
	 }
	 TimeClient client;

	 if(!client.ConnectServer(argv[1],atoi(argv[2])))
	 { 
				fprintf(stderr,"connect remote server failed\n");
				return EXIT_FAILURE;
	 }

	 g_reactor.RegisterHandler(&client,kWriteEvent);

	 while(1)
	 {
	    g_reactor.HandleEvents();
			sleep(1);
	 }
	 g_reactor.RemoveHandler(&client);
	 return EXIT_SUCCESS;
}
