import re
import string
import os

file_name = "item_list.txt"
output_file = "frequency.dat"

# Sort the items_list.txt alphabetically and store in sorted_dict for later reference
# input: none
# output: dictionary sorted_dict
#
def SortItems():
    sorted_dict = {}
    try:
        f = open(file_name)
        data = f.readlines()
        data.sort()
        count = 0
        tmp = data[0].strip()
        for item in data:
            if item.strip() == tmp: 
                count += 1
            else:
                sorted_dict[tmp] = count
                tmp = item.strip()
                count = 1
        f.close()
 
    except:
        print("Error opening item list text file.")
        
    return sorted_dict
    
    
# Called on startup to sort the txt file and create the .dat file
# input: none
# output: .dat file and sorted_dict
#
def CreateDatFile():
    try:
        f = open(output_file, 'w')
        sorted_dict = SortItems()
        for k, v in sorted_dict.items():
            f.write(k + ' ' + str(v) + '\n')

        f.close()
    except:
        print("Error creating .dat file")
    

# Print sorted_dict in alphabetical order
# input: none
# output: none
#
def PrintList():
    sorted_dict = SortItems()
    print("{:<20} {:<20}".format('Item', 'Qty'))
    print("{:<20} {:<20}".format('-' * 10, '-' * 10))
    for k, v in sorted_dict.items():
        print("{:<20} {:<20}".format(k, v))


# Seach file for item and print the item and number of times found
# input: string item
# output: returns the value of item or 0 if item does not exist
#
def GetItem(item):
    sorted_dict = SortItems()
    return sorted_dict.get(item, 0)



# Test Functions
################
# SortItems()
# CreateDatFile()
# PrintList()
# print(PrintItem('Apples'))