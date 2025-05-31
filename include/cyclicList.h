/**
 * @file cyclicList.h
 * @brief Заголовочный файл, содержащий реализацию циклического двусвязного списка
 */

#ifndef CYCLICLIST_H
#define CYCLICLIST_H

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <memory>
#include <vector>

/**
 * @brief Шаблонный класс циклического двусвязного списка
 * 
 * @tparam T Тип данных, хранимых в списке
 * 
 * Класс реализует циклический двусвязный список с возможностью итерации
 * в обоих направлениях. Список поддерживает операции добавления и удаления
 * элементов в начало и конец, а также в произвольную позицию.
 */
template <typename T>
class CyclicList {
private:
    /**
     * @brief Структура узла списка
     */
    struct Node {
        T data;                          ///< Данные узла
        std::shared_ptr<Node> next;      ///< Указатель на следующий узел
        std::weak_ptr<Node> prev;        ///< Указатель на предыдущий узел

        /**
         * @brief Конструктор узла
         * @param value Значение для инициализации узла
         */
        Node(const T& value) : data(value), next(nullptr) {}
    };

    std::shared_ptr<Node> head;  ///< Указатель на головной узел списка
    size_t size_;               ///< Размер списка

public:
    /**
     * @brief Конструктор по умолчанию
     * 
     * Создает пустой список
     */
    CyclicList();

    /**
     * @brief Конструктор с инициализацией из списка
     * @param init Список инициализации
     */
    CyclicList(std::initializer_list<T> init);

    /**
     * @brief Класс итератора для списка
     * 
     * Реализует двунаправленный итератор для обхода списка
     */
    class iterator {
        friend class CyclicList<T>;  
    private:
        std::shared_ptr<Node> current;   ///< Текущий узел
        std::shared_ptr<Node> head;      ///< Головной узел списка
        bool is_end;                     ///< Флаг конца списка
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /**
         * @brief Конструктор итератора
         * @param node Текущий узел
         * @param head Головной узел списка
         * @param is_end Флаг конца списка
         */
        iterator(std::shared_ptr<Node> node = nullptr, 
                std::shared_ptr<Node> head = nullptr, 
                bool is_end = false);

        /**
         * @brief Оператор разыменования
         * @return Ссылка на данные текущего узла
         */
        reference operator*() const;

        /**
         * @brief Оператор доступа к членам
         * @return Указатель на данные текущего узла
         */
        pointer operator->() const;

        /**
         * @brief Префиксный оператор инкремента
         * @return Ссылка на итератор
         */
        iterator& operator++();

        /**
         * @brief Постфиксный оператор инкремента
         * @return Итератор до инкремента
         */
        iterator operator++(int);

        /**
         * @brief Префиксный оператор декремента
         * @return Ссылка на итератор
         */
        iterator& operator--();

        /**
         * @brief Постфиксный оператор декремента
         * @return Итератор до декремента
         */
        iterator operator--(int);

        /**
         * @brief Оператор сравнения на равенство
         * @param other Итератор для сравнения
         * @return true если итераторы равны, false иначе
         */
        bool operator==(const iterator& other) const;

        /**
         * @brief Оператор сравнения на неравенство
         * @param other Итератор для сравнения
         * @return true если итераторы не равны, false иначе
         */
        bool operator!=(const iterator& other) const;
    };

    /**
     * @brief Класс константного итератора для списка
     * 
     * Реализует двунаправленный константный итератор для обхода списка
     */
    class const_iterator {
        friend class CyclicList<T>;  
    private:
        std::shared_ptr<Node> current;   ///< Текущий узел
        std::shared_ptr<Node> head;      ///< Головной узел списка
        bool is_end;                     ///< Флаг конца списка
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        /**
         * @brief Конструктор константного итератора
         * @param node Текущий узел
         * @param head Головной узел списка
         * @param is_end Флаг конца списка
         */
        const_iterator(std::shared_ptr<Node> node = nullptr, 
                      std::shared_ptr<Node> head = nullptr, 
                      bool is_end = false);

        /**
         * @brief Оператор разыменования
         * @return Константная ссылка на данные текущего узла
         */
        reference operator*() const;

        /**
         * @brief Оператор доступа к членам
         * @return Константный указатель на данные текущего узла
         */
        pointer operator->() const;

