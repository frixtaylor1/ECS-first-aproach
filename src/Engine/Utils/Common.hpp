#ifndef COMMON_HPP
#define COMMON_HPP

#define interface   struct
#define implements  public
#define extends     public

#include "./SmartPointer/ScopePointer.hpp"

#include <iostream>

#define MUST_IMPLEMENT \
    std::cerr << "\033[31m" << "Warning: " << "\033[33m" << "ln[" << __LINE__ << "] in file[" << "\033[32m" << __FILE__ << "\033[33m" << "] must implement: " << "\033[32m" << "fn[" << __func__ << "\033[33m" << "]" << "\033[0m" << "\n"; \
    exit(EXIT_FAILURE);


#endif // COMMON_HPP