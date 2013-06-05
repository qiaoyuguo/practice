#!/usr/bin/env python

# enter a temperature in Fahrenheit, prints the temperature in Celsius

def fah_to_cels(temp):
    return (temp - 32)/1.8

if __name__ == "__main__":
    fah_temp = float(input("Enter temperature in Fahrenheit:"))
    print("The temperature in Celsius: ", str(fah_to_cels(fah_temp)))
