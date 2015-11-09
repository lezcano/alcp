#include <iosfwd>            // ostream
#include <string>            // to_string
#include <memory>           // unique_ptr

#include "exceptions.hpp"
#include "fqelem.hpp"
// types.hpp defined in fpelem.hpp
#include "fq.hpp"
#include "generalPurpose.hpp" // ExtendedEuclideanAlgorithm (eea)

Fqelem::Fqelem ( const Fqelem & other){
    _num = other._num;
    _f = std::unique_ptr<Fqelem::F>(new Fqelem::F(*other._f));
}

Fqelem & Fqelem::operator=(const Fqelem &rhs){
    if(&rhs != this){
        checkInSameField(rhs);
        _num = rhs._num;
    }
    return *this;
}

Fqelem & Fqelem::operator=(ll rhs){
    *this = _f->get(rhs);
    return *this;
}

bool Fqelem::operator==(const Fqelem &rhs)const{
    return (_num == rhs._num && *_f == *(rhs._f));
}

bool Fqelem::operator!=(const Fqelem &rhs)const{
    return !(*this == rhs);
}

Fqelem & Fqelem::operator+=(const Fqelem &rhs){
    checkInSameField(rhs);
    _num = (_num + rhs._num) % _mod;
    return *this;
}

const Fqelem Fqelem::operator+(const Fqelem &rhs) const{
    // We do not check if they are in the same field since
    // that will be done in the += operator
    return Fqelem(*this) += rhs;
}

const Fqelem Fqelem::operator-() const{
    return -_num;
}

Fqelem & Fqelem::operator-=(const Fqelem &rhs){
    // We do not check if they are in the same field since
    // that will be done in the += operator
    return (*this +=(-rhs));
}

const Fqelem Fqelem::operator-(const Fqelem &rhs) const{
    return Fqelem(*this) -= rhs;
}

Fqelem & Fqelem::operator*=(const Fqelem &rhs){
    checkInSameField(rhs);
    _num = (_num * rhs._num) % _mod;
    return *this;
}

const Fqelem Fqelem::operator*(const Fqelem &rhs) const{
    // We do not check if they are in the same field since
    // that will be done in the *= operator
    return Fqelem(*this) *= rhs;
}

/** Multiplicative inverse */
const Fqelem Fqelem::inv() const{
    if(_num == 0)
        throw EOperationUnsupported("Error. Zero has no inverse.");
    Fpxelem res = Fpxelem(_f->get(0)), aux = Fpxelem(_f->get(0));
    eea(_num, _mod, res, aux);
    return _f->get(res);
}

Fqelem & Fqelem::operator/=(const Fqelem &rhs){
    // We do not check if they are in the same field since
    // that will be done in the *= operator

    return *this *= rhs.inv();
}

const Fqelem Fqelem::operator/(const Fqelem &rhs) const{
    // We do not check if they are in the same field since
    // that will be done in the /= operator
    return Fqelem(*this) /= rhs;
}

int deg(const Fqelem &e){return e._num;}

// In a field the division has reminder zero
const Fqelem Fqelem::operator%(const Fqelem &rhs) const{return _f->get(0);}

ll Fqelem::getSize()const{return _f->getSize();}

const Fqelem::F Fqelem::getField()const{return *_f;}

std::string to_string(const Fqelem &e){return e._num.to_string();}
const Fqelem getZero(const Fqelem &e){return e.getField().get(0);}
const Fqelem getOne(const Fqelem &e){return e.getField().get(1);}

bool compatible(const Fqelem &lhs, const Fqelem &rhs){
    return lhs.getField()==rhs.getField();
}

Fqelem::Fqelem(Fpxelem num, Fpxelem mod,  std::unique_ptr<Fqelem::F> f): _num(num), _mod(mod){
    _f = std::move(f);
}

void Fqelem::checkInSameField(const Fqelem &rhs) const{
    if(this->getField() != rhs.getField())
        throw EOperationUnsupported(
            "Error. Is not possible to add the number " + std::to_string(_num) +
            " in " + to_string(this->getField()) +
            " with the number " + std::to_string(rhs._num) +
            " in F" + to_string(rhs.getField()));
}

Fqelem & operator+=(Fqelem &lhs, ll rhs){
    lhs+=lhs.getField().get(rhs);
    return lhs;
}

const Fqelem operator+(const Fqelem &lhs, ll rhs){
    return lhs + lhs.getField().get(rhs);
}

const Fqelem operator+(ll lhs, const Fqelem & rhs){
    return rhs.getField().get(lhs) + rhs;
}

Fqelem & operator-=(Fqelem &lhs, ll rhs){
    lhs-=lhs.getField().get(rhs);
    return lhs;
}

const Fqelem operator-(const Fqelem &lhs, ll rhs){
    return lhs - lhs.getField().get(rhs);
}

const Fqelem operator-(ll lhs, const Fqelem & rhs){
    return rhs.getField().get(lhs) - rhs;
}

bool operator==(const Fqelem & lhs, ll rhs){
    return lhs == lhs.getField().get(rhs);
}

bool operator==(ll lhs, const Fqelem &rhs){
    return rhs == lhs;
}

bool operator!=(const Fqelem & lhs, ll rhs){
    return !(lhs == rhs);
}

bool operator!=(ll lhs, const Fqelem &rhs){
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Fqelem &e){
    os << to_string(e);
    return os;
}