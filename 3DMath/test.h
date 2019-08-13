#include<iostream>
#include<algorithm>
#include<math.h>
#include<string.h>
using namespace std;

namespace MathTest {
static const int m11 = 0;
static const int m12 = 1;
static const int m13 = 2;
static const int m14 = 3;
static const int m21 = 4;
static const int m22 = 5;
static const int m23 = 6;
static const int m24 = 7;
static const int m31 = 8;
static const int m32 = 9;
static const int m33 = 10;
static const int m34 = 11;
static const int m41 = 12;
static const int m42 = 13;
static const int m43 = 14;
static const int m44 = 15;
static const float Pi = 3.1415926f;

// 定义2维向量
class Vector2
{
public:
	float x, y;
	Vector2( ) { }
	Vector2( float x_, float y_ )
		: x( x_ ), y( y_ ) { }

	float cross( const Vector2& v ){
		return this->x * v.y - v.x * this->y;
	}
};

// 定义3维向量
class Vector3
{
public:
	float x, y, z;
	Vector3( ) { }
	Vector3( float x_, float y_, float z_ )
		: x( x_ ), y( y_ ), z( z_ ) { }
	float dot( const Vector3& v){
		return this->x * v.x + this->y * v.y + this->z * v.z;
	}
};

// 输出2维向量
ostream& operator << ( ostream &out, const Vector2 &v )
{
	cout<<"Vector2:"<<(&v)<<"\tx:"<<v.x<<"\ty:"<<v.y<<endl;
	return out;
}

// 输出3维向量
ostream& operator << ( ostream &out, const Vector3 &v )
{
	cout<<"Vector3:"<<(&v)<<"\tx:"<<v.x<<"\ty:"<<v.y<<"\tz:"<<v.z<<endl;
	return out;
}


Vector2 operator-( const Vector2& v1, const Vector2& v2 ){
	Vector2 vec;
	vec.x = v1.x - v2.x;
	vec.y = v1.y - v2.y;
	return vec;
}

Vector3 operator*( const float t, const Vector3& v ){
	Vector3 vec;
	vec.x = t * v.x;
	vec.y = t * v.y;
	vec.z = t * v.z;
	return vec;
}

Vector3 operator+( const Vector3& v1, const Vector3& v2 ){
	Vector3 vec;
	vec.x = v1.x + v2.x;
	vec.y = v1.y + v2.y;
	vec.z = v1.z + v2.z;
	return vec;
}

// 判断线段与矩形的边是否重合，并且给cd赋值
bool coincidentAssign( const Vector2& a, const Vector2& b, const Vector2& p1, const Vector2& p2, Vector2& c, Vector2& d ){
	if ( p1.x == p2.x && a.x == b.x && p1.x == a.x ){
		Vector2 line_up = a.y > b.y ? a : b;
		Vector2 line_down = a.y < b.y ? a : b;
		//线段两端在矩形边内
		if ( line_up.y <= p1.y && p2.y <= line_down.y ){
			c = a;
			d = b;
		}
		//线段一端在矩形边
		else if ( p2.y <= line_up.y && line_up.y <= p1.y && line_down.y < p2.y ){
			c = line_down.y == a.y ? p2 : a;
			d = line_down.y == b.y ? p2 : b;
		}
		//线段一端在矩形边
		else if ( p2.y <= line_down.y && line_down.y <= p1.y && line_up.y > p1.y ){
			c = line_up.y == a.y ? p1 : a;
			d = line_up.y == b.y ? p1 : b;
		}
		//线段两端在矩形边外
		else {
			c = a.y == line_up.y ? p1 : p2;
			d = b.y == line_up.y ? p1 : p2;
		}
		return true;
	}
	if ( p1.y == p2.y && a.y == b.y && p1.y == a.y ){
		Vector2 line_right = a.x > b.x ? a : b;
		Vector2 line_left = a.x < b.x ? a : b;
		//线段两端在矩形边内
		if ( line_right.x <= p1.x && p2.x <= line_left.x ){
			c = a;
			d = b;
		}
		//线段一端在矩形边
		else if ( p2.x <= line_right.x && line_right.x <= p1.x && line_left.x < p2.x ){
			c = line_left.x == a.x ? p2 : a;
			d = line_left.x == b.x ? p2 : b;
		}
		//线段一端在矩形边
		else if ( p2.x <= line_left.x && line_left.x <= p1.x && line_right.x > p1.x ){
			c = line_right.x == a.x ? p1 : a;
			d = line_right.x == b.x ? p1 : b;
		}
		//线段两端在矩形边外
		else {
			c = a.x == line_right.x ? p1 : p2;
			d = b.x == line_right.x ? p1 : p2;
		}
		return true;
	}
	return false;
}
// 判断线段是否相交，p1p2是一个线段，p3p4是一个线段 
bool segmentIntersect( const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4 ){
	//快速互斥判断
	if (max( p1.x, p2.x ) < min( p3.x, p4.x ) || max( p3.x, p4.x ) < min( p1.x, p2.x ) || max( p1.y, p2.y ) < min( p3.y, p4.y ) || max( p3.y, p4.y ) < min( p1.y, p2.y ))
		return false;
	//跨立判断
	if ( ( p1 - p3 ).cross( p3 - p4 ) * ( p2 - p3 ).cross( p3 - p4 ) > 0 || ( p3 - p1 ).cross( p1 - p2 ) * ( p4 - p1 ).cross( p1 - p2 ) > 0)
		return false;
	return true;
}

//获取交点坐标
Vector2 getIntersection( const Vector2& p1, const Vector2& p2, const Vector2& q1, const Vector2& q2 ){
	Vector2 re;
	float tmpLeft,tmpRight;
    tmpLeft = ( q2.x - q1.x ) * ( p1.y - p2.y ) - ( p2.x - p1.x ) * ( q1.y - q2.y );
    tmpRight = ( p1.y - q1.y ) * ( p2.x - p1.x ) * ( q2.x - q1.x ) + q1.x * ( q2.y - q1.y ) * ( p2.x - p1.x ) - p1.x * ( p2.y - p1.y ) * ( q2.x - q1.x );

    re.x = tmpRight/tmpLeft;

    tmpLeft = ( p1.x - p2.x ) * ( q2.y - q1.y ) - ( p2.y - p1.y ) * ( q1.x - q2.x );
    tmpRight = p2.y * ( p1.x - p2.x ) * ( q2.y - q1.y ) + ( q2.x- p2.x ) * ( q2.y - q1.y ) * ( p1.y - p2.y ) - q2.y * ( q1.x - q2.x ) * ( p2.y - p1.y ); 
    re.y = tmpRight/tmpLeft;
	return re;
}

float square( float x ){
	return x * x;
}

float getDistance( const Vector2& p1, const Vector2& p2 ){
	return square( p1.x - p2.x ) + square( p1.y - p2.y );
}

//判断交点靠近a还是b,并给c,d赋值
void assign( const Vector2& a, const Vector2& b, const Vector2& intersect, Vector2& c, Vector2& d ){
	float temp1 = getDistance( a, intersect );
	float temp2 = getDistance( b, intersect );
	temp1 < temp2 ? c = intersect : d = intersect; 
}

// 定义轴对齐包围盒AABB模板类
template< class T >
class AABB
{
public:
	T _min;
	T _max;

