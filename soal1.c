#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/haikal/Documents/Shift4";

void caesarCipherEnc(char text[])
{
	int i, j;
	char charlist[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
	for(i=0; i<strlen(text); i++)
	{
		if(text[i]=='/')
			text[i]=text[i];
		else
		{
			for(j=0; j<94; j++)
			{
				if(text[i] == charlist[j])
				{
					text[i] = charlist[(j+17)%94];				
					break;
				}
			}
		}
	}
}

void caesarCipherDec(char text[])
{
	int i, j;
	char charlist[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
	for(i=0; i<strlen(text); i++)
	{
		if(text[i]=='/')
			text[i]=text[i];
		else
		{
			for(j=0; j<94; j++)
			{
				if(text[i] == charlist[j])
				{
					text[i] = charlist[(j+94-17)%94];				
					break;
				}
			}
		}
	}
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
  	int res;
	char fpath[1000], filename[1000]= "";
    
    	if(strcmp(path, ".")!= 0 && strcmp(path,"..")!=0)
    	{	
		strcpy(filename, path);
        	caesarCipherEnc(filename);
        	sprintf(fpath,"%s%s",dirpath,filename);
    	}
    	else
   	{
        	sprintf(fpath,"%s%s",dirpath,path);
    	}
	res = lstat(fpath, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
  	char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{	
		char filename[100];
		strcpy(filename,path);
		caesarCipherEnc(filename);
		sprintf(fpath, "%s%s",dirpath,filename);
		
	}
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		char fname[1000]={0};
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		if(strcmp(de->d_name, ".") && strcmp(de->d_name,".."))
        	{	
			strcpy(fname, de->d_name);
            		caesarCipherDec(fname);
    			res = (filler(buf,fname, &st, 0));
        	}
        	else
        	{
           		res = (filler(buf,de->d_name, &st, 0));    
        	}
		if(res!=0) break;
	}
	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
  	char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;
  	int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
