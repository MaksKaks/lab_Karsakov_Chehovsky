#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <stdexcept>
#include "TLists.h"

using namespace std;

template <typename TKey, typename TValue>
class Map {
public:
    
    struct Pair {
        TKey key;
        TValue value;
        Pair(const TKey& k, const TValue& v) : key(k), value(v) {}
        bool operator<(const Pair& other) const { return key < other.key; }
        bool operator>(const Pair& other) const { return key > other.key; }
        bool operator==(const Pair& other) const { return key == other.key; }
    };
    
    
    virtual ~Map() = default;
    
    
    virtual TValue* find(const TKey& key) = 0;
    virtual void Insert(const TKey& key, const TValue& value) = 0;
    virtual void delete(const TKey& key) = 0;
    virtual int count() const = 0;
    virtual bool isempty() const { return Count() == 0; }
    virtual TValue& operator[](const TKey& key) = 0;
    virtual vector<TKey> keys() const = 0;
    virtual vector<TValue> values() const = 0;
    virtual bool containsKey(const TKey& key) const {
        return find(key) != nullptr;
    }
};

template <typename TKey, typename TValue>
class OrderedMap : public Map<TKey, TValue> {
private:
    using typename Map<TKey, TValue>::Pair;
    vector<Pair> data;
    int BinarySearchWithPos(const TKey& key) const {
        int left = 0;
        int right = data.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (data[mid].key == key) {
                return mid;  
            }
            if (data[mid].key < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -left - 1;
    }
    
public:
    OrderedMap() = default;
    ~OrderedMap() = default;
    
    TValue* Find(const TKey& key) override {
        int result = BinarySearchWithPos(key);
        if (result >= 0) {
            return &data[result].value;
        }
        return nullptr;
    }
    
    const TValue* Find(const TKey& key) const override {
        int result = BinarySearchWithPos(key);
        if (result >= 0) {
            return &data[result].value;
        }
        return nullptr;
    }

    void Insert(const TKey& key, const TValue& value) override {
        int result = BinarySearchWithPos(key);
        
        if (result >= 0) {
            return;
        }
        
        // Преобразуем отрицательный результат обратно в позицию для вставки
        size_t insertPos = -result - 1;
        
        // Вставляем на вычисленную позицию
        data.insert(data.begin() + insertPos, Pair(key, value));
    }
    
    void Delete(const TKey& key) override {
        int result = BinarySearchWithPos(key);
        
        if (result < 0) {
            throw invalid_argument("Key not found");
        }
        
        data.erase(data.begin() + result);
    }
    
    int Count() const override {
        return data.size();
    }
    
    TValue& operator[](const TKey& key) override {
        int result = BinarySearchWithPos(key);
        
        if (result >= 0) {
            // Ключ найден - возвращаем ссылку на значение
            return data[result].value;
        }
        
        // Ключ не найден - вставляем новый элемент
        size_t insertPos = -result - 1;
        data.insert(data.begin() + insertPos, Pair(key, TValue()));
        return data[insertPos].value;
    }
    
    const TValue& operator[](const TKey& key) const override {
        int result = BinarySearchWithPos(key);
        
        if (result < 0) {
            throw invalid_argument("Key not found");
        }
        
        return data[result].value;
    }
    
    vector<TKey> Keys() const override {
        vector<TKey> result;
        result.reserve(data.size());
        for (const auto& pair : data) {
            result.push_back(pair.key);
        }
        return result;
    }
    
    vector<TValue> Values() const override {
        vector<TValue> result;
        result.reserve(data.size());
        for (const auto& pair : data) {
            result.push_back(pair.value);
        }
        return result;
    }
    
    void Clear() override {
        data.clear();
    }
    
    void Print() const {
        if (data.empty()) {
            cout << "{}" << endl;
            return;
        }
        
        cout << "{" << endl;
        for (size_t i = 0; i < data.size(); i++) {
            cout << "  " << data[i].key << " : " << data[i].value;
            if (i != data.size() - 1) {
                cout << ",";
            }
            cout << endl;
        }
        cout << "}" << endl;
    }
};

// НЕУПОРЯДОЧЕННАЯ ТАБЛИЦА НА ОДНОСВЯЗНОМ СПИСКЕ (с использованием TSinglyList)
template <typename TKey, typename TValue>
class UnorderedListMap : public Map<TKey, TValue> {
private:
    using typename Map<TKey, TValue>::Pair;
    
