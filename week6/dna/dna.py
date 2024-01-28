import csv
from sys import argv, exit

def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # TODO: Read database file into a variable
    database=[]

    # Read in database file - using `with` means we don't have to close the file
    with open(argv[1], "r") as file:
        read = csv.DictReader(file)

        for row in read:
            database.append(row)
        # print(read)
        # print()
        # print(database)
        # [{'name': 'Alice', 'AGATC': '2', 'AATG': '8', 'TATC': '3'}, {'name': 'Bob', 'AGATC': '4', 'AATG': '1', 'TATC': '5'}, {'name': 'Charlie', 'AGATC': '3', 'AATG': '2', 'TATC': '5'}]
        # hna l data base di mt save fih awl file as list fiha dict

    # TODO: Read DNA sequence file into a variable
    with open(argv[2], "r") as file:
        sequence = file.read()
        # print(sequence)
        # print()


    # TODO: Find longest match of each STR in DNA sequence
    # imppppppp
    subsequance={}
    for key in database[0].keys():
        if key != 'name':
            longest= longest_match(sequence,key)
            subsequance[key]=longest
            # print(subsequance)

    # longest_match(sequence,database[])
    count=0
    # TODO: Check database for matching profiles
    for i in range(len(database)):
        match = True
        for key in subsequance:
            newdict=database[i]
            # print(key ,subsequance[key])
            # print(newdict['name'],newdict[key])

            if subsequance[key]!=int(newdict[key]):
                match = False
                break
        if match:
            print(newdict['name'])

            return

        #     print('hereee')
        #     print(database[i].values())

        # #     # ={key:longest}
        #     count+=1
        # print(f"count{count}")
    print('No match')

def longest_match(sequence,subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
