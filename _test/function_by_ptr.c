#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <stdio.h>

// Объявление типа функции, которую мы будем использовать
typedef int (*func_ptr)(int);

// Определение структуры, которая будет содержать указатель на функцию
struct MyStruct {
    func_ptr function;
};

// Функция, которую мы хотим вызывать через указатель
int my_function(int x) {
	int res = x * 2;
	printf("Result: %d\n", res);
    return res;
}

int main() {
    // Создаем экземпляр структуры
    struct MyStruct my_struct;
    
    // Присваиваем указателю на функцию адрес функции my_function
    my_struct.function = &my_function;
    
    // Вызываем функцию через указатель
    my_struct.function(123);

    return 0;
}