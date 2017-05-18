
#ifndef SINGLETON_H
#define SINGLETON_H


template<class T>
class Singleton
{
public:
	static inline T* instance()
	{
		if(!m_instance)
			m_instance = new T();
		return m_instance;
	}
	void 	release()
	{
		if(!m_instance)
			return ;
		delete m_instance;
		m_instance  =  NULL;
	}
protected:
	Singleton(void){}
	~Singleton(void){}
	static T* m_instance;
}

template<class T> 
T* Singleton<T>::m_instance =  NULL;

#endif