	//AABB( ) { }
	AABB( T a, T b )
		: _min( a ), _max( b ) { }
	
	bool intersect( const T& a, const T& b, T* c = nullptr, T* d = nullptr ) const;

};

// TODO : 定义2维相交测试
// 返回值表示是否有交集，ab在内部返回true
// c,d不为空时，表示用户想要获取交点，其中：c是更靠近a的交点，d是更靠近b的交点
bool AABB< Vector2 >::intersect( const Vector2& a, const Vector2& b, Vector2* c, Vector2* d ) const
{
	bool re = false;
	Vector2 _min_up( _min.x, _max.y );
	Vector2 _max_down( _max.x, _min.y );
	Vector2 intersect;
	float temp_dis = 0;
	//判断线段是否在AABB内
	if ( min( a.x, b.x ) >= _min.x && max( a.x, b.x ) <= _max.x && min( a.y, b.y ) >= max( a.y, b.y ) <= _max.y )
		re = true;
	//判断线段与四条边是否相交，若相交求交点
	if ( segmentIntersect( a, b, _min, _min_up ) ){
		re = true;
		if(coincidentAssign( a, b, _min_up, _min, *c, *d ))
			return true;
		intersect = getIntersection( a, b, _min, _min_up );
		assign( a, b, intersect, *c, *d );
	}
	if (segmentIntersect( a, b, _min, _max_down ) ){
		re = true;
		if(coincidentAssign( a, b, _max_down, _min, *c, *d ) )
			return true;
		intersect = getIntersection( a, b, _min, _max_down );
		assign( a, b, intersect, *c, *d );
	}
	if ( segmentIntersect( a, b, _max, _max_down ) ){
		re = true;
		if (coincidentAssign( a, b, _max, _max_down, *c, *d ) )
			return true;
		intersect = getIntersection( a, b, _max, _max_down );
		assign( a, b, intersect, *c, *d );
	}
	if ( segmentIntersect( a, b, _max, _min_up ) ){
		re = true;
		if (coincidentAssign( a, b, _max, _min_up, *c, *d ) )
			return true;
		intersect = getIntersection( a, b, _max, _min_up );
		assign( a, b, intersect, *c, *d );
	}
	return re;
}

// float 类型计算值应该等于零却不是零的时候处理
void isToZero(Vector3& v){
	float min = 0.00001;
	if ( fabs(v.x) < min )
		v.x = 0.0;
	if ( fabs(v.y) < min )
		v.y = 0.0;
	if ( fabs(v.z) < min )
		v.z = 0.0;
} 

// 通过t值 求出交点坐标并赋值给c,d
void assign( const Vector3& a, Vector3& c, Vector3& d,  const Vector3& line_dir, const float t){
	if ( t <= 0.5 && t >= 0){
		c = t * line_dir + a;
		isToZero(c);
	}
	if ( t > 0.5 && t <= 1){
		d = t * line_dir + a;
		isToZero(d);
	}
}

// TODO : 定义3维相交测试，细节同上
bool AABB< Vector3 >::intersect( const Vector3& a, const Vector3& b, Vector3* c, Vector3* d ) const
{
	bool re = false;
	float t_max_value = 10000.0;
	float t_min_value = -10000.0;
	// 射线的方向向量
	Vector3 line_dir = Vector3( b.x - a.x, b.y - a.y, b.z - a.z );
	// 射线到三个候选面t值
	float t_min[3] = { -10000.0, -10000.0, -10000.0 };
	//  射线到与候选面对应的远平面t值
	float t_max[3] = { 10000.0, 10000.0, 10000.0 };
	// 判断射线与平行于YZ平面的 AABB两面的相交情况
	if ( line_dir.x == 0 ){
		if ( a.x < _min.x || a.x > _max.x)
			return false;
	}
	else{
		float div = 1.0 / line_dir.x;
		float t1 = ( _min.x - a.x ) * div;
		float t2 = ( _max.x - a.x ) * div;
		t_min[0] = t1 < t2 ? t1 : t2;
		t_max[0] = t1 >= t2 ? t1 : t2;
	}
	// 判断射线与平行于XZ平面的 AABB两面的相交情况
	if ( line_dir.y == 0 ){
		if ( a.y < _min.y || a.y > _max.y)
			return false;
	}
	else{
		float div = 1.0 / line_dir.y;
		float t1 = ( _min.y - a.y ) * div;
		float t2 = ( _max.y - a.y ) * div;
		t_min[1] = t1 < t2 ? t1 : t2;
		t_max[1] = t1 >= t2 ? t1 : t2;
	}
	// 判断射线与平行于XY平面的 AABB两面的相交情况
	if ( line_dir.z == 0 ){
		if ( a.z < _min.z || a.z > _max.z)
			return false;
	}
	else{
		float div = 1.0 / line_dir.z;
		float t1 = ( _min.z - a.z ) * div;
		float t2 = ( _max.z - a.z ) * div;
		t_min[2] = t1 < t2 ? t1 : t2;
		t_max[2] = t1 >= t2 ? t1 : t2;
	}
	sort( t_min, t_min + 3 );
	sort( t_max, t_max + 3 );
	if ( t_min[2] > t_max[0] )
		return false;
	else{
		assign( a, *c, *d, line_dir, t_min[2] );
		assign( a, *c, *d, line_dir, t_max[0] );
		return true;
	}
}

// TODO : 定义4维向量（3维向量的齐次向量，方便和矩阵相乘）
class Vector4
{
public:
	float x, y, z, w;
	Vector4( ){ };
	Vector4( float _x, float _y, float _z, float _w = 1 )
	: x( _x ), y( _y ), z( _z ), w( _w ) { }

