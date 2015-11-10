#ifndef __FIELDP_HPP
#define __FIELDP_HPP

#include "fp.hpp"
#include "types.hpp"
#include "polRing.hpp"

#include <iosfwd>           // ostream
#include <memory>           // unique_ptr
#include <vector>

class Fpelem;

////////////////////////////// Fp //////////////////////////////
class Fp{
    public:
        Fp(ll p);

        Fpelem get(ll n)const;

        ll getSize()const;

        std::vector<Fpelem> getElems()const;

        bool operator==(const Fp &rhs)const;
        bool operator!=(const Fp &rhs)const;


    private:
        ll _p;
};



////////////////////////////// Fpelem //////////////////////////////
class Fpelem{
    public:
        // Base field
        using F = Fp;

        Fpelem ( const Fpelem & );
        Fpelem & operator=(const Fpelem &rhs);

        Fpelem & operator=(ll rhs);

        bool operator==(const Fpelem &rhs)const;

        bool operator!=(const Fpelem &rhs)const;

        Fpelem & operator+=(const Fpelem &rhs);

        const Fpelem operator+(const Fpelem &rhs) const;

        const Fpelem operator-() const;

        Fpelem & operator-=(const Fpelem &rhs);

        const Fpelem operator-(const Fpelem &rhs) const;

        Fpelem & operator*=(const Fpelem &rhs);

        const Fpelem operator*(const Fpelem &rhs) const;

        /** Multiplicative inverse */
        const Fpelem inv() const;

        Fpelem & operator/=(const Fpelem &rhs);

        const Fpelem operator/(const Fpelem &rhs) const;

        friend int deg(const Fpelem &e);

        const Fpelem operator%(const Fpelem &rhs) const;

        ll getSize()const;

        const F getField()const;

        friend std::ostream& operator<<(std::ostream& os, const Fpelem &e);
        friend std::string to_string(const Fpelem &e);

    private:
        friend class Fp;

        Fpelem(ll num, std::unique_ptr<F> f);
        void checkInSameField(const Fpelem &rhs) const;

        ll _num;
        std::unique_ptr<F> _f;
};

bool operator==(ll lhs, const Fpelem &rhs);
bool operator==(const Fpelem &lhs, ll rhs);
bool operator!=(ll lhs, const Fpelem &rhs);
bool operator!=(const Fpelem &lhs, ll rhs);
Fpelem & operator+=(Fpelem &lhs, ll rhs);
const Fpelem operator+(const Fpelem &lhs, ll rhs);
const Fpelem operator+(ll lhs, const Fpelem & rhs);
Fpelem & operator-=(Fpelem &lhs, ll rhs);
const Fpelem operator-(const Fpelem &lhs, ll rhs);
const Fpelem operator-(ll lhs, const Fpelem & rhs);

bool compatible(const Fpelem &lhs, const Fpelem &rhs);
const Fpelem getZero(const Fpelem &e);
const Fpelem getOne(const Fpelem &e);
std::string to_string(const Fpelem &e);



////////////////////////////// Fpxelem //////////////////////////////

class Fpxelem : public PolinomialRing<Fpxelem, Fpelem>{
    public:
        // Base field
        using F = Fp;
        using Felem = Fpelem;

        Fpxelem(const Fpelem & e);
        Fpxelem(const std::vector<Fpelem> & v);

        bool irreducible()const;
        const F getField()const;
        ll getSize()const;
};

Fpxelem getZero(const Fpxelem &e);
Fpxelem getOne(const Fpxelem &e);
const Fpelem unit(const Fpxelem &e);
bool compatible(const Fpxelem &lhs, const Fpxelem &rhs);
bool operator==(const Fpxelem &lhs, ll rhs);
bool operator==(ll lhs, const Fpxelem &rhs);
bool operator!=(const Fpxelem &lhs, ll rhs);
bool operator!=(ll lhs, const Fpxelem &rhs );


#endif // __FP_HPP