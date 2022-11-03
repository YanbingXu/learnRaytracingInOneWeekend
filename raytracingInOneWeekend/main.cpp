//
//  main.cpp
//  raytracingInOneWeekend
//
//  Created by 徐雁冰edith on 2022/11/1.
//

#include <iostream>

#include "utils.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include "camera.h"

// Coloring background
color ray_color(const ray& r, const hittable& world, int depth_num){
    hit_record rec;
    
    if (depth_num <= 0) {
        return color(0.0, 0.0, 0.0);
    }
    
    if (world.hit(r, 0.001, infinity, rec)) {
        // return 0.5 * (rec.normal + color(1,1,1));
        
        // 对于阴影，较少的光直接向上反射，因此较小球体正下方的较大球体部分更亮。
        vec3 target = rec.p + rec.normal + random_on_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target-rec.p), world, depth_num-1);
    }
    
    vec3 unit_direction = unit_vector(r.direction()); // [-1, 1]
    auto t = 0.5 * (unit_direction.y() + 1.0); // [0,1]
    
    return (1.0 - t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}

int main(int argc, const char * argv[]) {
    
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 256;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int sample_per_pixel = 64;
    const int max_depth = 10;
    
    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
    
    // Camera
    camera cam;
    
    // Render
    std::cout<<"P3\n"<<image_width<<' ' <<image_height<<"\n255\n";
    
    for (int j = image_height-1; j>=0; --j) {
        std::cerr<<"\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i=0; i<image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < sample_per_pixel; ++s) {
                auto u = double(i + random_double())/(image_width-1); // 需要随机偏一点
                auto v = double(j + random_double())/(image_height-1);
                ray r = cam.gen_ray(u,v);

                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, sample_per_pixel);
            
            // no aa
//            auto u = double(i )/(image_width-1);
//            auto v = double(j )/(image_height-1);
//            ray r = cam.gen_ray(u,v);
//            pixel_color =ray_color(r, world);
//            write_color(std::cout, pixel_color);
            
        }
    }
    std::cerr << "\nDone.\n";
    
    return 0;
}
