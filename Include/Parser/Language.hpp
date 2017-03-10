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

namespace Parser {
    class Language {
    public:
        // enum class Operator {
        //     Assignment,

        //     // Comparison
        //     CompareEquality,
        //     CompareInequality,
        //     CompareLess,
        //     CompareGreater,
        //     CompareLessEquality,
        //     CompareGreaterEquality

        //     // Arithmetic
        //     Add,
        //     Subtract,
        //     Multiply,
        //     Divide,
        //     Modulo,

        //     // Assign-Arithmetic
        //     AddAssignment,
        //     SubtractAssignment,
        //     MultiplyAssignment,

        // }

        class ASTNode {
        public:
            virtual ~ASTNode();
        };

        class NumberASTNode {
        public:
            NumberASTNode(int value);
            NumberASTNode(float value);
            NumberASTNode(double value);
        private:
            double m_ValDouble;
            float m_ValFloat;
            int m_ValInt;
        };

        class VariableASTNode {
        public:
            VariableASTNode(const std::string& name);

        private:
            std::string m_Name;
        };

        class VariableDeclASTNode {
        public:
            VariableDeclASTNode(const std::string& name, const std::string& type);

        private:
            std::string m_Name;
            std::string m_Type;
        };

        class UnaryASTNode {
        public:
            UnaryASTNode(const std::string& op, std::unique_ptr<ASTNode> expr);

        private:
            std::string m_Op;
            std::unique_ptr<ASTNode> m_Expr;
        };

        class BinaryASTNode {
        public:
            BinaryASTNode(const std::string& op, std::unique_ptr<ASTNode> exprL, std::unique_ptr<ASTNode> exprR);

        private:
            std::string m_Op;
            std::unique_ptr<ASTNode> m_ExprL;
            std::unique_ptr<ASTNode> m_ExprR;
        };

        class TernaryASTNode {
        public:
            TernaryASTNode(const std::string& op, std::unique_ptr<ASTNode> exprL, std::unique_ptr<ASTNode> exprC, std::unique_ptr<ASTNode> exprR);

        private:
            std::string m_Op;
            std::unique_ptr<ASTNode> m_ExprL;
            std::unique_ptr<ASTNode> m_ExprC;
            std::unique_ptr<ASTNode> m_ExprR;
        };

        class CallASTNode {
        public:
            CallASTNode(const std::string& callee, std::unique_ptr<ASTNode> expr);

        private:
            std::string m_Callee;
            std::unique_ptr<ASTNode> m_Expr;
        };

        class PrototypeASTNode {
        public:
            PrototypeASTNode(const std::string& name, std::vector<std::unique_ptr<VariableDeclASTNode>> arguments);

        private:
            std::string m_Name;
            std::vector<std::unique_ptr<VariableDeclASTNode>> m_Args;
        };

        class FunctionASTNode {
        public:
            FunctionASTNode(std::unique_ptr<PrototypeASTNode> prototype, std::unique_ptr<ExprAST> expr);

        private:
            std::unique_ptr<PrototypeASTNode> m_Prototype;
            std::unique_ptr<ASTNode> m_Body;
        };

        class StructureASTNode {
        public:
            StructureASTNode(const std::string& name, std::vector<std::unique_ptr<VariableDeclASTNode>> members);

        private:
            std::string m_Name;
            std::vector<std::unique_ptr<VariableDeclASTNode>> m_Members;
        };

        Language() {}
        ~Language() = default;

        void BuildAST();

    private:
    };
}