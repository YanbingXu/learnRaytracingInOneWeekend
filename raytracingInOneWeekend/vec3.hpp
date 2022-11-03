//
//  vec3.hpp
//  raytracingInOneWeekend
//
//  Created by 徐雁冰edith on 2022/11/1.
//

#ifndef vec3_hpp
#define vec3_hpp

#include <stdio.h>

#include <cmath>
#include <iostream>

class vec3{
public:
    vec3():e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}
    
    double x() const {return e[0];}
    double y() const {return e[1];}
    double z() const {return e[2];}
    
    vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
    double operator[](int i) const {return e[i];}
    double& operator[](int i) {return e[i];}
    
    vec3& operator+=(const vec3 &v){
        e[0]+=v.e[0];
        e[1]+=v.e[1];
        e[2]+=v.e[2];
        return *this;
    }
    
    vec3& operator*=(const double t){
        e[0]*=t;
        e[1]*=t;
        e[2]*=t;
        return *this;
    }
    
    vec3& operator/=(const double t){
        return *this *= 1/t;
    }
    
    double length() const {
        return std::sqrt(length_squared());
    }
    
    double length_squared() const {
        return e[0] * e[0] + e[1]*e[1] + e[2]*e[2];
    }
    
    inline static vec3 random(){
        return vec3(random_double(), random_double(), random_double());
    }
    
    inline static vec3 random(double min, double max){
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
    
    bool near_zero()const{
        const auto s = 1e-8;
        return (fabs(e[0])<s) && (fabs(e[1])<s) && (fabs(e[2])<s);
    }
    
public:
    double e[3];
};

// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3;  // RGB color

// vec3 utility functions
inline std::ostream& operator<<(std::ostream &out, const vec3 &v){
    return out<<v.e[0]<<' '<<v.e[1]<<' '<<v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v){
    return vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v){
    return vec3(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v){
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t){
    return t*v;
}

inline vec3 operator/(vec3 v, double t){
    return (1/t)*v;
}

inline double dot(const vec3& u, const vec3& v){
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v){
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v){
    return v / v.length();
}

// We need a way to pick a random point in a unit radius sphere. We’ll use what is usually the easiest algorithm: a rejection method. First, pick a random point in the unit cube where x, y, and z all range from −1 to +1. Reject this point and try again if the point is outside the sphere.
vec3 random_in_unit_sphere(){
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() > 1) {
            continue;
        }
        return p;
    }
}

// lambertian distribution
// True Lambertian has the probability higher for ray scattering close to the normal, but the distribution is more uniform. This is achieved by picking random points on the surface of the unit sphere, offset along the surface normal. Picking random points on the unit sphere can be achieved by picking random points in the unit sphere, and then normalizing those.
vec3 random_on_unit_sphere(){
    return unit_vector(random_in_unit_sphere());
}

// another random distribution
vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

// The reflected ray direction in red is just 𝐯+2𝐛. In our design, 𝐧 is a unit vector, but 𝐯 may not be. The length of 𝐛 should be 𝐯⋅𝐧. Because 𝐯 points in, we will need a minus sign, yielding
vec3 reflect(const vec3& v, const vec3& n){
    return v-2*dot(n,v)*n;
}

#endif /* vec3_hpp */
