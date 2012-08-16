#!/usr/bin/python

import sys
import argparse

# ============ parse cmd line =================
parser = argparse.ArgumentParser (description="Parse Beevolve data")
parser.add_argument ("--show_input", action="store_true", help="Show the input lines as they are read")
parser.add_argument ("inputfile", help="input file")
args = parser.parse_args ()

# ================== open file ==================
filename = args.inputfile
try:
    inputfile = open (filename, 'r')
except IOError:
    print "could not open %s" % filename
    exit (1)
#print "# file is [%s]" % filename

# ================= process file ===================
import re
regex = re.compile (r',("[^"]*(?:"|$))?')             # <<<<<<<<<<< all the work is done here

# read field names from header
fields = inputfile.readline().rstrip('\n').split (',')

while inputfile:

    line = inputfile.readline ().rstrip('\n')

    if line:
        if args.show_input:
            print "# read [%s]" % line 

        # match against the regex
        matches = regex.findall (line)
        if matches:

            index = 1 # skip the rating field (checked: always empty in big_data file)

            for match in matches:
                if fields[index] == 'description':
                    print match[1:-1]
                index += 1

    else:
        break
    
inputfile.close ()
