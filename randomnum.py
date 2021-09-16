import random

randomget = random.randrange(1,4)

with open("/var/www/html/reqnum.txt","w") as outfile:
    outfile.write(str(randomget))

