#ifndef	__SOUNDSERVER_OPENAL__
#define	__SOUNDSERVER_OPENAL__

typedef void (*USER_CALLBACK) (void *pBuffer,long bufferLen);

class	CSoundServer
{
		class body; body* m_pBody;
  public:

		CSoundServer();
		~CSoundServer();

		bool	open(	USER_CALLBACK	pUserCallback,
						long bufferedMilliseconds=4000);

		void	close(void);

		bool	IsRunning();
  private:
		CSoundServer(CSoundServer const &) = delete;
		CSoundServer & operator=(CSoundServer &) = delete;
};

#endif
