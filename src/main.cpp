#include <iostream>
#include <cstddef>
#include <clocale>
#include "array_ops.h"

template <typename T>
void safe_input(T& value, const char* prompt) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            break;
        }
        std::cout << "Ошибка ввода! Пожалуйста, введите число.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    int* arr = nullptr;
    std::size_t size = 0;
    int choice = -1;

    std::cout << "=== Лабораторная работа 1. Вариант 3 ===\n";

    while (choice != 0) {
        std::cout << "\n--- МЕНЮ (Вариант 3) ---\n";
        std::cout << "1. Создать массив\n";
        std::cout << "2. Напечатать массив\n";
        std::cout << "3. Вставить элемент\n";
        std::cout << "4. Удалить элемент\n";
        std::cout << "5. Изменить размер\n";
        std::cout << "6. Сортировка вставками\n";
        std::cout << "7. Бинарный поиск элемента\n";
        std::cout << "8. Циклический сдвиг влево на k\n";
        std::cout << "0. Выход\n";
        
        safe_input(choice, "Выберите пункт: ");

        switch (choice) {
            case 1: {
                array_delete(arr); 
                safe_input(size, "Введите размер нового массива: ");
                arr = array_create(size);
                
                std::cout << "Введите элементы массива" << size << " шт.):\n";
                for (std::size_t i = 0; i < size; ++i) {
                    safe_input(arr[i], "Элемент: ");
                }
                std::cout << "Массив создан\n";
                break;
            }
            case 2: {
                std::cout << "Текущий массив: ";
                array_print(arr, size);
                break;
            }
            case 3: {
                std::size_t pos;
                int value;
    
                safe_input(pos, "Введите позицию для вставки (все пустые элементы будут равны 0): ");
                safe_input(value, "Введите значение: ");
                arr = array_insert(arr, size, pos, value);
                std::cout << "Элемент вставлен. Новый размер: " << size << "\n";
                break;
            }
            case 4: {
                if (size == 0 || arr == nullptr) {
                    std::cout << "Массив и так пустой, че ты там удалять собрался?\n";
                    break;
                }
                std::size_t pos;
                std::cout << "Введите позицию для удаления (0.." << size-1 << "): ";
                safe_input(pos, "");
                if (pos >= size) {
                    std::cout << "Ошибка: выход за рамки массива\n";
                    break;
                }
                arr = array_remove(arr, size, pos);
                std::cout << "Элемент удален. Новый размер: " << size << "\n";
                break;
            }
            case 5: {
                std::size_t new_size;
                safe_input(new_size, "Введите новый размер: ");
                arr = array_resize(arr, size, new_size);
                size = new_size;
                std::cout << "Размер изменен до: " << size << "\n";
                break;
            }
            case 6: {
                insert_sort(arr, size);
                std::cout << "Массив отсортирован вставками: ";
                array_print(arr, size);
                break;
            }
            case 7: {
                int target;
                std::size_t found_index = 0;
                safe_input(target, "Введите число для поиска: ");
                
                if (array_binary_search(arr, size, target, found_index)) {
                    std::cout << "Элемент найден на индексе: " << found_index << "\n";
                } else {
                    std::cout << "Элемент не найден\n";
                }
                break;
            }
            case 8: {
                std::size_t k;
                safe_input(k, "Введите k для сдвига: ");
                array_rotate_left(arr, size, k);
                std::cout << "Массив сдвинут влево: ";
                array_print(arr, size);
                break;
            }
            case 0: {
                std::cout << "Выход из программы...\n";
                break;
            }
            default: {
                std::cout << "Неверный пункт меню!\n";
                break;
            }
        }
    }

    array_delete(arr);
    return 0;
}
