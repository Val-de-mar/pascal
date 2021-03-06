#include <iostream>
#include <Expression.h>

using Ex = Expression;

using ff = std::vector<std::unique_ptr<Expression>>;

int main() {
    using std::unique_ptr;
    VariableManager manager;
    auto A = new ValueExpression(getId<int>, std::make_shared<VariableT>(9));
    auto B = new ValueExpression(getId<int>, std::make_shared<VariableT>(13));

    auto ApB = new BinaryOperation("*", unique_ptr<Ex>(A), unique_ptr<Ex>(B));

    auto C = new AtomExpression("C");
    auto D = new AtomExpression("D");
    auto addAns = new AtomExpression("add");
    auto CpD = new BinaryOperation("+", unique_ptr<Ex>(C), unique_ptr<Ex>(D));
    auto Assign = new BinaryOperation(":=", unique_ptr<Ex>(addAns), unique_ptr<Ex>(CpD));
    auto func = new CustomFunction (
            "add",
            getId<int>,
            manager,
            std::unique_ptr<Expression>(Assign),
            {"C", "D"},
            {getId<int>, getId<int>},
            {"ANS"},
            {getId<int>}
            );
    manager.declareFunction("add", {{getId<int>, getId<int>}}, {
        {[f = std::shared_ptr<CustomFunction>(func)](std::vector<std::shared_ptr<VariableT>> values){
            return (*f)(values);
        }},
        getId<int>});
    auto vv = ff();
    vv.push_back(unique_ptr<Ex>(A));
    vv.push_back(unique_ptr<Ex>(B));

    auto Print = new FunctionExpression("add", std::move(vv));
    auto pp = Print->calculate(manager);
    std::cout << std::get<int>(*(manager.getVar(pp))) << std::endl;
    return 0;
}
