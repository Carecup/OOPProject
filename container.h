#ifndef Container

#define Contaner
#include<iostream>

using namespace std;

class iterator;

template <typename T>
class container
{
private:
    int m_size;
    int m_capacity;
    T* m_data;

public:
    class Iterator;
    container()
    {
        m_size = 0;
        m_capacity = 0;
        m_data = NULL;
    }

    container(const container<T>& a)
    {
        m_size = a.m_size;
        m_capacity = m_size;
        m_data = NULL;
        if (m_size != 0)
            m_data = new T[m_size];
        else
            m_data = 0;
        for (int i = 0; i < m_size; ++i)
            m_data[i] = a.m_data[i];
    }

    container(int size)
    {
        m_size = size;
        m_capacity = size;
        if (size != 0)
            m_data = new T[size];
        else
            m_data = 0;
    }

    ~container() = default;

    int resize(int size)
    {
        if (size > m_capacity)
        {
            int new_capacity = max(size, m_size * 2);
            T* new_data = new T[new_capacity];
            for (int i = 0; i < m_size; ++i)
                new_data[i] = m_data[i];
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_size = size;
        return m_size;
    }

    void emplace_back(T val)
    {
        resize(m_size + 1);
        m_data[m_size - 1] = val;
    }
    void emplace_back()
    {
        T val = T();
        resize(m_size + 1);
        m_data[m_size - 1] = val;
    }

    int size() const
    {
        return m_size;
    }

    bool remove(int pos)
    {
        if (pos >= m_size || pos < 0)
            return false;

        int new_capacity = m_size - 1;
        T* temp = new T[new_capacity];
        if (!pos)
            for (int i = 1; i < m_size; i++)
                temp[i - 1] = m_data[i];
        else
        {
            for (int i = 0; i < pos; i++)
                temp[i] = m_data[i];
            for (int i = pos + 1; i < m_size; i++)
                temp[i - 1] = m_data[i];
        }

        delete[] m_data;
        m_size--;
        m_capacity--;
        m_data = new T[m_size];
        for (int i = 0; i < m_size; i++)
            m_data[i] = temp[i];

        delete[] temp;
        return true;
    }

    T& operator[] (int i)
    {
        return m_data[i];
    }

    Iterator begin() { return m_data; }
    Iterator end() { return m_data + m_size; }

    class Iterator
    {
    private:
        T* current;
    public:
        Iterator(T* first):current(first){}

        T& operator+ (int n) { return *(current + n); }
        T& operator- (int n) { return *(current - n); }

        T& operator++ (int) {return *current++;}
        T& operator-- (int) {return *current--;}
        T& operator++ () { return *++current; }
        T& operator-- () { return *--current; }

        bool operator!= (const Iterator& it) { return current != it.current; }
        bool operator== (const Iterator& it) { return current == it.current; }

        T&  getCurrent() { return *current; }
    };


};

template<typename T>
ostream& operator << (ostream& out, container<T> a)
{
    for (int i = 0; i < a.size(); ++i)
        out << a[i] << " ";
    return out;
};







#endif