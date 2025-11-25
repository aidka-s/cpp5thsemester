#include "ExpressionEvaluator.h"
#include <cctype>
#include <stdexcept>
#include <cmath>        // ← std::pow
#include <string>
#include <vector>

namespace {
    class Parser {
    public:
        Parser(const std::string& s, const std::vector<IFunction*>& funcs)
            : str(s), pos(0), functions(funcs) {}

        double parse() {
            double result = parseExpression();
            skip();
            if (pos < str.size())
                throw std::runtime_error("Extra characters after expression");
            return result;
        }

    private:
        const std::string& str;
        size_t pos;
        const std::vector<IFunction*>& functions;

        void skip() {
            while (pos < str.size() && std::isspace(static_cast<unsigned char>(str[pos])))
                ++pos;
        }

        double number() {
            skip();
            if (pos >= str.size())
                throw std::runtime_error("Unexpected end of input");

            size_t start = pos;
            if (str[pos] == '.') ++pos;
            while (pos < str.size() && (std::isdigit(static_cast<unsigned char>(str[pos])) || str[pos] == '.'))
                ++pos;

            if (start == pos)
                throw std::runtime_error("Expected number");

            return std::stod(str.substr(start, pos - start));
        }

        std::string identifier() {
            skip();
            size_t start = pos;
            if (pos >= str.size() || !std::isalpha(static_cast<unsigned char>(str[pos])))
                throw std::runtime_error("Expected function name");

            while (pos < str.size() && std::isalnum(static_cast<unsigned char>(str[pos])))
                ++pos;

            return str.substr(start, pos - start);
        }

        IFunction* findFunction(const std::string& name) const {
            for (auto* f : functions)
                if (f->name() == name)
                    return f;
            return nullptr;
        }

        double parsePrimary() {
            skip();

            // Число
            if (pos < str.size() && (std::isdigit(static_cast<unsigned char>(str[pos])) || str[pos] == '.')) {
                return number();
            }

            // Скобки
            if (pos < str.size() && str[pos] == '(') {
                ++pos;
                double val = parseExpression();
                skip();
                if (pos >= str.size() || str[pos] != ')')
                    throw std::runtime_error("Expected ')'");
                ++pos;
                return val;
            }

            // Функция из плагина: sin(30), deg(...)
            std::string name = identifier();
            IFunction* func = findFunction(name);
            if (!func)
                throw std::runtime_error("Unknown function: " + name);

            skip();
            if (pos >= str.size() || str[pos] != '(')
                throw std::runtime_error("Expected '(' after function name");

            ++pos;
            double arg = parseExpression();
            skip();
            if (pos >= str.size() || str[pos] != ')')
                throw std::runtime_error("Expected ')' after function argument");

            ++pos;
            return func->execute(arg);
        }

        double parsePower() {
            double left = parsePrimary();
            skip();
            while (pos < str.size() && str[pos] == '^') {
                ++pos;
                double right = parsePower();  // Right-associative
                left = std::pow(left, right);
            }
            return left;
        }

        double parseTerm() {
            double val = parsePower();
            while (true) {
                skip();
                if (pos >= str.size()) break;
                char op = str[pos];
                if (op != '*' && op != '/') break;
                ++pos;
                double rhs = parsePower();
                if (op == '*') val *= rhs;
                else {
                    if (rhs == 0.0)
                        throw std::runtime_error("Division by zero");
                    val /= rhs;
                }
            }
            return val;
        }

        double parseExpression() {
            double val = parseTerm();
            while (true) {
                skip();
                if (pos >= str.size()) break;
                char op = str[pos];
                if (op != '+' && op != '-') break;
                ++pos;
                double rhs = parseTerm();
                if (op == '+') val += rhs;
                else val -= rhs;
            }
            return val;
        }
    };
}

// Конструктор
ExpressionEvaluator::ExpressionEvaluator(const std::vector<IFunction*>& funcs)
    : functions(funcs) {}

// Основной метод
double ExpressionEvaluator::evaluate(const std::string& expression) const {
    if (expression.empty())
        throw std::runtime_error("Empty expression");

    Parser parser(expression, functions);
    return parser.parse();
}