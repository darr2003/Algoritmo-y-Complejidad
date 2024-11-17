import os
import random

testcases_dir = "./testcases"
num_testcases = 3  
max_length = (int)(input(""))

os.makedirs(testcases_dir, exist_ok=True)

def generate_string(length):
    return ''.join(random.choices('abcdefghijklmnopqrstuvwxyz', k=length))

def compute_output(s1, s2):    
    return abs(len(s1) - len(s2))  

for i in range(1, num_testcases + 1):
    folder = os.path.join(testcases_dir, f"test{i}")
    os.makedirs(folder, exist_ok=True)

    s1 = generate_string(max_length)
    s1 = list(s1)
    half=(int)(max_length/2) 
    quarter=(int)(half/2)

    s2 = s1
    s2[half], s2[half+1] = s1[half+1], s2[half]
    s2[quarter], s2[quarter+1] = s1[quarter+1], s2[quarter]
    s2[half+quarter], s2[half+quarter+1] = s1[half+quarter+1], s1[half+quarter]

    s1 = ''.join(s1)
    s2 = ''.join(s2)
    #s1 = generate_string(random.randint(1, max_length))
    #s2 = generate_string(random.randint(1, max_length))
    with open(os.path.join(folder, "test.txt"), "w") as f_in:
        f_in.write(f"{s1}\n{s2}\n")

print(f"Se generaron {num_testcases} casos de prueba en {testcases_dir}")
