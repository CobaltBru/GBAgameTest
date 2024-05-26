
#ifndef UTIL_HPP
# define UTIL_HPP

template <typename T>
void	swap(T &a, T& b) {
	T tmp = a;

	a = b;
	b = tmp;
}

#endif
