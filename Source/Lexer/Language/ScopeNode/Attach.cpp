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

int Lexer::Language::ScopeNode::Attach(ScopeType type) {
    m_Children.push_back(ScopeNode(type, this));
    return m_Children.size() - 1;
}

void Lexer::Language::ScopeNode::Attach(Lexer::Language::LangMatchType type, std::string value) {
    m_Types.push_back(type);
    m_Values.push_back(value);
}