#include "ExpressionEvaluator.h"
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>


namespace {
    class Parser {
    public:
        explicit Parser(const std::string& s) : str(s), pos(0) {}

        double parse() { return parseExpression(); }

    private:
        std::string str;
        size_t pos;

        void skip() {
            while (pos < str.size() && isspace(str[pos])) ++pos;
        }

        double number() {
            skip();
            double val = 0;
            bool dot = false;
            double frac = 0.1;
            if (pos >= str.size()) throw std::runtime_error("unexpected end");

            if (!isdigit(str[pos]) && str[pos] != '.')
                throw std::runtime_error("expected number");

            while (pos < str.size() && (isdigit(str[pos]) || str[pos] == '.')) {
                if (str[pos] == '.') { dot = true; ++pos; continue; }
                int d = str[pos++] - '0';
                if (dot) { val += d * frac; frac /= 10; }
                else val = val * 10 + d;
            }
            return val;
        }

        double factor() {
            skip();
            if (pos < str.size() && str[pos] == '(') {
                ++pos;
                double val = parseExpression();
                skip();
                if (pos >= str.size() || str[pos] != ')')
                    throw std::runtime_error("missing )");
                ++pos;
                return val;
            }
            return number();
        }

        double term() {
            double val = factor();
            while (true) {
                skip();
                if (pos < str.size() && (str[pos] == '*' || str[pos] == '/')) {
                    char op = str[pos++];
                    double rhs = factor();
                    val = (op == '*') ? val * rhs : val / rhs;
                } else break;
            }
            return val;
        }

        double parseExpression() {
            double val = term();
            while (true) {
                skip();
                if (pos < str.size() && (str[pos] == '+' || str[pos] == '-')) {
                    char op = str[pos++];
                    double rhs = term();
                    val = (op == '+') ? val + rhs : val - rhs;
                } else break;
            }
            return val;
        }
    };
}

double ExpressionEvaluator::evaluate(const std::string& expression) {
    Parser parser(expression);
    return parser.parse();
}