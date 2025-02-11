#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>

struct PolynomialTerm{
    int coefficient;
    int powA;
    int powB;
    int powC;

    inline bool operator!= (const PolynomialTerm& rhs){
        return (powA != rhs.powA) || (powB != rhs.powB) || (powC != rhs.powC);
    }
};


struct Tuple{
    int A;
    int B;
    int C;
};


class Polynomial{
    private:
        std::vector<PolynomialTerm> terms;
    
    public:
        Polynomial(){ terms.push_back({0, 0, 0, 0}); }

        Polynomial(int coefficient, int powA, int powB, int powC){
            terms.push_back({coefficient, powA, powB, powC});
        }

        void add_term(PolynomialTerm rhs);
        void multiply_term(PolynomialTerm rhs);
        
        void remove_zeroes();
        int evaluate(Tuple tuple);
};

#endif