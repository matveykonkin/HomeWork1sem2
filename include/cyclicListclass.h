/**
 * @file cyclicListclass.h
 * @brief Реализация методов класса CyclicList
 */

#ifndef CYCLICLISTCLASS_H
#define CYCLICLISTCLASS_H

#include "cyclicList.h"

/**
 * @brief Конструктор итератора
 * @param node Текущий узел
 * @param head Головной узел списка
 * @param is_end Флаг конца списка
 */
template <typename T>
CyclicList<T>::iterator::iterator(std::shared_ptr<Node> node, 
                                std::shared_ptr<Node> head, 
                                bool is_end)
    : current(node), head(head), is_end(is_end) {}

/**
 * @brief Оператор разыменования
 * @return Ссылка на данные текущего узла
 */
template <typename T>
typename CyclicList<T>::iterator::reference 
CyclicList<T>::iterator::operator*() const { 
    return current->data; 
}

/**
 * @brief Оператор доступа к членам
 * @return Указатель на данные текущего узла
 */
template <typename T>
typename CyclicList<T>::iterator::pointer 
CyclicList<T>::iterator::operator->() const { 
    return &current->data; 
}

/**
 * @brief Префиксный оператор инкремента
 * @return Ссылка на итератор
 */
template <typename T>
typename CyclicList<T>::iterator& 
CyclicList<T>::iterator::operator++() {
    if (!current) return *this;
    if (current->next == head) is_end = true;
    current = current->next;
    return *this;
}

/**
 * @brief Постфиксный оператор инкремента
 * @return Итератор до инкремента
 */
template <typename T>
typename CyclicList<T>::iterator 
CyclicList<T>::iterator::operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
}

/**
 * @brief Префиксный оператор декремента
 * @return Ссылка на итератор
 */
template <typename T>
typename CyclicList<T>::iterator& 
CyclicList<T>::iterator::operator--() {
    if (!current) return *this;
    if (is_end) {
        is_end = false;
    } else {
        current = current->prev.lock();
    }
    return *this;
}

/**
 * @brief Постфиксный оператор декремента
 * @return Итератор до декремента
 */
template <typename T>
typename CyclicList<T>::iterator 
CyclicList<T>::iterator::operator--(int) {
    iterator tmp = *this;
    --(*this);
    return tmp;
}

/**
 * @brief Оператор сравнения на равенство
 * @param other Итератор для сравнения
 * @return true если итераторы равны, false иначе
 */
template <typename T>
bool CyclicList<T>::iterator::operator==(const iterator& other) const {
    return current == other.current && is_end == other.is_end;
}

/**
 * @brief Оператор сравнения на неравенство
 * @param other Итератор для сравнения
 * @return true если итераторы не равны, false иначе
 */
template <typename T>
bool CyclicList<T>::iterator::operator!=(const iterator& other) const {
    return !(*this == other);
}

/**
 * @brief Конструктор константного итератора
 * @param node Текущий узел
 * @param head Головной узел списка
 * @param is_end Флаг конца списка
 */
template <typename T>
CyclicList<T>::const_iterator::const_iterator(std::shared_ptr<Node> node,
                                            std::shared_ptr<Node> head,
                                            bool is_end)
    : current(node), head(head), is_end(is_end) {}

/**
 * @brief Оператор разыменования
 * @return Константная ссылка на данные текущего узла
 */
template <typename T>
typename CyclicList<T>::const_iterator::reference 
CyclicList<T>::const_iterator::operator*() const { 
    return current->data; 
}

/**
 * @brief Оператор доступа к членам
 * @return Константный указатель на данные текущего узла
 */
template <typename T>
typename CyclicList<T>::const_iterator::pointer 
CyclicList<T>::const_iterator::operator->() const { 
    return &current->data; 
}

/**
 * @brief Префиксный оператор инкремента
 * @return Ссылка на итератор
 */
template <typename T>
typename CyclicList<T>::const_iterator& 
CyclicList<T>::const_iterator::operator++() {
    if (!current) return *this;
    if (current->next == head) is_end = true;
    current = current->next;
    return *this;
}

/**
 * @brief Постфиксный оператор инкремента
 * @return Итератор до инкремента
 */
template <typename T>
typename CyclicList<T>::const_iterator 
CyclicList<T>::const_iterator::operator++(int) {
    const_iterator tmp = *this;
    ++(*this);
    return tmp;
}

