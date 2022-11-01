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



#endif /* color_h */
