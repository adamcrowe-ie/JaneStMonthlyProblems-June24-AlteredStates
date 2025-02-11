#include "polynomial.h"

#include <math.h>

void Polynomial::remove_zeroes(){
    std::vector<PolynomialTerm> new_terms;

    for(const PolynomialTerm& term : terms){
        if(term.coefficient != 0)
            new_terms.push_back(term);
    }

    terms = std::move(new_terms);
}

void Polynomial::add_term(PolynomialTerm rhs){
    for(PolynomialTerm& lhs : terms){
        if(lhs != rhs) continue;

        lhs.coefficient += rhs.coefficient;
        return;
    }

    terms.push_back(rhs);
}

void Polynomial::multiply_term(PolynomialTerm rhs){
    for(PolynomialTerm& lhs : terms){
        lhs.coefficient *= rhs.coefficient;
        lhs.powA += rhs.powA;
        lhs.powB += rhs.powB;
        lhs.powC += rhs.powC;
    }
}

int Polynomial::evaluate(Tuple tuple){
    int result = 0;

    for(const auto& [coefficient, powA, powB, powC] : terms)
        result += coefficient * std::pow(tuple.A, powA) * std::pow(tuple.B, powB) * std::pow(tuple.C, powC);

    return result;
}