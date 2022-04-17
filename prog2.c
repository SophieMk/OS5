#include <dlfcn.h>
#include <stdio.h>

int main()
{
    void* cur_lib = NULL; //пустой указатель 
    float (*Derivative)(float A, float deltaX); // указатель на функцию производной
    float (*E)(int x); // указатель на функцию е

    int key;
    int lib_num;
    printf("Library 1 or 2?\n"); //Выберите библиотеку
    scanf("%d",&lib_num);

    // Открываем нужную библиотеку:
    if (lib_num == 1) { //если первая библиотека
        //dlopen(const char *filename, int flag), dlopen загружает динамическую библиотеку и возвращает
        //прямой указатель на начало динамической библиотеки
        //RTLD_LAZY подразумевает разрешение неопределённых символов в виде кода из динамической библиотеке
        cur_lib = dlopen("./libd1.so",RTLD_LAZY);  //загружаем и открываем библиотеку 1
    } else if (lib_num == 2) { //если вторая библиотека
        cur_lib = dlopen("./libd2.so",RTLD_LAZY); //загружаем и открываем библиотеку 2
    } else {
        return 1;
    }

    // Находим адреса функций:
    //void *dlsym(void *handle, char *symbol), dlsym использует указатель на динамическую библиотеку, возвращаемую dlopen, 
    //и оканчивающееся нулем символьное имя, а затем возвращает адрес, указывающий, откуда загружается этот символ
    Derivative = dlsym(cur_lib, "Derivative");
    E = dlsym(cur_lib, "E");

    while (scanf("%d",&key) > 0) {
        if (key == 1) { //если значение 1
            float A,deltaX;
            scanf("%f%f",&A,&deltaX); //считываем A, deltaX
            printf("%s(%f, %f) = %f\n","Derivative", A, deltaX,(*Derivative)(A, deltaX)); //выводим значение производной
        } else if (key == 2) { //если значение 2
            int x;
            scanf("%d",&x); //считываем х
            printf("%s(%d) = %f\n","E",x,(*E)(x)); //выводим значение е
        } else if (key == 0) { //если значение 0
            //dlclose(void* handle) уменьшает на единицу счетчик ссылок на указатель динамической библиотеки handle
            dlclose(cur_lib);  //закрываем библиотеку

            if (lib_num == 1) { //если значение библиотеки 1
                lib_num = 2; //меняем значение на 2
                cur_lib = dlopen("./libd2.so",RTLD_LAZY); //загружаем и открываем библиотеку 2
            } else {
                lib_num = 1; //иначе меняем значение на 1
                cur_lib = dlopen("./libd1.so",RTLD_LAZY); //загружаем и открываем библиотеку 1
            }
            //находим начало адреса функций Derivative и E другой библиотеки
            Derivative = dlsym(cur_lib,"Derivative"); 
            E = dlsym(cur_lib, "E");
        }
    }

    dlclose(cur_lib); //закрываем библиотеку
}
