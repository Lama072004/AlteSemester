# -*- coding: utf-8 -*-

"""
break_xor_key.py
Yoji Watanabe

Script to find the key used in a XOR cipher given the input text and the
encrypted text.
"""

import argparse

parser = argparse.ArgumentParser(description='Script to find the key used in a xor cipher given the decrypted and '
                                             'encrypted text')
parser.add_argument('f_encrypted', metavar='encrypted_text_file', help='Input text')
parser.add_argument('f_decrypted', metavar='decrypted_text_file', help='Output/encrypted text')
args = parser.parse_args()


# get_data(enInput, deInput)
# Function to retrieve encrypted data and decrypted data from the given input
# files.
# Input:  enInput - string to path of the input file
# 		  deInput - string to path of the output file
# Output: two-element array with first element encrypted data, second element 
# 		  decrypted data
def get_data(en_input, de_input):
    encrypted = open(en_input, 'r').read().split()
    decrypted = open(de_input, 'r').read()

    return [encrypted, decrypted]


# get_key(encrypt, decrypt)
# Function to calculate the key used to encrypt a string with an xor cipher
# files.
# Input:  encrypt - string with encrypted data
#         decrypt - string with decrypted data
# Output: string with the key used to encrypt data
def get_key(encrypted, decrypted):
    temp = ''
    for i in range(0, len(encrypted)):
        temp = temp + unichr(int(encrypted[i], 16) ^ ord(decrypted[i % len(decrypted)]))

    return temp


# def clean_key(keyString):
# Returns the key from a larger substring containing multple keys.
# Input:  keyString - string with multiple instances of key to get key from
# Output: string with key
def clean_key(key_string):
    for x in range(1, len(key_string)):
        temp_key = key_string[:x]

        if temp_key * (len(key_string) // len(temp_key)) + \
                (temp_key[:len(key_string) % len(temp_key)]) == key_string:
            return temp_key


# # # # # # # # # # # # # # # # # # # # # # # # #
if __name__ == '__main__':
    [encrypt, decrypt] = get_data(args.f_encrypted, args.f_decrypted)
    key = get_key(encrypt, decrypt)
    key = clean_key(key)

    print 'Text to decrypt:\t' + ' '.join(encrypt)
    print 'Decrypted text:\t\t' + decrypt
    print '########################################'
    print '\tDecrypted key:\t\t' + key
    print '########################################'