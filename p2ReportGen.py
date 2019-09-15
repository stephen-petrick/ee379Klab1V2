from ipwhois import IPWhois
from ipwhois.utils import unique_addresses
from pprint import pprint

addresses = [line.rstrip('\n') for line in open ('results.csv')]


#testValue = '209.97.206.188/20'

def getPrefixLength (cidr):
	i = 0
	#print(len(cidr))
	for x in cidr:
		#print("x"+x)
		i += 1
		#print(i)
		if x == '/':	
			if len(cidr)==(i+2):#if there's a second digit for prefex length
				#print("true")
				char1 = cidr[i]
				char2 = cidr[i+1]
				prefixLength = char1+char2
				#print(prefixLength)
				return int(prefixLength)
			else:
				return int(cidr[i])
		#else:
			#print("Error in getting PrefixLength")

#test = getPrefixLength (testValue)
#print("test: "+str(test))

info = []
index = 0
writer = open("p2Reports.txt","w")

for x in addresses:
	dictionary = {'CIDR': 'blank', 'asn_description':'blank','numOfAddresses':-1}
	whoisObj = IPWhois(addresses[index])
	results = whoisObj.lookup_rdap()
	print("Currently working on: "+results['asn_cidr'])
	dictionary['CIDR'] = results['network']['cidr']
	dictionary['asn_description'] = results['asn_description']
	totalAddresses = 2**getPrefixLength(results['network']['cidr'])
	dictionary['numOfAddresses'] = totalAddresses
	writer.write("asn_description: "+dictionary['asn_description']+'\n')
	writer.write("CIDR: "+dictionary['CIDR']+'\n')
	writer.write("Number of IP Addresses: "+str(dictionary['numOfAddresses'])+'\n\n')
	info.append(dictionary)
	index += 1

print(info[0])	
	
