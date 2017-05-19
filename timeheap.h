

#ifndef TIME_HEAP_H__
#define TIME_HEAP_H__ 

#include <iostream>
#include <netinet/in.h>
#include <time.h>

#define BUFFER_SIZE 64
#define LEN 10

class heap_timer;
struct client_data
{
	sockaddr_in address;
	int sockfd;
	char buf[BUFFER_SIZE];
	heap_timer* timer;
};

class heap_timer
{
public:
	heap_timer(int delay)
	{
		expire = time( NULL ) + delay;	
	}
public:
	time_t expire;
	void (*cb_func)(client_data* cli);
	client_data* user_data;
};


class time_heap
{
  public:
  	time_heap(int cap):capacity(cap+LEN),cur_size(0)
  	{
  		array = new heap_timer* [capacity];
  		if( !array )
  		{

  		}
  		for(int i = 0;i<capacity;i++)
  		{
  			array[i] = NULL;
  		}

  	}
  	time_heap(heap_timer** init_array,int size,int cap)
  	{
  		cur_size = size;
  		capacity = cap + LEN;
  		array = new heap_timer* [capacity];

  		if(!array)
  		{

  		}

  		for(int i = 0; i < capacity; i++ )
  		{
  			array[i] = NULL;
  		}


  		if(cur_size != 0)
  		{
  			for(int i=0;i<cur_size;i++)
  			{
  				array[i+1] = init_array[i];
  			}

  			for(int i = cur_size/2;i>0;i--)
  			{
  				percolate_down(i);
  			}
  		}
  	}
  	~time_heap()
  	{
  		for(int i=0;i<cur_size;i++)
  		{
  			delete array[i];
  		}
  		delete []array;
  	}
  	bool empty() const
  	{
  		return cur_size == 0;
  	}

  public:
    void add_timer(heap_timer* timer)
    {
      if(!timer)
        return ;
      if(cur_size >= capacity)
      {
        resize();
      }
      int hole = ++cur_size;
      int parent = 0;
      for(;hole>1;hole = parent )
      {
        parent = hole/2;
        if( array[parent]->expire <= array[hole]->expire)
        {
          break;
        }
        array[hole] = array[parent];

      }
      array[hole] = timer;
    }

    void del_timer(heap_timer* timer)
    {
      if(!timer)
      {
        return ;
      }

      timer->cb_func = NULL; //lazy delete
    }

    heap_timer* top() const
    {
      if(empty())
      {
        return NULL;
      }
      return array[1];

    }

    void pop_timer()
    {
      if(empty())
      {
        return ;
      }

      if(array[1])
      {
        delete array[1];
        array[1] = array[cur_size--];
        percolate_down(1);
      }
    }

    void tick()
    {
      heap_timer* tmp = array[1];
      time_t cur = time(NULL);

      while(!empty())
      {
        if(!tmp)
        {
          break;
        }
        if(tmp->expire > cur)
        {
          break;
        }

        if(array[1]->cb_func)
        {
          array[1]->cb_func(array[1]->user_data);
        }
        pop_timer();
        tmp = array[1];
      }
    }
  private:
  	void percolate_down(int hole)
  	{
  		heap_timer* temp = array[hole];
  		int child = 0;
  		for(;hole*2 <= cur_size;hole = child)
  		{
  			child = hole * 2;
  			if(child!=cur_size && array[child+1] < array[child])
  				child++;
  			if(array[child]->expire < temp->expire)
  			{
  				array[hole] = array[child];
  			}

  		}
  		array[hole] = temp;
  	}
      void resize()
      {
      	heap_timer** temp = new heap_timer* [2*capacity];

      	for(int i=0;i<2*capacity;i++)
      	{
      		temp[i] = NULL;
      	}
      	capacity = 2 * capacity;
      	for(int i=0;i<cur_size;i++)
      	{
      		temp[i] = array[i];
      	}
      	delete []array;
      	array = temp;

      }
  private:
  	heap_timer** array;
  	int capacity;
  	int cur_size;
};
#endif