/**
 * @brief Префиксный оператор декремента
 * @return Ссылка на итератор
 */
template <typename T>
typename CyclicList<T>::const_iterator& 
CyclicList<T>::const_iterator::operator--() {
    if (!current) return *this;
    if (is_end) {
        is_end = false;
    } else {
        current = current->prev.lock();
    }
    return *this;
}

/**
 * @brief Постфиксный оператор декремента
 * @return Итератор до декремента
 */
template <typename T>
typename CyclicList<T>::const_iterator 
CyclicList<T>::const_iterator::operator--(int) {
    const_iterator tmp = *this;
    --(*this);
    return tmp;
}

/**
 * @brief Оператор сравнения на равенство
 * @param other Итератор для сравнения
 * @return true если итераторы равны, false иначе
 */
template <typename T>
bool CyclicList<T>::const_iterator::operator==(const const_iterator& other) const {
    return current == other.current && is_end == other.is_end;
}

/**
 * @brief Оператор сравнения на неравенство
 * @param other Итератор для сравнения
 * @return true если итераторы не равны, false иначе
 */
template <typename T>
bool CyclicList<T>::const_iterator::operator!=(const const_iterator& other) const {
    return !(*this == other);
}

/**
 * @brief Конструктор по умолчанию
 * 
 * Создает пустой список
 */
template <typename T>
CyclicList<T>::CyclicList() : head(nullptr), size_(0) {}

/**
 * @brief Конструктор с инициализацией из списка
 * @param init Список инициализации
 */
template <typename T>
CyclicList<T>::CyclicList(std::initializer_list<T> init) : CyclicList() {
    for (const auto& item : init) push_back(item);
}

/**
 * @brief Возвращает итератор на начало списка
 * @return Итератор на первый элемент
 */
template <typename T>
typename CyclicList<T>::iterator CyclicList<T>::begin() { 
    return iterator(head, head); 
}

/**
 * @brief Возвращает итератор на конец списка
 * @return Итератор на позицию после последнего элемента
 */
template <typename T>
typename CyclicList<T>::iterator CyclicList<T>::end() { 
    return iterator(head, head, true); 
}

/**
 * @brief Возвращает константный итератор на начало списка
 * @return Константный итератор на первый элемент
 */
template <typename T>
typename CyclicList<T>::const_iterator CyclicList<T>::begin() const { 
    return const_iterator(head, head); 
}

/**
 * @brief Возвращает константный итератор на конец списка
 * @return Константный итератор на позицию после последнего элемента
 */
template <typename T>
typename CyclicList<T>::const_iterator CyclicList<T>::end() const { 
    return const_iterator(head, head, true); 
}

/**
 * @brief Возвращает константный итератор на начало списка
 * @return Константный итератор на первый элемент
 */
template <typename T>
typename CyclicList<T>::const_iterator CyclicList<T>::cbegin() const { 
    return const_iterator(head, head); 
}

/**
 * @brief Возвращает константный итератор на конец списка
 * @return Константный итератор на позицию после последнего элемента
 */
template <typename T>
typename CyclicList<T>::const_iterator CyclicList<T>::cend() const { 
    return const_iterator(head, head, true); 
}

/**
 * @brief Проверяет, пуст ли список
 * @return true если список пуст, false иначе
 */
template <typename T>
bool CyclicList<T>::empty() const { 
    return size_ == 0; 
}

/**
 * @brief Возвращает размер списка
 * @return Количество элементов в списке
 */
template <typename T>
size_t CyclicList<T>::size() const { 
    return size_; 
}

/**
 * @brief Возвращает ссылку на первый элемент
 * @return Ссылка на первый элемент
 * @throw std::out_of_range если список пуст
 */
template <typename T>
T& CyclicList<T>::front() {
    if (empty()) throw std::out_of_range("List is empty");
    return head->data;
}

/**
 * @brief Возвращает константную ссылку на первый элемент
 * @return Константная ссылка на первый элемент
 * @throw std::out_of_range если список пуст
 */
template <typename T>
const T& CyclicList<T>::front() const {
    if (empty()) throw std::out_of_range("List is empty");
    return head->data;
}

/**
 * @brief Возвращает ссылку на последний элемент
 * @return Ссылка на последний элемент
 * @throw std::out_of_range если список пуст
 */
template <typename T>
T& CyclicList<T>::back() {
    if (empty()) throw std::out_of_range("List is empty");
    return head->prev.lock()->data;
}