	Vector4( Vector3 v , float _w = 1 )
		: x( v.x ), y( v.y ), z( v.z ), w( _w ) { }
};

// 输出4维向量
ostream& operator << ( ostream &out, const Vector4 &v )
{
	cout<<"Vector4:"<<(&v)<<"\tx:"<<v.x<<"\ty:"<<v.y<<"\tz:"<<v.z<<"\tw:"<<v.w<<endl;
	return out;
}
// TODO : 定义4x4矩阵、构造、矩阵乘法、矩阵乘向量、空间操作
class Matrix
{
public:
	float m[16];

	Matrix operator * ( Matrix& mat );
	Vector4 operator * ( const Vector4& vec );
	float &operator []( int pos );
	Matrix(){
		memset( m, 0, sizeof(float) * 16 );
	}
	void print(){
		int pos = 0;
		while ( pos < 16 ){
			if ( pos == 3 || pos == 7 || pos == 11 || pos == 15){
				cout<<m[pos]<<endl;
				pos++;
				continue;
			}
			cout<<m[pos]<<" ";
			pos++;
		}
	}

	// 清除所有信息，从原点平移到v点
	void translate( const Vector3& v );
	// 清除所有信息，绕方向d旋转弧度r
	void rotate( const Vector3& n, float r );
	// 清除所有信息，xyz轴缩放s
	void scale(  const Vector3& s );
	
