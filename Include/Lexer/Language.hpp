//===========================================================================//
//                                Just JIT It                                //
//                Implementing your own simple JIT compiler.                 //
//---------------------------------------------------------------------------//
// This file is the definition of the Lexer class for our test language.     //
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
#pragma once

#include <string>
#include <vector>

namespace Lexer {
    class Language {
    public:
        enum class TokenMatchType {
            Literal,
            Number,
            Punctuation,
            String,
            Space,
            Comment
        };

        enum class LangMatchType {
            Literal,
            Number,
            Operator,
            Keyword,
            Identifier,
            Scope
        };

        class ScopeNode {
        public:
            enum ScopeType {
                Global,         // Global Scope
                Parentheses,    // (..)
                Brackets,       // [..]
                Braces          // {..}
            };

            ScopeNode() = default;
            ScopeNode(ScopeType type, ScopeNode* parent);
            int Attach(ScopeType type);
            void Attach(LangMatchType type, std::string value);

            ScopeNode* Parent();
            ScopeNode* Child(int id);
            ScopeType Type() const;

        private:
            ScopeType m_Type;
            ScopeNode* m_Parent;

            std::vector<ScopeNode> m_Children;

            std::vector<LangMatchType> m_Types;
            std::vector<std::string> m_Values;
        };

        Language() {}
        ~Language() = default;

        void LoadFile(const std::string& name);
        void LoadSource(std::string source);

        void Tokenize();
        void Analyze();

    private:
        std::string m_Source;
        std::vector<TokenMatchType> m_Types;
        std::vector<std::string> m_Values;

        ScopeNode m_Scopes;
    };
}