//
//  ray.h
//  raytracingInOneWeekend
//
//  Created by 徐雁冰edith on 2022/11/1.
//

#ifndef ray_h
#define ray_h

#include "vec3.hpp"

class ray {
public:
    ray() {}
    ray(const point3& origin, const vec3& direction, double time = 0.0):orig(origin), dir(direction), tm(time){}
    
    point3 origin() const {return orig;}
    vec3 direction() const{return dir;}
    
    point3 at(double t) const {
        return orig + t*dir;
    }
    
    double time() const {return tm;}
    
public:
    point3 orig;
    vec3 dir;
    double tm;
};


#endif /* ray_h */
