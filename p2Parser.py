from ipwhois import IPWhois
from ipwhois.utils import unique_addresses
from pprint import pprint

"""Includes new lines
fileReader = open("results.csv", "r")
print ("First IP Address: ")
print fileReader.readline()
"""
#lines = open("results.csv", "r")
lines = [line.rstrip('\n') for line in open ('results.csv')]
#lines.readline()
#print(lines)
print(lines[0])

#writer = open("subnetCIDRs.txt","w")
index = 0
subnets = ''

#Parse through IP addresses from .csv file and puts them into subnetCIDRs.txt
"""
writer = open("subnetCIDRs.txt","w")
for x in lines:
	whoisObj = IPWhois(lines[index])
	results = whoisObj.lookup_rdap()
	#print(results)
	print(results['asn_cidr'])
	writer.write(results['asn_cidr']+",")
	index += 1
writer.close()
"""
""" same as above but putting into a string instead of a text file
for x in lines:
	whoisObj = IPWhois(lines[index])
	results = whoisObj.lookup_rdap()
	print(results['asn_cidr'])
	subnets += results['asn_cidr']+","
	index += 1
"""

fileReader = open("subnetCIDRs2.txt", "r")
subnets = fileReader.readline()
#print(subnets)

subnetCount = unique_addresses(data=subnets, file_path = None)
pprint(subnetCount)

#writer.close()
fileReader.close()
