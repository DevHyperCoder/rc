import math
import sys

from typing import List
from tabulate import tabulate

from rc.util import str_to_exponent, in_range
from rc.si_formatter import si_format

# CONSTANTS
resistor_file = "./resistors"
capacitor_file = "./capacitors"

def read_file(filename: str):
    with open(filename,"r") as f:
        return f.readlines()

def parse_file(files: List[str]):
    values = []

    # Parse values like 1.4K to 1.4 * (10 ^ 3)
    for i in files:
        i = i.strip()
        if i[-1] in "pnumKMG":
            values.append(float(i[:-1]) * str_to_exponent(i[-1]))
        else:
            values.append(float(i))
    return values

def main():
    combi = []
    if sys.argv[1] == "r":
        combi = get_time_in_range(float(sys.argv[2]),float(sys.argv[3]))
    elif sys.argv[1] == "a":
        combi = get_all_time_ranges()

    heading = ["Resistance","Capacitance","Time Period"]
    print(tabulate(combi,headers=heading))

def get_time_in_range(start_time,end_time):
    resistors = parse_file(read_file(resistor_file))
    capacitors = parse_file(read_file(capacitor_file))

    combi = []

    # Test all the RC combinations and check if they are in the time range
    for r in resistors:
        for c in capacitors:
            time_period = r*c
            if in_range(time_period,start_time,end_time):
                combi.append([si_format(r),si_format(c),f'{si_format(r*c)}'])
    return combi

def get_all_time_ranges():
    resistors = parse_file(read_file(resistor_file))
    capacitors = parse_file(read_file(capacitor_file))

    combi = []

    # Test all the RC combinations and check if they are in the time range
    for r in resistors:
        for c in capacitors:
            combi.append([si_format(r),si_format(c),f'{si_format(r*c)}'])
    return combi

if __name__ == "__main__":
    main()

