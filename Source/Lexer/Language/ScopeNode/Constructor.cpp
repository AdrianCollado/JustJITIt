//===========================================================================//
//                                Just JIT It                                //
//                Implementing your own simple JIT compiler.                 //
//---------------------------------------------------------------------------//
// Copyright (C) 2017 - Adrian J. Collado                                    //
// All Rights Reserved                                                       //
//---------------------------------------------------------------------------//
// Permission is hereby granted, free of charge, to any person obtaining a   //
// copy of this software and associated documentation files (the             //
// “Software”), to deal in the Software without restriction, including       //
// without limitation the rights to use, copy, modify, merge, publish,       //
// distribute, sublicense, and/or sell copies of the Software, and to permit //
// persons to whom the Software is furnished to do so, subject to the        //
// following conditions:                                                     //
//                                                                           //
// The above copyright notice and this permission notice shall be included   //
// in all copies or substantial portions of the Software.                    //
//                                                                           //
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS   //
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                //
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN //
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,  //
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR     //
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE //
// USE OR OTHER DEALINGS IN THE SOFTWARE.                                    //
//===========================================================================//
#include "Lexer/Language.hpp"

#include <iostream>

using ScopeNode = Lexer::Language::ScopeNode;

ScopeNode::ScopeNode(ScopeNode::ScopeType type, ScopeNode* parent)
    : m_Type(type), m_Parent(parent) {}

// DEBUG PRINT --- REMOVE!!!!!!
// void ScopeNode::Print(std::string ident) {
//     std::size_t loc = 0;
//     while (loc < m_Types.size()) {
//         auto type = m_Types[loc];
//         auto val = m_Values[loc];

//         if (type == LangMatchType::Literal) {
//             std::cout << ident << "Literal: " << val << std::endl;
//         }
//         else if (type == LangMatchType::Number) {
//             std::cout << ident << "Number: " << val << std::endl;
//         }
//         else if (type == LangMatchType::Operator) {
//             std::cout << ident << "Operator: " << val << std::endl;
//         }
//         else if (type == LangMatchType::Keyword) {
//             std::cout << ident << "Keyword: " << val << std::endl;
//         }
//         else if (type == LangMatchType::Identifier) {
//             std::cout << ident << "Identifier: " << val << std::endl;
//         }
//         else if (type == LangMatchType::Scope) {
//             std::cout << ident << "Scope (";
//             int id = std::stoi(val);
//             std::cout << id << ", '";
//             ScopeType t = Child(id)->Type();
//             if (t == Parentheses) std::cout << "()': " << std::endl;
//             else if (t == Brackets) std::cout << "[]': " << std::endl;
//             else if (t == Braces) std::cout << "{}': " << std::endl;

//             Child(id)->Print(ident + "  ");
//         }

//         loc++;
//     }
// }