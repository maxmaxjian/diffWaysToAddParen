#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <stack>

int evalExpr(const std::string & s) {
    std::stack<std::string> st;
    size_t curr = 0;
    while (curr != std::string::npos && curr < s.size()) {
        if (s[curr] == ' ')
            curr++;
        else {
            if (s.find_first_of("(+-*", curr) == curr) {
                st.push(s.substr(curr,1));
                curr++;
            }
            else if (s.find_first_of("0123456789", curr) == curr){
                size_t end = s.find_first_not_of("0123456789", curr);
                st.push(s.substr(curr,end-curr));
                curr = end;
            }
            else {
                int op2 = std::stoi(st.top());
                st.pop();
                std::string operand = st.top();
                st.pop();
                int op1 = std::stoi(st.top());
                st.pop();
                st.pop();
                int rs;
                if (!operand.compare("+"))
                    rs = op1+op2;
                else if (!operand.compare("-"))
                    rs = op1-op2;
                else
                    rs = op1*op2;
                st.push(std::to_string(rs));
                curr++;
            }
        }
    }
    return std::stoi(st.top());
}

// namespace {
//     std::ostream & operator<<(std::ostream & os, const std::string & s) {
//         os << s << " = " << evalExpr(s);
//         return os;
//     }
// }

// std::ostream & myPrint(std::ostream & os, const std::string & s) {
//     os << s << " = " << evalExpr(s);
//     return os;
// }

class solution {
  public:
    std::vector<std::string> diffWaysToAddParen(const std::string & input) {
    	std::vector<std::string> result;
        if (input.find_first_of("+-*") == std::string::npos) {
            result.push_back(input);
        }
    	else {
            size_t found = input.find_first_of("+-*");
            while (found != std::string::npos) {
                auto first = diffWaysToAddParen(input.substr(0,found));
                auto second = diffWaysToAddParen(input.substr(found+1));
                for (auto& op1 : first) {
                    std::string temp{"("};
                    temp += op1;
                    temp += input[found];
                    for (auto & op2 : second) {
                        auto tmp = temp;
                        tmp += op2;
                        tmp += ")";
                        result.push_back(tmp);
                    }
                }
                found = input.find_first_of("+-*", found+1);
            }
    	}
        return result;
    }

    std::vector<int> diffWaysToEval(const std::string & input) {
        std::vector<std::string> diffExps = diffWaysToAddParen(input);
        std::vector<int> result;
        std::transform(diffExps.begin(), diffExps.end(), std::inserter(result, result.begin()),
                       [&](const std::string & s){
                           return evalExpr(s);
                       });
        return result;
    }
};

int main() {
    // std::string s{"2-1-1"};
    std::string s{"2*3-4*5"};

    solution soln;
    auto exprs = soln.diffWaysToAddParen(s);
    std::cout << "All possible expressions are:\n";
    std::for_each(exprs.begin(), exprs.end(), [&](const std::string &s){
        std::cout << s << " = " << evalExpr(s) << std::endl;
    });
    // auto results = soln.diffWaysToEval(s);
    // std::cout << "All possible results are:\n";
    // std::copy(results.begin(), results.end(), std::ostream_iterator<int>(std::cout, "\n"));
}
