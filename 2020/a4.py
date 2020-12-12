#!/usr/bin/env python3

# returns a list with every postion of a given character
# also copied from the StackOverflow lol
def char_position(string, char):
    pos = []
    for n in range(len(string)):
        if string[n] == char:
            pos.append(n)
    return pos

# makes it so that every line is a member of a list, empty strings means end of the passport
def string_parsing(string):
    new_string_list = []
    file1 = open(string, 'r')
    lines = file1.readlines()
    for line in lines:
        new_string = line[:-2]
        new_string_list.append(new_string)

    file1.close()
    return new_string_list


def passport_check(passports):
    valid_counter = 0
    req_fields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"}
    fields = {"cid"}
    lines = string_parsing(passports)

    for line in lines:
        # end of passport - time to check if its valid
        if not line:
            if fields == req_fields:
                valid_counter += 1
            fields = {"cid"}
        # adds every field it encounters to a set
        else:
            x = char_position(line, ':')
            for field in x:
                fields.add(line[field - 3: field])

    return valid_counter

print(passport_check("in/04"))
