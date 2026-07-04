#include <iostream>
#include <vector>
#include <cmath>

typedef struct {
    double R;
    double C;
} DqDtParams;

typedef struct {
    double r;
    double K;
} DPDtParams;

// discharging a capacitor
double dqdt(double q, const DqDtParams& p) {
    return -1 * q / (p.R * p.C);
}

double dPdt(double P, const DPDtParams& p) {
    return p.r * P * (1 - P / p.K);
}

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

    DPDtParams p2;
    p2.r = 0.5;
    p2.K = 30000;

    auto capacitorDqDt = [&p1](double q) {
        return dqdt(q, p1);
    };

    auto populationDPDt = [&p2](double P) {
        return dPdt(P, p2);
    };

    std::vector<double> i1;
    i1.push_back(0.0);
    i1.push_back(6.0e-6);
    double eTrue = i1[1] * exp(-1 * 5 / (p1.R * p1.C));
    std::vector<double> e1 = eulersMethod(1, i1, 5, capacitorDqDt);
    std::vector<double> e2 = eulersMethod(0.1, i1, 5, capacitorDqDt);
    std::vector<double> e3 = eulersMethod(0.01, i1, 5, capacitorDqDt);
    std::vector<double> e4 = eulersMethod(0.001, i1, 5, capacitorDqDt);

    std::vector<double> i2;
    i2.push_back(0.0);
    i2.push_back(35000);
    double pTrue = i2[1] * p2.K * exp(p2.r * 4) / ((p2.K - i2[1])+ i2[1] * exp(p2.r * 4));
    std::vector<double> e5 = eulersMethod(1, i2, 4, populationDPDt);
    std::vector<double> e6 = eulersMethod(0.1, i2, 4, populationDPDt);
    std::vector<double> e7 = eulersMethod(0.01, i2, 4, populationDPDt);
    std::vector<double> e8 = eulersMethod(0.001, i2, 4, populationDPDt);

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
    std::cout << "True value: " << eTrue << std::endl;

    std::cout << "\n";

    std::cout << "Example - Salmon population of a lake: dP/dt = rP(1-P/K)" << std::endl;
    std::cout << "\n";
    std::cout << "Approximation at t = 4 with dt = 1: ";
    std::cout << e5.back() << "    Error: " << abs(e5.back() - pTrue) << std::endl;
    std::cout << "Approximation at t = 4 with dt = 0.1: ";
    std::cout << e6.back() << "    Error: " << abs(e6.back() - pTrue) << std::endl;
    std::cout << "Approximation at t = 4 with dt = 0.01: ";
    std::cout << e7.back() << "    Error: " << abs(e7.back() - pTrue) << std::endl;
    std::cout << "Approximation at t = 4 with dt = 0.001: ";
    std::cout << e8.back() << "    Error: " << abs(e8.back() - pTrue) << std::endl;
    std::cout << "\n";
    std::cout << "True value: " << pTrue;

    return 0;
}
