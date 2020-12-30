#!/usr/local/bin/python3

def main():
    filename = "output.txt"
    with open(filename) as f:
        mylist = f.read().splitlines() 
        mylist = [int(i) for i in mylist]
        # print (mylist)
        for i in range(0, 100000):
            if i != (mylist[i]-1):
                print ("mistmatch on ",i," ",mylist[i])


if __name__ == "__main__":
    main()