        /**
         * @brief Префиксный оператор инкремента
         * @return Ссылка на итератор
         */
        const_iterator& operator++();

        /**
         * @brief Постфиксный оператор инкремента
         * @return Итератор до инкремента
         */
        const_iterator operator++(int);

        /**
         * @brief Префиксный оператор декремента
         * @return Ссылка на итератор
         */
        const_iterator& operator--();

        /**
         * @brief Постфиксный оператор декремента
         * @return Итератор до декремента
         */
        const_iterator operator--(int);

        /**
         * @brief Оператор сравнения на равенство
         * @param other Итератор для сравнения
         * @return true если итераторы равны, false иначе
         */
        bool operator==(const const_iterator& other) const;

        /**
         * @brief Оператор сравнения на неравенство
         * @param other Итератор для сравнения
         * @return true если итераторы не равны, false иначе
         */
        bool operator!=(const const_iterator& other) const;
    };

    /**
     * @brief Возвращает итератор на начало списка
     * @return Итератор на первый элемент
     */
    iterator begin();

    /**
     * @brief Возвращает итератор на конец списка
     * @return Итератор на позицию после последнего элемента
     */
    iterator end();

    /**
     * @brief Возвращает константный итератор на начало списка
     * @return Константный итератор на первый элемент
     */
    const_iterator begin() const;

    /**
     * @brief Возвращает константный итератор на конец списка
     * @return Константный итератор на позицию после последнего элемента
     */
    const_iterator end() const;

    /**
     * @brief Возвращает константный итератор на начало списка
     * @return Константный итератор на первый элемент
     */
    const_iterator cbegin() const;

    /**
     * @brief Возвращает константный итератор на конец списка
     * @return Константный итератор на позицию после последнего элемента
     */
    const_iterator cend() const;

    /**
     * @brief Проверяет, пуст ли список
     * @return true если список пуст, false иначе
     */
    bool empty() const;

    /**
     * @brief Возвращает размер списка
     * @return Количество элементов в списке
     */
    size_t size() const;

    /**
     * @brief Возвращает ссылку на первый элемент
     * @return Ссылка на первый элемент
     * @throw std::out_of_range если список пуст
     */
    T& front();

    /**
     * @brief Возвращает константную ссылку на первый элемент
     * @return Константная ссылка на первый элемент
     * @throw std::out_of_range если список пуст
     */
    const T& front() const;

    /**
     * @brief Возвращает ссылку на последний элемент
     * @return Ссылка на последний элемент
     * @throw std::out_of_range если список пуст
     */
    T& back();

    /**
     * @brief Возвращает константную ссылку на последний элемент
     * @return Константная ссылка на последний элемент
     * @throw std::out_of_range если список пуст
     */
    const T& back() const;

    /**
     * @brief Добавляет элемент в начало списка
     * @param value Значение для добавления
     */
    void push_front(const T& value);

    /**
     * @brief Добавляет элемент в конец списка
     * @param value Значение для добавления
     */
    void push_back(const T& value);

    /**
     * @brief Удаляет первый элемент списка
     * @throw std::out_of_range если список пуст
     */
    void pop_front();

    /**
     * @brief Удаляет последний элемент списка
     * @throw std::out_of_range если список пуст
     */
    void pop_back();

    /**
     * @brief Вставляет элемент перед указанной позицией
     * @param pos Итератор, указывающий на позицию вставки
     * @param value Значение для вставки
     * @return Итератор на вставленный элемент
     */
    iterator insert(iterator pos, const T& value);

    /**
     * @brief Удаляет элемент в указанной позиции
     * @param pos Итератор, указывающий на удаляемый элемент
     * @return Итератор на следующий элемент
     */
    iterator erase(iterator pos);

    /**
     * @brief Очищает список
     */
    void clear();

    /**
     * @brief Оператор сравнения на равенство
     * @param other Список для сравнения
     * @return true если списки равны, false иначе
     */
    bool operator==(const CyclicList& other) const;

    /**
     * @brief Оператор сравнения на неравенство
     * @param other Список для сравнения
     * @return true если списки не равны, false иначе
     */
    bool operator!=(const CyclicList& other) const;
};

#include "cyclicListclass.h"

#endif 