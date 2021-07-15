#include <type_traits>

namespace myTemplates {
    /**
    *  @brief 
    *      This method finds the larger of the two variables.
    *
    *  @tparam T
    *      Template parameter type      
    *
    *  @param first
    *      First parameter required for comparison.
    *  
    *  @param second 
    *      Second parameter required for comparison.
    *
    *  @return T
    *
    *  @retval
    *      if b < a then yield a else yield b
    */
    template<typename T>
    constexpr T max(const T& first, const T& second) {

        return first < second ? second : first;
    }


    /**
     *  @brief 
     *      This method finds the larger of the two different variables.
     *
     *  @tparam T1 
     *      Firt template parameter type
     *
     *  @tparam T2 
     *       Second template parameter type
     *
     *  @param first
     *      First parameter required for comparison.
     * 
     *  @param second
     *      Second parameter required for comparison.
     *
     *  @return std::common_type<T1, T2>
     *      Returns common type of T1 and T2 
     */
    template<typename T1, typename T2>
    constexpr typename std::common_type<T1, T2>::type max(const T1& first, const T2& second) {

        return first < second ? second : first;
    }

}