/**
 * @brief Возвращает константную ссылку на последний элемент
 * @return Константная ссылка на последний элемент
 * @throw std::out_of_range если список пуст
 */
template <typename T>
const T& CyclicList<T>::back() const {
    if (empty()) throw std::out_of_range("List is empty");
    return head->prev.lock()->data;
}

/**
 * @brief Добавляет элемент в начало списка
 * @param value Значение для добавления
 */
template <typename T>
void CyclicList<T>::push_front(const T& value) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
    
    if (empty()) {
        head = new_node;
        head->next = head;
        head->prev = head;
    } else {
        new_node->next = head;
        new_node->prev = head->prev;
        head->prev.lock()->next = new_node;
        head->prev = new_node;
        head = new_node;
    }
    
    size_++;
}

/**
 * @brief Добавляет элемент в конец списка
 * @param value Значение для добавления
 */
template <typename T>
void CyclicList<T>::push_back(const T& value) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
    
    if (empty()) {
        head = new_node;
        head->next = head;
        head->prev = head;
    } else {
        new_node->next = head;
        new_node->prev = head->prev;
        head->prev.lock()->next = new_node;
        head->prev = new_node;
    }
    
    size_++;
}

/**
 * @brief Удаляет первый элемент списка
 * @throw std::out_of_range если список пуст
 */
template <typename T>
void CyclicList<T>::pop_front() {
    if (empty()) throw std::out_of_range("List is empty");
    
    if (size_ == 1) {
        head.reset();
    } else {
        auto old_head = head;
        head = head->next;
        head->prev = old_head->prev;
        old_head->prev.lock()->next = head;
        old_head.reset();
    }
    
    size_--;
}

/**
 * @brief Удаляет последний элемент списка
 * @throw std::out_of_range если список пуст
 */
template <typename T>
void CyclicList<T>::pop_back() {
    if (empty()) throw std::out_of_range("List is empty");
    
    if (size_ == 1) {
        head.reset();
    } else {
        auto last_node = head->prev.lock();
        last_node->prev.lock()->next = head;
        head->prev = last_node->prev;
        last_node.reset();
    }
    
    size_--;
}

/**
 * @brief Вставляет элемент перед указанной позицией
 * @param pos Итератор, указывающий на позицию вставки
 * @param value Значение для вставки
 * @return Итератор на вставленный элемент
 */
template <typename T>
typename CyclicList<T>::iterator CyclicList<T>::insert(iterator pos, const T& value) {
    if (pos == begin()) {
        push_front(value);
        return begin();
    }
    else if (pos == end()) {
        push_back(value);
        return --end();
    }
    else {
        std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
        auto prev_node = pos.current->prev.lock();
        
        new_node->next = pos.current;
        new_node->prev = prev_node;
        prev_node->next = new_node;
        pos.current->prev = new_node;
        
        size_++;
        return iterator(new_node, head);
    }
}

/**
 * @brief Удаляет элемент в указанной позиции
 * @param pos Итератор, указывающий на удаляемый элемент
 * @return Итератор на следующий элемент
 */
template <typename T>
typename CyclicList<T>::iterator CyclicList<T>::erase(iterator pos) {
    if (empty()) throw std::out_of_range("List is empty");
    if (pos == end()) return pos;
    
    if (pos == begin()) {
        pop_front();
        return begin();
    }
    else {
        auto next_node = pos.current->next;
        auto prev_node = pos.current->prev.lock();
        
        prev_node->next = next_node;
        next_node->prev = prev_node;
        pos.current.reset();
        
        size_--;
        return iterator(next_node, head);
    }
}

/**
 * @brief Очищает список
 */
template <typename T>
void CyclicList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

/**
 * @brief Оператор сравнения на равенство
 * @param other Список для сравнения
 * @return true если списки равны, false иначе
 */
template <typename T>
bool CyclicList<T>::operator==(const CyclicList& other) const {
    if (size_ != other.size_) return false;
    
    auto it1 = begin();
    auto it2 = other.begin();
    
    for (; it1 != end() && it2 != other.end(); ++it1, ++it2) {
        if (*it1 != *it2) return false;
    }
    
    return true;
}

/**
 * @brief Оператор сравнения на неравенство
 * @param other Список для сравнения
 * @return true если списки не равны, false иначе
 */
template <typename T>
bool CyclicList<T>::operator!=(const CyclicList& other) const {
    return !(*this == other);
}

#endif 