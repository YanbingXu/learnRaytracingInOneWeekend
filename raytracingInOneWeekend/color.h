//
//  color.h
//  raytracingInOneWeekend
//
//  Created by 徐雁冰edith on 2022/11/1.
//

#ifndef color_h
#define color_h

#include "vec3.hpp"

#include <iostream>

void write_color(std::ostream &out, color pixel_color){
    // Write the translated [0,255] value of each color component
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
    << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

// anti-aliasing
// Rather than adding in a fractional contribution each time we accumulate more light to the color, just add the full color each iteration, and then perform a single divide at the end (by the number of samples) when writing out the color
void write_color(std::ostream &out, color pixel_color, int samples_per_pixel){
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    
    // devide the color by the number of samples;
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;
    
    // Write the translated [0,255] value of each color component
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
    << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
    
}



#endif /* color_h */
