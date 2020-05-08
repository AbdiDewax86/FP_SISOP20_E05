# FP_SISOP20_E05
## rmdir
#### Code:
```
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

```
  Implementasi rmdir ini adalah ekspansi dari command rm yang sudah ada. Dalam command rm, terdapat system call unlink untuk menghapus file yang dituju. Untuk ekspansi command menjadi rmdir, dipakai struct stat dari stat.h. struct stat memiliki atribut untuk menyimpan data-data file, salah satunya adalah tipe. 
    Directory dibuka dengan function open dan disimpan ke variabel fd. Data-data directory dalam fd lalu diassign ke struct stat st. st meyimpan data-data directory fd. Untuk mengecek apakah fd adalah file biasa atau directory, dilakukan pengecekan dalam if(st.type == T_DIR). Jika fd adalah directory, maka akan bernilai true. Selanjutnya dilakukan system call unlink untuk menghapus directory. Unlink tidak akan menghapus folder yang memiliki file atau folder didalamnya, maka akan mengeluarkan error dan tidak akan menghapus directory. Jika directory kosong, maka unlink akan menghapus directory.
    Implementasi rmdir ini memiliki argumen "-p". Argumen ini akan mencoba menghapus semua direktori sepanjang path. Direktori paling dalam akan terhapus terlebih dahulu, lalu mengecek direktori diatasnya seperti langkah sebelumnya. Apabila direktori atas masih memiliki file, proses akan dihentikan. Jika sepanjang direktori kosong, maka akan ikut terhapus dan proses dilanjutkan untuk direktori-direktori diatasnya.
