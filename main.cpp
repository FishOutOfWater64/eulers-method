#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <sstream>
#include <fstream>
#include <muParser.h>

static std::vector<double> eulersMethod(double dx, const std::vector<double>& initCond, double x_f, const std::function<double(double, double)>& f) {
    int numSteps = static_cast<int>((x_f - initCond[0]) / dx);
    std::vector<double> solution;
    solution.push_back(initCond[1]);
    for (int n = 0; n < numSteps; n++) {
        solution.push_back(solution[n] + f(n, solution[n]) * dx); // for f(n, solution[n]), n is abscissa, solution[n] is ordinate
    }
    return solution;
}

static std::vector<double> rkFour(double dx, const std::vector<double>& initCond, double x_f, const std::function<double(double, double)>& f) {
    int numSteps = static_cast<int>((x_f - initCond[0]) / dx); // divide into finite number of steps
    std::vector<double> solution;
    solution.push_back(initCond[1]);
    for (int n = 0; n < numSteps; n++) {
        double k1 = f(n, solution[n]);
        double k2 = f(n + dx / 2, solution[n] + k1 * dx / 2);
        double k3 = f(n + dx / 2, solution[n] + k2 * dx / 2);
        double k4 = f(n + dx, solution[n] + k3 * dx);
        solution.push_back(solution[n] + (dx / 6) * (k1 + 2*k2 + 2*k3 + k4));
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
        std::getline(std::cin, dydx);
        std::cout << '\n';

        p.SetExpr(dydx); // Setting the parser's expression to the user's input

        std::vector<double> initCond;
        std::string input;

        std::cout << "Enter the initial condition in the form y( x_0 ) = y_0: " << std::endl;
        std::getline(std::cin, input);
        std::stringstream s(input);
        std::string temp;
        double initVar;

        while (s >> temp) { // extracts each token
            std::stringstream extractor(temp);
            if (extractor >> initVar) {
                initCond.push_back(initVar);
            }
        }

        std::cout << '\n';

        std::cout << "Enter the step size you would like the function to be evaluated with: " << std::endl;
        std::getline(std::cin, input);
        double dx;
        std::stringstream(input) >> dx;
        std::cout << '\n'; // step size

        std::cout << "Enter the value you would like the function to be evaluated for: " << std::endl;
        std::getline(std::cin, input);
        double x_f;
        std::stringstream(input) >> x_f;
        std::cout << '\n'; // x value to approximate the function at

        auto userDerivative = [&](double xCurrent, double yCurrent) -> long double {
            x = xCurrent; // Update x value that the parser reads through each iteration
            y = yCurrent; // Same for y
            return p.Eval(); // Evaluate the expression entered by the user
        };

        std::vector<double> e1 = eulersMethod(dx, initCond, x_f, userDerivative);
        std::vector<double> rk1 = rkFour(dx, initCond, x_f, userDerivative);

        std::cout << "Approximation with Euler's Method: ";
        std::cout << "y(" << x_f << ") = " << e1.back() << std::endl;
        std::cout << "Approximation with Runge-Kutta 4th-order: ";
        std::cout << "y(" << x_f << ") = " << rk1.back() << std::endl;
    }

    catch (mu::Parser::exception_type &e){
        std::cout << e.GetMsg() << std::endl;
    }

    return 0;
}