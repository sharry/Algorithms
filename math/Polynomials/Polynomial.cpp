#include "Polynomial.h"

std::tuple<double, int> Monomial::define(std::string input)
{
    std::remove(input.begin(), input.end(), ' ');
    double c;
    int d;
    if (input.find("x") != std::string::npos)
    {
        std::string delim = "x";
        if (input.length() - input.find(delim) > 1 && input.at(input.find(delim) + 1) == '^')
            delim = "x^";
        size_t start = 0;
        std::ostringstream coeff;
        std::ostringstream degree;
        size_t end = input.find(delim);
        while (end != -1)
        {
            coeff << input.substr(start, end - start);
            start = end + delim.size();
            end = input.find(delim, start);
            degree << input.substr(start, end - start);
        }
        try
        {
            c = std::stod(coeff.str());
        }
        catch (const std::exception &)
        {
            if (coeff.str()[0] == '-' && coeff.str().length() == 1)
                c = -1;
            else
                c = 1;
        }
        try
        {
            d = std::stoi(degree.str());
        }
        catch (const std::exception &)
        {
            d = 1;
        }
    }
    else
    {
        d = 0;
        try
        {
            c = std::stod(input);
        }
        catch (const std::exception &e)
        {
            c = 0.0;
        }
    }
    return std::make_tuple(c, d);
}
void Polynomial::delete_monomial(Monomial *mono)
{
    if (!mono->prev)
    {
        if (!mono->next)
        {
            this->head = this->tail = nullptr;
            this->_degree = 0;
        }
        else
        {
            this->head = mono->next;
            mono->next->prev = nullptr;
        }
        delete mono;
    }
    else if (!mono->next)
    {
        this->_degree = mono->prev->degree;
        this->tail = mono->prev;
        mono->prev->next = nullptr;
        delete mono;
    }
    else
    {
        mono->prev->next = mono->next;
        mono->next->prev = mono->prev;
        delete mono;
    }
}