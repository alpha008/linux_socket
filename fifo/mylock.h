
 
int lock_set(int fd,int type)
{
	struct flock old_lock,lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_type = type;
	lock.l_pid = -1;
		
	fcntl(fd,F_GETLK,&lock);
 
	if(lock.l_type != F_UNLCK)
	{
		
		if (lock.l_type == F_RDLCK)  
		{
			printf("Read lock already set by %d\n",lock.l_pid);
		}
		else if (lock.l_type == F_WRLCK) 
		{
			printf("Write lock already set by %d\n",lock.l_pid);
		}						
	}
	
	lock.l_type = type;
	
	if ((fcntl(fd,F_SETLKW,&lock)) < 0)
	{
		printf("Lock failed : type = %d\n",lock.l_type);
		return 1;
	}
	
	switch (lock.l_type)
	{
		case F_RDLCK:
		{
			printf("Read lock set by %d\n",getpid());
		}
		break;
		case F_WRLCK:
		{
			printf("write lock set by %d\n",getpid());
		}
		break;
		case F_UNLCK:
		{
			printf("Release lock by %d\n",getpid());
			return 1;
		}
		break;
		
		default:
		break;
 
	}
	return 0;
}