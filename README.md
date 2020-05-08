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
```
Implementasi rmdir ini adalah ekspansi dari command rm yang sudah ada. Dalam command rm, terdapat system call unlink untuk menghapus file yang dituju. Untuk ekspansi command menjadi rmdir, dipakai struct stat dari stat.h. struct stat memiliki atribut untuk menyimpan data-data file, salah satunya adalah tipe. Directory dibuka dengan function open dan disimpan ke variabel fd. Data-data directory dalam fd lalu diassign ke struct stat st. st meyimpan data-data directory fd. Untuk mengecek apakah fd adalah file biasa atau directory, dilakukan pengecekan dalam if(st.type == T_DIR). Jika fd adalah directory, maka akan bernilai true. Selanjutnya dilakukan system call unlink untuk menghapus directory. Unlink tidak akan menghapus folder yang memiliki file atau folder didalamnya, maka akan mengeluarkan error dan tidak akan menghapus directory. Jika directory kosong, maka unlink akan menghapus directory
