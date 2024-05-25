
#ifndef FIXED_HPP
# define FIXED_HPP

#define FIX_SHIFT   8

struct fixed
{
    int num;
    
    fixed();
    fixed(int d);
    fixed(float f);

	operator	float() const; 
    operator    int() const;
    
    fixed   operator-() const;

    fixed operator+(fixed other) const;
    fixed operator-(fixed other) const;
    fixed operator*(fixed other) const;
    fixed operator/(fixed other) const;
	
	bool operator<(fixed other) const;
    bool operator>(fixed other) const;
    bool operator<=(fixed other) const;
    bool operator>=(fixed other) const;
	bool operator==(fixed other) const;
    bool operator!=(fixed other) const;

	fixed &operator+=(fixed other);
    fixed &operator-=(fixed other);
    fixed &operator*=(fixed other);
    fixed &operator/=(fixed other);

    static fixed    sqrt(fixed other);
    static fixed    from(int other);
};

#endif
