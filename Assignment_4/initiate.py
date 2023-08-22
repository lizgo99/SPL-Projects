from persistence import *

import sys
import os

def add_branche(splittedline : list[str]):
    #TODO: add the branch into the repo
    repo._Branches.insert(Branche(int(splittedline[0]) , splittedline[1] , int(splittedline[2]))) 

def add_supplier(splittedline : list[str]):
    #TODO: insert the supplier into the repo
    repo._Suppliers.insert(Supplier(int(splittedline[0]) , splittedline[1] , splittedline[2]))

def add_product(splittedline : list[str]):
    #TODO: insert product
    repo._Products.insert(Product(int(splittedline[0]) , splittedline[1] , float(splittedline[2]) , int(splittedline[3])))

def add_employee(splittedline : list[str]):
    #TODO: insert employee
    repo._Employees.insert(Employee(int(splittedline[0]) , splittedline[1] , float(splittedline[2]) , int(splittedline[3])))

adders = {  "B": add_branche,
            "S": add_supplier,
            "P": add_product,
            "E": add_employee}

def main(args : list[str]):
    inputfilename = args[1]
    # delete the database file if it exists
    repo._close()

    # uncomment if needed
    if os.path.isfile("bgumart.db"):
        os.remove("bgumart.db")
    
    repo.__init__()
    repo.create_tables()
    with open(inputfilename) as inputfile:
        for line in inputfile:
            splittedline : list[str] = line.strip().split(",")
            adders.get(splittedline[0])(splittedline[1:])

if __name__ == '__main__':
    main(sys.argv)