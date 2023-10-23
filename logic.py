

def getchar(charset, index):
    return charset[index]


def convert_to_k(number, charset):
    new_base = len(charset)
    ret_str = ""
    while (number // new_base != 0):
        ret_str = getchar(charset, number % new_base) + ret_str
        number = number // new_base

    ret_str = getchar(charset, number % new_base) + ret_str

    return ret_str



total_processes = 240
this_process = 239

charset = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

i = 0
upper = len(charset)**6
while i < upper:
    print(convert_to_k(i, charset))
    i += total_processes


#for i in range(27**3):
#    print(convert_to_k(i, 27))