	// 以上为基础空间操作矩阵，仅表示一种操作，复合操作使用乘法组合
	// 如：先旋转再平移：Mr旋转矩阵，Mt平移矩阵，M为复合矩阵。
	// Mr.rotate(xxx); Mt.translate(xxx); M = Mr * Mt;
};

float& Matrix::operator[]( int pos ){
	return m[pos];
}

Matrix Matrix::operator * ( Matrix& mat ){
	Matrix re;
	for ( int i = 0; i < 4; i++ ){
		for ( int j = 0; j < 4; j++){
			for ( int k = 0; k < 4; k++ ){
				re[4*i+j] += m[4*i+k] * mat[4*k+j];
			}
		}
	}
	return re;
}

Vector4 Matrix::operator * ( const Vector4& vec ){
	Vector4 re;
	float temp;
	re.x = vec.x * m[0] + vec.y * m[4] + vec.z * m[8] + vec.w * m[12];
	re.y = vec.x * m[1] + vec.y * m[5] + vec.z * m[9] + vec.w * m[13];
	re.z = vec.x * m[2] + vec.y * m[6] + vec.z * m[10] + vec.w * m[14];
	re.w = vec.x * m[3] + vec.y * m[7] + vec.z * m[11] + vec.w * m[15];
	return re;
}

void Matrix::translate( const Vector3& v ){
	memset( m, 0, sizeof(float) * 16 );
	m[m11] = m[m22] = m[m33] = m[m44] = 1;
	m[m41] = v.x;
	m[m42] = v.y;
	m[m43] = v.z;
}

void Matrix::rotate( const Vector3& n, float r ){
	memset( m, 0, sizeof(float) * 16 );
	m[m44] = 1;
	float temp = 1 - cosf(r);
	m[m11] = n.x * n.x * temp + cosf(r);
	m[m12] = n.x * n.y * temp + n.z * sinf(r);
	m[m13] = n.x * n.z * temp - n.y * sinf(r);

	m[m21] = n.x * n.y * temp - n.z * sinf(r);
	m[m22] = n.y * n.y * temp + cosf(r);
	m[m23] = n.y * n.z * temp + n.x * sinf(r);

	m[m31] = n.x * n.z * temp + n.y * sinf(r);
	m[m32] = n.y * n.z * temp - n.x * sinf(r);
	m[m33] = n.z * n.z * temp + cosf(r);
}

void Matrix::scale(  const Vector3& s ){
	memset( m, 0, sizeof(float) * 16 );
	m[m44] = 1;
	m[m11] = s.x;
	m[m22] = s.y;
	m[m33] = s.z;
}

void test1( );
void test2( );

}