##
# Brennan Reed
# This project is a grocery list tracker that creates a list of items purchased,
# how often they're purchased, and creates a visual for said information for each
# day for the grocery store - all utilizing c++ and python code
# 10/17/21
##

# this file contains the Python code to run the math driving the program
import re
import string

# create empty dictionary that will contain our items and counts
d = dict()

# function that opens List file, formats text and adds count
# no parameters required
# prints the key value pairs (item and count of how many purchased)
def fullList():
    with open(r'List.txt') as text:
   
        for line in text:
            # remove the leading spaces and newline character
            line = line.strip()
  
            # convert the characters in line to 
            # lowercase to avoid case mismatch
            line = line.lower()
  
            # split the line into words
            words = line.split(" ")
  
            # iterate over each word in line
            for word in words:
                # check if the word is already in dictionary
                if word in d:
                    # increment count of word by 1
                    d[word] = d[word] + 1
                else:
                    # add the word to dictionary with count 1
                    d[word] = 1
  
        # print the contents of dictionary
        for key in list(d.keys()):
            print(key, ":", d[key])

# function that opens List file, formats text and adds count,
# but only RETURNS one key/value pair to C++ if it matches
# the specified item (rather than whole list)
# requires itemName string parameter
# returns the key value pair that matches itemName (item and count of how many purchased)
def singleItem(itemName):
    with open(r'List.txt') as text:

        for line in text:
            # Remove the leading spaces and newline character
            line = line.strip()
  
            # Convert the characters in line to 
            # lowercase to avoid case mismatch
            line = line.lower()
  
            # Split the line into words
            words = line.split(" ")
  
            # Iterate over each word in line
            for word in words:
                # Check if the word is already in dictionary
                if word in d:
                    # Increment count of word by 1
                    d[word] = d[word] + 1
                else:
                    # Add the word to dictionary with count 1
                    d[word] = 1

        # prints only specific item from dictionary matching itemName parameter requested
        if itemName in list(d.keys()):         
            for key in list(d.keys()):
                if key == itemName:
                    return d[key]
                    return 1
        else:
            return 0

# function that opens List file and frequency.dat file (creates if not already existing),
# formats List file into key value pairs as we have done previously, then writes them
# as key value pairs into frequency.dat file that C++ will then read
# no parameters required
# returns nothing, but writes a file containing the item and count of how many purchased
# to be read by C++ function
def itemGraph():
    with open(r'List.txt', 'r') as firstFile, open('frequency.dat', 'w') as secondFile:
   
        for line in firstFile:
            # remove the leading spaces and newline character
            line = line.strip()
  
            # convert the characters in line to 
            # lowercase to avoid case mismatch
            line = line.lower()
  
            # split the line into words
            words = line.split(" ")

            # iterate over each word in line
            for word in words:
                # check if the word is already in dictionary
                if word in d:
                    # increment count of word by 1
                    d[word] = d[word] + 1
                else:
                    # add the word to dictionary with count 1
                    d[word] = 1
        
        # iterates through dict we created and writes item followed by 
        # single space and then count to .dat file
        for key in list(d.keys()):
            secondFile.write("{} {}\n".format(key, d[key]))
            # ('{} {}'.format(key,value))
    
    return 0

