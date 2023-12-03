#ifndef GRAPH_ARRAY_H
#define GRAPH_ARRAY_H

#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class Array {
private:
    T* array = nullptr;
    size_t capacity;
    size_t arraySize;

public:
    // Конструктор по умолчанию
    Array() : array(nullptr), capacity(0), arraySize(0) {}

    // Деструктор
    ~Array() {
        delete[] array;
    }

    // Метод добавления элемента в конец вектора
    void push_back(const T& element) {
        if (arraySize >= capacity) {
            // Увеличиваем размер массива при необходимости
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity *= 2;
            }

            // Создаем новый массив с увеличенной ёмкостью
            T* new_array = new T[capacity];
            new_array[0] = element;
            // Копируем элементы из старого массива в новый
            for (size_t i = 0; i < arraySize; ++i) {
                new_array[i] = array[i];
            }

            // Удаляем старый массив и присваиваем новый
            delete[] array;
            array = new_array;
        }

        // Добавляем элемент в конец
        array[arraySize++] = element;
    }

    // Метод получения размера вектора
    size_t getSize() const {
        return arraySize;
    }

    // Метод получения элемента по индексу
    T& operator[](size_t index) {
        if (index >= arraySize) {
            // Обработка ошибки: выход за границы вектора
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

    // Константная версия оператора получения элемента по индексу
    const T& operator[](size_t index) const {
        if (index >= arraySize) {
            // Обработка ошибки: выход за границы вектора
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

    // Итераторы для использования с стандартными алгоритмами
    T* begin() {
        return array;
    }

    const T* begin() const {
        return array;
    }

    T* end() {
        return array + arraySize;
    }

    const T* end() const {
        return array + arraySize;
    }
};
#endif //GRAPH_ARRAY_H
