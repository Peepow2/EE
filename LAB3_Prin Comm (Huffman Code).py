def Data_Preparation(S): 
    char_freq_prob = sorted([(c, NAME.count(c), NAME.count(c)/len(S)) for c in set(S)], \
                       key = lambda x: (x[1], x[0]), reverse = True)
    # print(char_freq_prob)
    char = [itr[0] for itr in char_freq_prob]
    prob = [itr[2] for itr in char_freq_prob]
    return char_freq_prob, char, prob

def show_result(Huffman_Code, Binary_code):
    print(f"Binary_code = {Binary_code}")
    print(f"Huffman_Code = {Huffman_Code}")
    print(f"length = {len(Huffman_Code)}")
    return

def upper_bound(val, Arr):
    for i in range(len(Arr)-1, 0, -1):
        if Arr[i] >= val:
            return i + 1
    return 0

def Huffman_Encoding(NAME):
    char_freq, char, freq = Data_Preparation(NAME)
    P_xi = [freq]
    Code = [['0', '1']]
    
    for i in range(1, len(char) - 1):
        val = P_xi[i-1][-2] + P_xi[i-1][-1]
        idx = upper_bound(val, P_xi[i-1][:-2:])
        P_xi.append(P_xi[i-1][:idx] + [val] + P_xi[i-1][idx:-2])

    for i in range(len(P_xi) - 1, 0, -1):
        least = P_xi[i-1][-2] + P_xi[i-1][-1]
        for j in range(len(P_xi[i]) - 1, -1, -1):
            if P_xi[i][j] == least:
                C1 = Code[0][j] + '0'
                C2 = Code[0][j] + '1'
                Code.insert(0, Code[0][:j] + Code[0][j+1:] + [C1, C2])
                break
    
    Binary_code = list()
    Huffman_Code = ""

    for i in range(len(char)):
        Binary_code.append((char[i], Code[0][i]))

    for c in NAME: 
        Huffman_Code += Code[0][char.index(c)]

    return Huffman_Code, Binary_code

# Driver Code (MAIN)
NAME = "peerawichsodsuay" #input("Your Name: ")
Huffman_Code, Binary_code = Huffman_Encoding(NAME)
show_result(Huffman_Code, Binary_code)
