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

#include <algorithm>
#include <array>
#include <iostream>

void Lexer::Language::Analyze() {
    m_Scopes = ScopeNode(ScopeNode::Global, nullptr);
    ScopeNode* scope = &m_Scopes;

    // We'll convert each token into a language-specific token.
    std::size_t loc = 0;

    while (loc < m_Types.size()) {
        // Handle operators, as well as scoping.
        if (m_Types[loc] == TokenMatchType::Punctuation) {
            auto value = m_Values[loc];

            // Handle empty scopes.
            if (value == "{}") {
                int id = scope->Attach(ScopeNode::Braces);
                scope->Attach(LangMatchType::Scope, std::to_string(id));
            }
            else if (value == "[]") {
                int id = scope->Attach(ScopeNode::Brackets);
                scope->Attach(LangMatchType::Scope, std::to_string(id));
            }
            else if (value == "()") {
                int id = scope->Attach(ScopeNode::Parentheses);
                scope->Attach(LangMatchType::Scope, std::to_string(id));
            }

            // Handle opening scopes.
            else if (value == "{") {
                int id = scope->Attach(ScopeNode::Braces);
                scope->Attach(LangMatchType::Scope, std::to_string(id));
                scope = scope->Child(id);
            }
            else if (value == "[") {
                int id = scope->Attach(ScopeNode::Brackets);
                scope->Attach(LangMatchType::Scope, std::to_string(id));
                scope = scope->Child(id);
            }
            else if (value == "(") {
                int id = scope->Attach(ScopeNode::Parentheses);
                scope->Attach(LangMatchType::Scope, std::to_string(id));
                scope = scope->Child(id);
            }

            // Handle closing scopes.
            else if (value == "}") {
                if (scope->Type() == ScopeNode::Braces) {
                    scope = scope->Parent();
                }
                else {
                    // TODO: Handle error elegantly.
                    std::cerr << "Incorrect Scoping." << std::endl;
                    std::abort();
                }
            }
            else if (value == "]") {
                if (scope->Type() == ScopeNode::Brackets) {
                    scope = scope->Parent();
                }
                else {
                    // TODO: Handle error elegantly.
                    std::cerr << "Incorrect Scoping." << std::endl;
                    std::abort();
                }
            }
            else if (value == ")") {
                if (scope->Type() == ScopeNode::Parentheses) {
                    scope = scope->Parent();
                }
                else {
                    // TODO: Handle error elegantly.
                    std::cerr << "Incorrect Scoping." << std::endl;
                    std::abort();
                }
            }
            else {
                // Handle operators.
                const std::array<std::string, 45> operators = {
                    ">>=", "<<=",
                    "&&=", "||=",
                    "->", "[]", "()", "{}",
                    "++", "--",
                    "==", "!=", ">=", "<=",
                    "&&", "||",
                    "<<", ">>",
                    "+=", "-=", "*=", "/=", "%=",
                    "&=", "|=", "^=",
                    "+", "-", "*", "/", "%",
                    "&", "|", "^",
                    "=", "!", "~", ">", "<", ".",
                    "?", ":", "?:",
                    ",", ";"
                };

                auto iter = std::find(operators.begin(), operators.end(), value);
                if (iter != operators.end()) {
                    scope->Attach(LangMatchType::Operator, value);
                }
                else {
                    // TODO: Handle the error.
                    std::cerr << "Invalid Operator." << std::endl;
                    std::abort();
                }
            }
        }

        // Handle keywords and identifiers
        else if (m_Types[loc] == TokenMatchType::String) {
            auto value = m_Values[loc];
            const std::array<std::string, 20> keywords = {
                "func",
                "f32", "f64",
                "i8", "i16", "i32", "i64"
                "u8", "u16", "u32", "u64",
                "if", "else",
                "do", "while", "for",
                "to", "in",
                "def", "use"
            };

            auto iter = std::find(keywords.begin(), keywords.end(), value);
            if (iter != keywords.end()) {
                scope->Attach(LangMatchType::Keyword, value);
            }
            else {
                scope->Attach(LangMatchType::Identifier, value);
            }
        }

        // Handle numbers
        else if (m_Types[loc] == TokenMatchType::Number) {
            auto& n1 = m_Values[loc];
            if (m_Types[loc + 1] == TokenMatchType::Punctuation) {
                if (m_Values[loc + 1] == ".") {
                    if (m_Types[loc + 2] == TokenMatchType::Number) {
                        auto& n2 = m_Values[loc + 2];
                        if (m_Types[loc + 3] == TokenMatchType::Punctuation) {
                            if (m_Values[loc + 3] == ".") {
                                // TODO: Handle the error.
                                std::cerr << "Invalid Number." << std::endl;
                                std::abort();
                            }
                            else {
                                scope->Attach(LangMatchType::Number, n1 + "." + n2);
                                loc += 2;
                            }
                        }
                        else {
                            scope->Attach(LangMatchType::Number, n1 + "." + n2);
                            loc += 2;
                        }
                    }
                    else {
                        // TODO: Handle the error.
                        std::cerr << "Invalid Number." << std::endl;
                        std::abort();
                    }
                }
                else {
                    scope->Attach(LangMatchType::Number, n1);
                }
            }
            else {
                scope->Attach(LangMatchType::Number, n1);
            }
        }

        loc++;
    }
}