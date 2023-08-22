from persistence import *

import sys

def main(args : list[str]):
    inputfilename : str = args[1]
    with open(inputfilename) as inputfile:
        for line in inputfile:
            splittedline : list[str] = line.strip().split(", ")
            #TODO: apply the action (and insert to the table) if possible
            repo._Activities.insert(Activitie(int(splittedline[0]) , int(splittedline[1]) , int(splittedline[2]) , splittedline[3]))
            action_quantity = int(splittedline[1])
            product_id = splittedline[0]
            product_DTO = repo._Products.find(id=product_id)[0]
            quantity_in_store = product_DTO.quantity
            new_quantity = quantity_in_store + action_quantity
            if (new_quantity >= 0): 
                repo._Products.update({'id':product_DTO.id,
                                        'description':product_DTO.description,
                                        'price':product_DTO.price,
                                        'quantity':new_quantity
                                        },{
                                        'id':product_DTO.id,
                                        'description':product_DTO.description,
                                        'price':product_DTO.price
                                        })

if __name__ == '__main__':
    main(sys.argv)