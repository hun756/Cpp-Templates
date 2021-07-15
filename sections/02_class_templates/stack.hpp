#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include <vector>

namespace myTemplate {
    template<typename T>
    class Stack {
    public:
        /**
         * @brief Construct a new Stack object
         * 
         */
        Stack() = default;


        /**
         * @brief 
         * 
         * @return const T& 
         */
        const T& top();


        /**
         * @brief 
         * 
         * @param val 
         */
        void push(const T& val);


        /**
         * @brief 
         * 
         */
        void pop();


        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool isEmpty() const;

    private:
        /**
         * @brief 
         * 
         */
        std::vector<T> elems;
    };
}


//> implementation

namespace myTemplate {
    template<typename T>
    const T& Stack<T>::top() 
    {
        return elems.empty() ? 
            throw std::domain_error("Error..! Stack is empty") 
                : elems.back();
    }


    template<typename T>
    void Stack<T>::push(const T& val) 
    {
        elems.push_back(val);
    }


    template<typename T>
    void Stack<T>::pop() 
    {
        elems.empty() ? throw std::domain_error("Error..! Stack is empty") 
            : elems.pop_back();
    }


    template<typename T>
    bool Stack<T>::isEmpty() const
    {
        return elems.empty();
    }
}

#endif /* end of include guard : STACK_HPP */