#pragma once

#include <iostream>
#include <tuple>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <assert.h>

#define DESC true
#define ASC false

class Polynomial
{
private:
	struct Monomial
	{
		double coeff;
		int degree;
		Monomial *next, *prev;

		// Monomial constructor
		Monomial(double _coeff_, int _degree_) : degree(_degree_), coeff(_coeff_), next(nullptr), prev(nullptr) {}
		Monomial(std::tuple<double, int> mono) : next(nullptr), prev(nullptr)
		{
			this->coeff = std::get<0>(mono);
			this->degree = std::get<1>(mono);
		}
		Monomial(std::string mono) : next(nullptr), prev(nullptr)
		{
			auto tup = define(mono);
			this->coeff = std::get<0>(tup);
			this->degree = std::get<1>(tup);
		}
		std::tuple<double, int> define(std::string input)
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
	};

	Monomial *head, *tail;
	int _degree;

	void delete_monomial(Monomial *mono)
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

public:
	// Constructors
	Polynomial() : _degree(0), tail(nullptr), head(nullptr) {}
	Polynomial(std::string expr)
	{
		this->define(expr);
	}

	// Methods
	void define(std::string expr)
	{
		this->nullify();
		expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end());
		for (int i = 0; i < expr.length(); i++)
		{
			if (expr[i] == '-' && expr[i - 1] != '^')
			{
				expr.insert(i, "+");
				i++;
			}
		}

