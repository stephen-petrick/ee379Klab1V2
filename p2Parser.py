from ipwhois import IPWhois
import pprint

"""Includes new lines
fileReader = open("results.csv", "r")
print ("First IP Address: ")
print fileReader.readline()
"""
lines = open("results.csv", "r")
lines = [lines.rstrip('\n') for line in open ('results.csv')]
lines.readline()

whoisObj = IPWhois(lines.readline())
results = obj.lookup_rws()
print(results['nets'][0]['name'])
