#!/usr/bin/env python

# compute the area of the trapezoid

def trap_area(top_base, bottom_base, height):
    return (top_base + bottom_base)*height/2


if __name__ == "__main__":
    print("Area of a trapezoid")
    height = float(input("Enter the height of the trapezoid:"))
    bottom_base = float(input("Enter the length of the bottom base:"))
    top_base = float(input("Enter the length of the top base:"))
    print("The area is: ", trap_area(top_base, bottom_base, height))