		std::string delim{"+"};
		size_t pos = 0;
		std::string token;
		while ((pos = expr.find(delim)) != std::string::npos)
		{
			token = expr.substr(0, pos);
			this->insert(token);
			expr.erase(0, pos + 1);
		}
		this->insert(expr);
	}
	void insert(std::string mono)
	{
		auto subj = new Monomial(mono);
		assert(subj->degree >= 0);
		if (subj->coeff == 0)
			return;

		if (this->head == nullptr)
		{
			this->head = this->tail = subj;
			this->_degree = subj->degree;
			return;
		}

		Monomial *curr = head;
		while (curr)
		{
			if (curr->degree == subj->degree)
			{
				if (curr->coeff == (-1) * subj->coeff)
				{
					delete_monomial(curr);
					return;
				}
				curr->coeff += subj->coeff;
				return;
			}

			if (curr->degree > subj->degree && !curr->prev)
			{
				subj->next = curr;
				this->head = curr->prev = subj;
				return;
			}

			if (curr->degree < subj->degree)
			{
				if (!curr->next)
				{
					subj->prev = curr;
					this->tail = curr->next = subj;
					this->_degree = subj->degree;
					return;
				}
				if (curr->next->degree > subj->degree)
				{
					subj->next = curr->next;
					subj->prev = curr;
					curr->next->prev = subj;
					curr->next = subj;
					return;
				}
			}

			curr = curr->next;
		}
	}
	void insert(Monomial *mono)
	{
		if (mono->coeff == 0)
			return;

		assert(mono->degree >= 0);
		if (this->head == nullptr)
		{
			this->head = this->tail = mono;
			this->_degree = mono->degree;
			return;
		}

		Monomial *curr = head;
		while (curr)
		{
			if (curr->degree == mono->degree)
			{
				if (curr->coeff == (-1) * mono->coeff)
				{
					delete_monomial(curr);
					return;
				}
				curr->coeff += mono->coeff;
				return;
			}

			if (curr->degree > mono->degree && !curr->prev)
			{
				mono->next = curr;
				this->head = curr->prev = mono;
				return;
			}

			if (curr->degree < mono->degree)
			{
				if (!curr->next)
				{
					mono->prev = curr;
					this->tail = curr->next = mono;
					this->_degree = mono->degree;
					return;
				}
				if (curr->next->degree > mono->degree)
				{
					mono->next = curr->next;
					mono->prev = curr;
					curr->next->prev = mono;
					curr->next = mono;
					return;
				}
			}

			curr = curr->next;
		}
	}
	void nullify()
	{
		while (this->head)
			delete_monomial(this->head);
	}
	int degree()
	{
		return this->_degree;
	}
	double eval(double x)
	{
		double res{0};
		auto curr = this->head;
		while (curr)
		{
			res += (curr->coeff * std::pow(x, curr->degree));
			curr = curr->next;
		}
		return res;
	}
	std::string to_string(bool desc = true)
	{
		std::ostringstream out;
		if (!this->head)
		{
			out << 0;
			return out.str();
		}
		auto curr = (desc ? this->tail : this->head);
		bool first = true;
		while (curr)
		{
			if (curr->coeff != 0)
			{
				// Sign
				auto sign = (curr->coeff < 0 ? '-' : '+');
				if (first && sign == '-')
					out << sign;
				else if (!first)
					out << ' ' << sign << ' ';

				// Coeff
				auto abs = std::abs(curr->coeff);
				if (abs != 1 || curr->degree == 0)
					out << abs;
				// x
				if (curr->degree != 0)
				{
					out << 'x';
					if (curr->degree != 1)
					{
						out << '^';
						out << curr->degree;
					}
				}
				first = false;
			}
			curr = (desc ? curr->prev : curr->next);
		}
		return out.str();
	}
	std::vector<double> to_vector()
	{
		int n = this->degree() + 1;
		std::vector<double> vect;
		auto curr = this->head;
		for (int i = 0; i < n; i++)
		{
			if (curr->degree == i)
			{
				vect.push_back(curr->coeff);
				curr = curr->next;
			}
			else
				vect.push_back(0.0);
		}
		return vect;
	}
	void set_coeff(unsigned int order, double x)
	{
		auto curr = this->head;
		while (curr)
		{
			if (curr->degree == order)
				curr->coeff = x;
			curr = curr->next;
		}
	}

	// Operators

	// Addition of two polynomials
	Polynomial
	operator+(Polynomial const &poly)
	{
		Polynomial res;
		auto curr = poly.head;
		while (curr)
		{
			auto mono = new Monomial(curr->coeff, curr->degree);
			res.insert(mono);
			curr = curr->next;
		}
		curr = this->head;
		while (curr)
		{
			auto mono = new Monomial(curr->coeff, curr->degree);
			res.insert(mono);
			curr = curr->next;
		}
		return res;
	}
	// Substraction of two polynomials
	Polynomial operator-(Polynomial const &poly)
	{
		Polynomial res;
		auto curr = poly.head;
		while (curr)
		{
			auto mono = new Monomial((-1) * curr->coeff, curr->degree);
			res.insert(mono);
			curr = curr->next;
		}
		curr = this->head;
		while (curr)
		{
			auto mono = new Monomial(curr->coeff, curr->degree);
			res.insert(mono);
			curr = curr->next;
		}
		return res;
	}
	// Multiplication of two polynomials
	Polynomial operator*(Polynomial const &poly)
	{
		Polynomial prod;
		auto left = this->head;
		while (left)
		{
			auto right = poly.head;
			while (right)
			{
				auto coeff = left->coeff * right->coeff;
				auto degree = left->degree + right->degree;
				auto mono = new Monomial(coeff, degree);
				prod.insert(mono);
				right = right->next;
			}

			left = left->next;
		}
		return prod;
	}
	// Division of two polynomials
	// Polynomial operator/(Polynomial const &poly)
	// {
	// 	auto ret = new Polynomial;
	// 	assert(poly._degree > 0);
	// 	if (this->_degree == 0)
	// 		return *ret;
	// }
	// Apply first derivation of the polynomial (poly--)
	Polynomial operator--(int)
	{
		auto curr = this->head;
		while (curr)
		{
			if (curr->degree == 0)
				delete_monomial(curr);
			else
			{
				curr->coeff *= curr->degree;
				curr->degree--;
			}
			curr = curr->next;
		}
	}
	// Apply first integration of the polynomial (poly++)
	Polynomial operator++(int)
	{
		auto curr = this->head;
		while (curr)
		{
			curr->degree++;
			curr->coeff /= curr->degree;
			curr = curr->next;
		}
	}
	// Multiplication with a scalar
	Polynomial operator*(double const &scalar)
	{
		auto scaled = new Polynomial(this->to_string());
		auto curr = scaled->head;
		while (curr)
		{
			curr->coeff *= scalar;
			curr = curr->next;
		}
		return *scaled;
	}
	// Polynomial comparison
	bool operator==(Polynomial const &poly)
	{
		auto q = this->head;
		auto p = poly.head;
		while (q && p)
		{
			if (q->coeff != p->coeff || q->degree != p->degree)
				return false;
			q = q->next;
			p = p->next;
		}

		return true;
	}
};
