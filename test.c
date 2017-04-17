/* Start Including Header Files */
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <stdlib.h>

int rv,sectionFilterFd,ret;
#define SECTION_HEADER_SIZE 3
int main(int argc, char const *argv[])
{
    unsigned int section_length;
    unsigned char *p_section_mem;
	unsigned char tmp_buff[512];

	memset(tmp_buff,0,sizeof(tmp_buff));
	rv = read(sectionFilterFd, tmp_buff,SECTION_HEADER_SIZE);
	if (rv > 0)
	{
		section_length = (((tmp_buff[1] & 0x0f) * 256) + tmp_buff[2]);
		p_section_mem = (unsigned char *)malloc(section_length + SECTION_HEADER_SIZE + 1);
		if (p_section_mem)
		{
			memcpy(p_section_mem, tmp_buff, SECTION_HEADER_SIZE);
    	
                rv = read(sectionFilterFd, &p_section_mem[SECTION_HEADER_SIZE], section_length);
                if (rv > 0)
                {
                   // *psection_length = section_length;

                    ret = 0;
                }
                 else
                {
                    free(p_section_mem);
                    p_section_mem = NULL;
                    close(sectionFilterFd);

                    return -1;
                }
        }
    }
    else if ( rv ==  -1 )
    {
    	printf("Error\n");
    }   
	return 0;
}