    // Вспомогательная структура для хранения в списке
    struct ListPair {
        TKey key;
        TValue value;
        
        ListPair() = default;
        ListPair(const TKey& k, const TValue& v) : key(k), value(v) {}
        
        // Для сравнения при поиске
        bool operator==(const TKey& otherKey) const { return key == otherKey; }
    };
    
    TSinglyList<ListPair> list;  // Используем ваш класс TSinglyList
    
public:
    UnorderedListMap() = default;
    ~UnorderedListMap() = default;
    
    // Поиск по ключу - O(n)
    TValue* Find(const TKey& key) override {
        for (int i = 0; i < list.size(); i++) {
            if (list[i].key == key) {
                return &list[i].value;
            }
        }
        return nullptr;
    }
    
    const TValue* Find(const TKey& key) const override {
        // Создаем неконстантную версию для поиска
        UnorderedListMap* nonConstThis = const_cast<UnorderedListMap*>(this);
        return nonConstThis->Find(key);
    }
    
    // Вставка в начало списка - O(n) из-за проверки уникальности
    void Insert(const TKey& key, const TValue& value) override {
        // Проверяем уникальность ключа
        if (Find(key) != nullptr) {
            return; // ключ уже существует
        }
        
        // Вставляем в начало списка
        ListPair newPair(key, value);
        list.PushFront(newPair);
    }
    
    // Удаление по ключу - O(n)
    void Delete(const TKey& key) override {
        if (list.isEmpty()) {
            throw invalid_argument("Key not found");
        }
        
        // Проверяем первый элемент
        if (list.GetFirst()->val.key == key) {
            list.PopFront();
            return;
        }
        
        // Ищем элемент для удаления
        for (int i = 1; i < list.size(); i++) {
            if (list[i].key == key) {
                // Удаляем элемент после i-1 (т.е. элемент i)
                list.EraseAfter(i - 1);
                return;
            }
        }
        
        throw invalid_argument("Key not found");
    }
    
    // Количество записей - O(1) (если size() работает за O(1))
    int Count() const override {
        return list.size();
    }
    
    // Оператор доступа (неконстантный)
    TValue& operator[](const TKey& key) override {
        TValue* val = Find(key);
        if (val != nullptr) {
            return *val;
        }
        
        // Если ключа нет - создаем элемент со значением по умолчанию
        ListPair newPair(key, TValue());
        list.PushFront(newPair);
        
        // Возвращаем ссылку на только что созданный элемент
        return list.GetFirst()->val.value;
    }
    
    // Константный оператор доступа
    const TValue& operator[](const TKey& key) const override {
        const TValue* val = Find(key);
        if (val == nullptr) {
            throw invalid_argument("Key not found");
        }
        return *val;
    }
    
    // Получение всех ключей (в порядке, обратном вставке)
    vector<TKey> Keys() const override {
        vector<TKey> result;
        result.reserve(list.size());
        
        for (int i = 0; i < list.size(); i++) {
            result.push_back(list[i].key);
        }
        return result;
    }
    
    // Получение всех значений (в порядке, обратном вставке)
    vector<TValue> Values() const override {
        vector<TValue> result;
        result.reserve(list.size());
        
        for (int i = 0; i < list.size(); i++) {
            result.push_back(list[i].value);
        }
        return result;
    }
    
    // Очистка
    void Clear() override {
        while (!list.isEmpty()) {
            list.PopFront();
        }
    }
    
    // Для отладки
    void Print() const {
        if (list.isEmpty()) {
            cout << "{}" << endl;
            return;
        }
        
        cout << "{" << endl;
        for (int i = 0; i < list.size(); i++) {
            cout << "  " << list[i].key << " : " << list[i].value;
            if (i != list.size() - 1) {
                cout << ",";
            }
            cout << endl;
        }
        cout << "}" << endl;
    }
};

#endif 