#include <iostream>
#include <vector>
#include <functional>
#include <muParser.h>

static std::vector<double> eulersMethod(double dx, std::vector<double>& initCond, double x_f, const std::function<double(double, double)>& f) {
    int numSteps = static_cast<int>((x_f - initCond[0]) / dx);
    std::vector<double> solution;
    solution.push_back(initCond[1]);
    for (int x = 0; x < numSteps; x++) {
        solution.push_back(solution[x] + f(x, solution[x]) * dx); // for f(x, solution[x]), x is abscissa, solution[x] is ordinate
    }
    return solution;
}

int main() {
    try {
        double x;
        double y;

        mu::Parser p;
        p.DefineVar("x", &x);
        p.DefineVar("y", &y); // Adding variables to the parser

        // We receive user input below
        std::cout << "Enter an explicit first order ODE: " << std::endl;
        std::cout << "dy/dx =";
        std::string dydx;
        std::cin >> dydx;
        std::cout << '\n';

        p.SetExpr(dydx);

        std::vector<double> initCond;
        double input;

        std::cout << "Enter the input value of the initial condition: " << std::endl;
        std::cin >> input;
        initCond.push_back(input);
        std::cout << '\n';

        std::cout << "Enter the output value of the initial condition: " << std::endl;
        std::cin >> input;
        initCond.push_back(input);
        std::cout << '\n';

        std::cout << "Enter the step size you would like the function to be evaluated with: " << std::endl;
        std::cin >> input;
        double dx = input;
        std::cout << '\n';

        std::cout << "Enter the input value you would like the function to be evaluated at: " << std::endl;
        std::cin >> input;
        double x_f = input;
        std::cout << '\n';


        auto userDerivative = [&](double xCurrent, double yCurrent) -> double {
            x = xCurrent; // Update x value that the parser reads through each iteration
            y = yCurrent; // Same for y
            return p.Eval();
        };

        std::vector<double> e1 = eulersMethod(dx, initCond, x_f, userDerivative);

        std::cout << "y(" << x_f << ") = " << e1.back() << std::endl;
    }

    catch (mu::Parser::exception_type &e){
        std::cout << e.GetMsg() << std::endl;
    }

    return 0;
}
