#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

void
fold(int fd, int n)
{
  int ret;
  if (n == -1)
  {
    ret = read(fd,buf,sizeof(buf));
    for (int i = 0; i<sizeof(buf); i++)
    {
      if (buf[i]==' ') printf (1,"\n");
      else printf (1,"%c",buf[i]);
    }
  }
  else{
    while(1){
      ret = read(fd, buf, n);
      if (ret < n) {
        buf[n] = '\0';
        printf (1,"%s\n",buf);
        break;
      }
      else {
        printf (1,"%s\n",buf);
      }
    }
  }
}

int
main(int argc, char *argv[])
{
  int fd;
  int i=2,j=0;
  if (argc <= 1)
  {
    printf (1,"argumen kurang!\n");
    exit();
  }

  else if(argc == 2){
    if((fd = open(argv[1], O_RDONLY)) < 0){
      printf(1, "fold: cannot open %s\n", argv[1]);
    }
    fold(fd,80);
    close(fd);
  }

  else{
    char * temp = argv[1];
    char angka[5];
    if (temp[0] == '-' && temp[1] == 's')
    {
        if((fd = open(argv[2], O_RDONLY)) < 0){
          printf(1, "fold: cannot open %s\n", argv[2]);
          exit();
      }
      fold(fd,-1);
      close(fd);
    }
    else if (temp[0] == '-' && (temp[1] == 'w' || temp[1]== 'b')){
      if((fd = open(argv[2], O_RDONLY)) < 0){
        printf(1, "fold: cannot open %s\n", argv[2]);
        exit();
      }
      while (temp[i]!='\0')
      {
        angka[j]=temp[i];
        i++;j++;
      }
      int n = atoi(angka);
      fold(fd,n);
      close(fd);
    }
    else{
      printf (1,"Argumen error!\n");
    }
  }
  exit();
}