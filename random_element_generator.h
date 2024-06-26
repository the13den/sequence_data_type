#ifndef RANDOM_ELEMENT_GENERATOR_H
#define RANDOM_ELEMENT_GENERATOR_H

#include <type_traits>
#include <random>
#include <string>
#include <limits>

// Define the random number generator
std::random_device rd;
std::mt19937 gen(rd());

// Generate random integer within a safe range
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type generate_random() {
    std::uniform_int_distribution<T> dis(std::numeric_limits<T>::min() / 2, std::numeric_limits<T>::max() / 2);
    return dis(gen);
}

// Generate random floating-point number within a safe range
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type generate_random() {
    std::uniform_real_distribution<T> dis(std::numeric_limits<T>::lowest() / 2, std::numeric_limits<T>::max() / 2);
    return dis(gen);
}

// Generate random boolean
template<>
bool generate_random<bool>() {
    std::uniform_int_distribution<int> dis(0, 1);
    return dis(gen) == 1;
}

// Generate random character
template<>
char generate_random<char>() {
    std::uniform_int_distribution<int> dis(32, 126); // Printable ASCII range
    return static_cast<char>(dis(gen));
}

// Generate random pointer
template<typename T>
typename std::enable_if<std::is_pointer<T>::value, T>::type generate_random() {
    using PointeeType = typename std::remove_pointer<T>::type;
    return new PointeeType(generate_random<PointeeType>());
}

// Generate random value (default case)
template<typename T>
typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_same<T, char>::value && !std::is_pointer<T>::value && !std::is_array<T>::value, T>::type generate_random() {
    return T(); // Use default constructor for other types
}



#endif // RANDOM_ELEMENT_GENERATOR_H
