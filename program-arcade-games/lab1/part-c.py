#!/usr/bin/env python

# Area of an arbitrary triangle

import math

def triangle_area(one_side, other_side, angle):
    """
        one_side: length of one side
        other_side: length of other_side
        angle: angle between one side and other side
        
        compute the area of traingle 
    """

    return one_side/2 * other_side * math.sin(angle*math.pi/180)

if __name__ == "__main__":
    print("Area of triangle")
    one_side = float(input("Enter length of one side:"))
    other_side = float(input("Enter length of other side:"))
    angle = float(input("Enter the angle in angular form:"))
    print("area is: ", triangle_area(one_side, other_side, angle))
