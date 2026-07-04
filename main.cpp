#include <iostream>
#include <vector>
#include <cmath>

typedef struct {
    double R;
    double C;
} DqDtParams;

typedef struct {

};

// discharging a capacitor
double dqdt(double q, const DqDtParams& p) {
    return -1 * q / (p.R * p.C);
}

double dPdt(double p0, const )

template <typename DiffEqFunc>
std::vector<double> eulersMethod(double dt, const std::vector<double>& initCond, double t_f, DiffEqFunc f) {
    int numSteps = (int) ((t_f - initCond[0]) / dt);
    std::vector<double> solution;
    solution.push_back(initCond[1]);
    for (int t = 0; t < numSteps; t++) {
        solution.push_back(solution[t] + f(solution[t]) * dt);
    }
    return solution;
}

int main() {
    DqDtParams p1;

    p1.R = 3e2;
    p1.C = 4.5e-3;

    auto capacitorDqDt = [&p1](double q) {
        return dqdt(q, p1);
    };

    std::vector<double> i1;
    i1.push_back(0.0);
    i1.push_back(6.0e-6);
    double eTrue = i1[1] * exp(-1 * 5 / (p1.R * p1.C));
    std::vector<double> e1 = eulersMethod(1, i1, 5, capacitorDqDt);
    std::vector<double> e2 = eulersMethod(0.1, i1, 5, capacitorDqDt);
    std::vector<double> e3 = eulersMethod(0.01, i1, 5, capacitorDqDt);
    std::vector<double> e4 = eulersMethod(0.001, i1, 5, capacitorDqDt);


    std::cout << "Example - Discharging a capacitor: dq/dt = -q / RC" << std::endl;
    std::cout << "\n";
    std::cout << "Approximation at t = 5 with dt = 1: ";
    std::cout << e1.back() << "    Error: " << abs(e1.back() - eTrue) << std::endl;
    std::cout << "Approximation at t = 5 with dt = 0.1: ";
    std::cout << e2.back() << "    Error: " << abs(e2.back() - eTrue) << std::endl;
    std::cout << "Approximation at t = 5 with dt = 0.01: ";
    std::cout << e3.back() << "    Error: " << abs(e3.back() - eTrue) << std::endl;
    std::cout << "Approximation at t = 5 with dt = 0.001: ";
    std::cout << e4.back() << "    Error: " << abs(e4.back() - eTrue) << std::endl;
    std::cout << "\n";
    std::cout << "True value: " << eTrue;

    return 0;
}
