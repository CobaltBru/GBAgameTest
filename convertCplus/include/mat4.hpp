
#ifndef MAT4_HPP
# define MAT4_HPP

# include "fixed.hpp"
# include "vec4.hpp"

/* 임시 타입 정의*/
typedef unsigned int	u32;


struct mat4 {
	fixed	element[16];

	mat4(); // zero-initialized
	mat4	operator+(mat4 const &other) const;
	mat4	operator-(mat4 const &other) const;
	mat4	operator*(fixed const &other) const;
	mat4	operator*(mat4 const &other) const;
	vec4	operator*(vec4 const &other) const;
	static mat4	identity();
	static mat4	transpose(mat4 const &matrix);
};///뭣ㅇㅇ??
// 이게 뭐에요
// 벡터 세개 받아서 행렬로 만들어주는 함수에오
// 그냥 초기화할 때 초기화자에 직접 넣는게 보기 좋을거같어요
// 생성자가 아니고 그냥 바로 element를 설정해버릴 수가 있어요
// 생성자로 만들어버릴까요???
//엑

#endif
