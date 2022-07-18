# STRING XOR STRING
def encrypt_for_vs_key(string: str, key: int):
    L = []
    for char in string:
        hex_loc = hex(ord(char) ^ key)[2:]
        if len(hex_loc) == 1:
            hex_loc = "0" + hex_loc
        hex_loc = "\\x" + hex_loc
        L.append(hex_loc)

    L.append("\\x00")
    res = "{"
    for i, h in enumerate(L):
        res += f"'{h}'"+", "*int(i != len(L)-1)
    res += "};"
    print(res)
    return res

def decrypt_for_vs_str(string_l : str, str_key : str) :
    res = ""
    for i,c in enumerate(string_l[:-1]) :
        res += chr(ord(c)^ord(str_key[i%len(str_key)]))
    print(res)
    return res

# STRING XOR INT
def encrypt_for_vs_str(string : str, str_key : str) :
    L = []
    for i, char in enumerate(string):
        hex_loc = hex(ord(char) ^ ord(str_key[i%(len(str_key))]) )[2:]
        if len(hex_loc) == 1:
            hex_loc = "0" + hex_loc
        hex_loc = "\\x" + hex_loc
        L.append(hex_loc)
    L.append("\\x00")
    res = "{"
    for i, h in enumerate(L):
        res += f"'{h}'"+", "*int(i != len(L)-1)
    res += "};"
    print(res)
    return res

def decrypt_for_vs_key(string_l : list, key : int):
    res = ""
    for c in string_l[:-1] :
        res += chr(ord(c)^key)
    print(res)
    return res

# SPECIAL 
def encrypt_special(val : int, key : int ) :
    print((val^key)*key)
    return (val^key)*key

def decrypt_special(val : int, key : int ) :
    print(int((val/key))^key)
    return (int(val/key))^key

# DOUBLE HELIX
def encrypt_key_dh(key : int, helix1 : int, helix2 : int):
    print(helix1^(key^helix2))
    return helix1^(key^helix2)

def decrypt_key_dh(res : int, helix1 : int, helix2 : int):
    print(helix1^(res^helix2))
    return helix1^(res^helix2)

#Example use :
#encrypt_key_dh(18073568067909359,12899852669886,95977744112225997) #Inversed with decrypt_dh in the .cpp, decrypt_key_dh here
#encrypt_for_vs_key("%d-%02d-%02d", 200) #Inversed with decrypt_key in the .cpp, decrypt_for_vs_key here
#encrypt_for_vs_str("ping -n 3 localhost 1>nul","8d96çç0à@fjsfp,") #Inversed with decrypt_str in the .cpp, decrypt_for_vs_str here
#encrypt_special(168,139) #Inversed with decrypt_special in the .cpp and here

