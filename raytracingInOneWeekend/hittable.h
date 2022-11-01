//
//  hittable.h
//  raytracingInOneWeekend
//
//  Created by 徐雁冰edith on 2022/11/2.
//

#ifndef hittable_h
#define hittable_h

#include "ray.h"

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    // 我们可以把决定surface side留在geometry intersection或者留在着色时，这里由于我们着色的type更多计算更大，因此在intersection的时候就决定surface side
    bool front_face;
    
    inline void set_face_normal(const ray& r, const vec3& outward_normal){
        front_face = dot(r.direction(), outward_normal)<0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const= 0;
};

#endif /* hittable_h */
