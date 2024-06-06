#include <iostream>
#include <utility>

using namespace std;

class Array 
{
private:
    int* data; // указатель на массив элементов
    int size; // размер массива

public:
    Array(int s) : data(new int[s]), size(s) // конструктор инициализации
    { 
        for (int i = 0; i < size; i++) 
        {
            data[i] = 0; // заполнение массива нулями
        }
    }

    Array(const Array& other) : data(new int[other.size]), size(other.size) // конструктор копирования
    { 
        for (int i = 0; i < size; i++) 
        {
            data[i] = other.data[i]; // копирование данных из другого массива
        }
    }

    Array(Array&& other) noexcept : data(nullptr), size(0) // конструктор переноса
    { 
        data = other.data; // перемещаем указатель на данные
        size = other.size; // перемещаем размер
        other.data = nullptr; // устанавливаем указатель и размер у другого массива в nullptr
        other.size = 0;
    }

    Array& operator=(const Array& other) // оператор присваивания
    { 
        if (this != &other) // проверка на самоприсваивание
        { 
            delete[] data; // освобождаем память
            data = new int[other.size]; // выделяем новую память
            size = other.size; // устанавливаем новый размер
            for (int i = 0; i < size; i++) 
            {
                data[i] = other.data[i]; // копируем данные
            }
        }
        return *this; // возвращаем ссылку на текущий объект
    }

    Array& operator=(Array&& other) noexcept // оператор присваивания переноса
    { 
        if (this != &other) // проверка на самоприсваивание
        { 
            delete[] data; // освобождаем память
            data = other.data; // перемещаем указатель на данные
            size = other.size; // перемещаем размер
            other.data = nullptr; // устанавливаем указатель и размер у другого массива в nullptr
            other.size = 0;
        }
        return *this; // возвращаем ссылку на текущий объект
    }

    ~Array() // деструктор
    { 
        delete[] data; // освобождаем память
    }
};

int main() 
{
    Array arr1(3); // создаем массив с 3 элементами
    Array arr2(arr1); // вызывается конструктор копирования
    Array arr3(std::move(arr1)); // вызывается конструктор переноса

    Array arr4(5);
    arr4 = arr2; // вызывается оператор присваивания
    arr2 = std::move(arr3); // вызывается оператор присваивания переноса

    return 0;
}