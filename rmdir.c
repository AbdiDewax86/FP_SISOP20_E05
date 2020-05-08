#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  int fd,i;
  struct stat st;

  if(argc < 2){
    printf(2, "Usage: rmdir [directory] or rmdir [argument] [directory]\n");
    exit();
  }

  if(argc == 2){
    fd = open(argv[1], O_RDONLY);
    
    fstat(fd,&st);

    if(st.type == T_DIR){
      if(unlink(argv[1]) < 0){
        printf(2, "rmdir: %s failed to delete directory\n", argv[1]);
      }
      else
      {
        printf(2, "rmdir: %s directory deleted\n",argv[1]);
      }
    }
    else{
      printf(2, "rmdir: %s is not a directory\n", argv[1]);
    }
  }
  else{
    char * argument = argv[1];
    char * path = argv[2];
    if(argument[0]=='-' && argument[1]=='p'){
      while(strlen(path) != 0){
        fd = open(path, O_RDONLY);
    
        fstat(fd,&st);

        if(st.type == T_DIR){
          if(unlink(argv[2]) < 0){
            printf(2, "rmdir: %s failed to delete directory\n", argv[2]);
            break;
          }
          else
          {
            printf(2, "rmdir: %s directory deleted\n",argv[2]);
          }
        }
        else{
          printf(2, "rmdir: %s is not a directory\n", argv[2]);
          break;
        }

        for(i=strlen(path)-1; i>=0; i--){
          if(path[i]=='/'){
            path[i]='\0';
            break;
          }
          else{
            path[i]='\0';
          }
        }
      }
    }
    else{
      printf(2, "unknown argument: %s", argument);
    }
  }

  exit();
}
