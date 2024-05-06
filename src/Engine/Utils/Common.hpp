/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

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

#define LOG_MESSAGE(message) \
    std::cout << "\033[33m" << message << "\033[33m \033[0m\n"; 

#endif // COMMON_HPP

/**  
 * MIT License
 *  
 * Copyright (c) 2024 Kevin Daniel Taylor
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *  
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *  
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */