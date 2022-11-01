//
//  sphere.h
//  raytracingInOneWeekend
//
//  Created by 徐雁冰edith on 2022/11/2.
//

#ifndef sphere_h
#define sphere_h

#include "hittable.h"
#include "vec3.hpp"

class sphere : public hittable {
public:
    sphere() {}
    sphere(point3 cen, double r):center(cen),radius(r) {};
    
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    
public:
    point3 center;
    double radius;
    
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    // simplify the hit sphere computation
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b * half_b-a*c;
    
    if (discriminant < 0) return false;
    
    // find the nearest root that lies in the acceptable range
    auto sqrt_discriminant = sqrt(discriminant);
    auto root = (-half_b - sqrt_discriminant) / a;
    if (root < t_min || t_max < root) {
        root =(-half_b + sqrt_discriminant) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }
    
    rec.t = root;
    rec.p = r.at(rec.t);
    auto outward_normal= (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    
    return true;
}



#endif /* sphere_h */
