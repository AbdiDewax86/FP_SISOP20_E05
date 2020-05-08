#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  int fd,i;
  //struct dirent de;
  struct stat st;

  if(argc < 2){
    printf(2, "Usage: rmdir directory...\n");
    exit();
  }

  for(i = 1; i < argc; i++){
    fd = open(argv[i], O_RDONLY);
    
    fstat(fd,&st);

    if(st.type == T_DIR){
      if(unlink(argv[i]) < 0){
        printf(2, "rmdir: %s failed to delete directory\n", argv[i]);
        break;
      }
      else
      {
        printf(2, "rmdir: %s directory deleted\n",argv[i]);
      }
    }
    else{
      printf(2, "rmdir: %s is not a directory\n", argv[i]);
    }
  }

  exit();
}
