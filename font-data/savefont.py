import json

result = {}
reading = False
char = ""
counter = 0
charnum = 0

f = open("ter-u16b.bdf", "r")

for line in f:
	if (reading and counter < 5): counter += 1
	elif (reading and counter < 21):
		counter += 1
		result[char].append(line[:-1])
	elif (reading and counter >= 21): reading = False


	if ("STARTCHAR" in line): 
		char = line.split(" ")[1][:-1]
		if (charnum > 0 and charnum < 94): 
			reading = True
			result[char] = []
			print(char)
		counter = 0
		charnum += 1
		
with open("bitmap.json", "w") as fp:
	json.dump(result, fp)