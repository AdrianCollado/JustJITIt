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
#include <locale>

void Lexer::Language::Tokenize() {
    // We utilize C++ locales to ensure that languages other than English are
    // correctly handled.
    std::locale locale;

    std::vector<std::string> matches;
    std::vector<TokenMatchType> matchTypes;
    std::vector<int> matchOrder;

    // Perform initial tokenization.
    std::size_t loc = 0;
    while (loc < m_Source.size()) {
        auto start = loc;

        // Handle String Literals
        if (m_Source[loc] == '"') {
            while (++loc < m_Source.size() && m_Source[loc] != '"');
            auto value = m_Source.substr(start+1, loc-start-1);
            auto iter = std::find(matches.begin(), matches.end(), value);
            auto index = std::distance(matches.begin(), iter);

            // Check if the string was already found as to prevent multiple
            // of the same string from existing.
            if (iter == matches.end()) {
                iter = matches.insert(iter, value);
                matchTypes.push_back(TokenMatchType::Literal);
            }
            else {
                if (matchTypes[index] != TokenMatchType::Literal) {
                    iter = matches.insert(iter, value);
                    matchTypes.push_back(TokenMatchType::Literal);
                }
            }

            matchOrder.push_back(index);
            loc++;
        }

        // Handle Comments
        else if (m_Source[loc] == '/') {
            if (++loc < m_Source.size() && m_Source[loc] == '/') {
                while (loc+1 < m_Source.size() && m_Source[++loc] != '\n');
                auto value = m_Source.substr(start, loc-start);
                auto iter = std::find(matches.begin(), matches.end(), value);
                auto index = std::distance(matches.begin(), iter);

                // Check if the string was already found as to prevent multiple
                // of the same string from existing.
                if (iter == matches.end()) {
                    iter = matches.insert(iter, value);
                    matchTypes.push_back(TokenMatchType::Comment);
                }
                else {
                    if (matchTypes[index] != TokenMatchType::Comment) {
                        iter = matches.insert(iter, value);
                        matchTypes.push_back(TokenMatchType::Comment);
                    }
                }

                matchOrder.push_back(index);
            }
            else if (loc+1 < m_Source.size() && m_Source[loc] == '*') {
                while (loc+2 < m_Source.size()) {
                    if (m_Source[++loc] == '*') {
                        if (m_Source[++loc] == '/') break;
                    }
                }
                auto value = m_Source.substr(start, loc-start+1);
                auto iter = std::find(matches.begin(), matches.end(), value);
                auto index = std::distance(matches.begin(), iter);

                // Check if the string was already found as to prevent multiple
                // of the same string from existing.
                if (iter == matches.end()) {
                    iter = matches.insert(iter, value);
                    matchTypes.push_back(TokenMatchType::Comment);
                }
                else {
                    if (matchTypes[index] != TokenMatchType::Comment) {
                        iter = matches.insert(iter, value);
                        matchTypes.push_back(TokenMatchType::Comment);
                    }
                }

                matchOrder.push_back(index);
            }
            loc++;
        }

        // Handle Number Literals
        else if (std::isdigit(m_Source[loc], locale)) {
            while (++loc < m_Source.size() && std::isdigit(m_Source[loc], locale));
            auto value = m_Source.substr(start, loc-start);
            auto iter = std::find(matches.begin(), matches.end(), value);
            auto index = std::distance(matches.begin(), iter);

            // Check if the string was already found as to prevent multiple
            // of the same string from existing.
            if (iter == matches.end()) {
                iter = matches.insert(iter, value);
                matchTypes.push_back(TokenMatchType::Number);
            }
            else {
                if (matchTypes[index] != TokenMatchType::Number) {
                    iter = matches.insert(iter, value);
                    matchTypes.push_back(TokenMatchType::Number);
                }
            }

            matchOrder.push_back(index);
        }

        // Handle Strings
        else if (std::isalnum(m_Source[loc], locale) || m_Source[loc] == '_') {
            while (++loc < m_Source.size() && (std::isalnum(m_Source[loc], locale) || m_Source[loc] == '_'));
            auto value = m_Source.substr(start, loc-start);
            auto iter = std::find(matches.begin(), matches.end(), value);
            auto index = std::distance(matches.begin(), iter);

            // Check if the string was already found as to prevent multiple
            // of the same string from existing.
            if (iter == matches.end()) {
                iter = matches.insert(iter, value);
                matchTypes.push_back(TokenMatchType::String);
            }
            else {
                if (matchTypes[index] != TokenMatchType::String) {
                    iter = matches.insert(iter, value);
                    matchTypes.push_back(TokenMatchType::String);
                }
            }

            matchOrder.push_back(index);
        }

        // Handle Punctuation
        else if (std::ispunct(m_Source[loc], locale)) {
            auto value = m_Source.substr(start, 1);
            auto iter = std::find(matches.begin(), matches.end(), value);
            auto index = std::distance(matches.begin(), iter);

            // Check if the string was already found as to prevent multiple
            // of the same string from existing.
            if (iter == matches.end()) {
                iter = matches.insert(iter, value);
                matchTypes.push_back(TokenMatchType::Punctuation);
            }
            else {
                if (matchTypes[index] != TokenMatchType::Punctuation) {
                    iter = matches.insert(iter, value);
                    matchTypes.push_back(TokenMatchType::Punctuation);
                }
            }

            matchOrder.push_back(index);
            loc++;
        }

        // Handle Whitespace
        else if (std::isspace(m_Source[loc], locale)) {
            while (++loc < m_Source.size() && std::isspace(m_Source[loc], locale));
            auto value = m_Source.substr(start, loc-start);
            auto iter = std::find(matches.begin(), matches.end(), value);
            auto index = std::distance(matches.begin(), iter);

            // Check if the string was already found as to prevent multiple
            // of the same string from existing.
            if (iter == matches.end()) {
                iter = matches.insert(iter, value);
                matchTypes.push_back(TokenMatchType::Space);
            }
            else {
                if (matchTypes[index] != TokenMatchType::Space) {
                    iter = matches.insert(iter, value);
                    matchTypes.push_back(TokenMatchType::Space);
                }
            }

            matchOrder.push_back(index);
        }

        start = loc;
    }

    // Convert ordered identifiers to lists of values.
    std::vector<TokenMatchType> types;
    std::vector<std::string> values;

    for (auto val : matchOrder) {
        types.push_back(matchTypes[val]);
        values.push_back(matches[val]);
    }

    // Extract out multicharacter punctuation.
    for (std::size_t i = 0; i < types.size(); i++) {
        if (types[i] == TokenMatchType::Punctuation) {
            if (i+1 < types.size() && types[i+1] == TokenMatchType::Punctuation) {
                if (i+2 < types.size() && types[i+2] == TokenMatchType::Punctuation) {
                    auto value = values[i] + values[i+1] + values[i+2];

                    // Punctuation Lookup
                    const std::array<std::string, 4> punct = {
                        ">>=", "<<=",
                        "&&=", "||="
                    };

                    auto iter = std::find(punct.begin(), punct.end(), value);
                    if (iter != punct.end()) {
                        m_Types.push_back(TokenMatchType::Punctuation);
                        m_Values.push_back(value);
                        i += 2;
                        continue;
                    }
                }

                auto value = values[i] + values[i+1];

                // Punctuation Lookup
                const std::array<std::string, 22> punct = {
                    "->", "[]", "()", "{}",
                    "++", "--",
                    "==", "!=", ">=", "<=",
                    "&&", "||",
                    "<<", ">>",
                    "+=", "-=", "*=", "/=", "%=",
                    "&=", "|=", "^="
                };

                auto iter = std::find(punct.begin(), punct.end(), value);
                if (iter != punct.end()) {
                    m_Types.push_back(TokenMatchType::Punctuation);
                    m_Values.push_back(value);
                    i++;
                    continue;
                }
            }
        }
        
        m_Types.push_back(types[i]);
        m_Values.push_back(values[i]);
    }

    // Remove whitespace and comments.
    for (std::size_t i = 0; i < m_Types.size(); i++) {
        if (m_Types[i] == TokenMatchType::Space || m_Types[i] == TokenMatchType::Comment) m_Values[i].clear();
    }
    m_Types.erase(std::remove(m_Types.begin(), m_Types.end(), TokenMatchType::Space), m_Types.end());
    m_Types.erase(std::remove(m_Types.begin(), m_Types.end(), TokenMatchType::Comment), m_Types.end());
    m_Values.erase(std::remove(m_Values.begin(), m_Values.end(), std::string()), m_Values.end());
}