
#ifndef FIXED_HPP
# define FIXED_HPP

#define FIX_SHIFT   8

struct fixed
{
    int num;
    
    fixed();
    fixed(int d);
    fixed(float f);

	explicit operator	float() const; 
    explicit operator    int() const;
    
    fixed   operator-() const;

    fixed operator+(fixed other) const;
    fixed operator-(fixed other) const;
    fixed operator*(fixed other) const;
    fixed operator/(fixed other) const;

    fixed operator>>(int shift) const;
    fixed operator<<(int shift) const;

    template <typename T>
    bool    operator<(T other) const {
        return (this->num < (int(other) << FIX_SHIFT));
    }
	template <typename T>
    bool    operator>(T other) const {
        return (this->num > (int(other) << FIX_SHIFT));
    }
    template <typename T>
    bool    operator<=(T other) const {
        return (this->num <= (int(other) << FIX_SHIFT));
    }
    template <typename T>
    bool    operator>=(T other) const {
        return (this->num >= (int(other) << FIX_SHIFT));
    }
    template <typename T>
    bool    operator==(T other) const {
        return (this->num == (int(other) << FIX_SHIFT));
    }
    template <typename T>
    bool    operator!=(T other) const {
        return (this->num != (int(other) << FIX_SHIFT));
    }

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
    fixed &operator>>=(int shift);
    fixed &operator<<=(int shift);

    static fixed    from(int other);
};

#endif
