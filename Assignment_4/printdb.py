from persistence import *

def main():
    # TODO: implement
    print("Activities")
    activities_script = """SELECT * FROM activities ORDER BY date"""
    activities_rows = repo.execute_command(activities_script)
    for row in activities_rows:
        print(row)
    
    print("Branches")
    branches_script = """SELECT * FROM branches ORDER BY id"""
    branches_rows = repo.execute_command(branches_script)
    for row in branches_rows:
        print(row)
    
    print("Employees")
    employees_script = """SELECT * FROM employees ORDER BY id"""
    employees_rows = repo.execute_command(employees_script)
    for row in employees_rows:
        print(row)
    
    print("Products")
    products_script = """SELECT * FROM products ORDER BY id"""
    products_rows = repo.execute_command(products_script)
    for row in products_rows:
        print(row)
    
    print("Suppliers")
    suppliers_script = """SELECT * FROM suppliers ORDER BY id"""
    suppliers_rows = repo.execute_command(suppliers_script)
    for row in suppliers_rows:
        print(row)

    print("\nEmployees report")
    employees_report_script = """SELECT employees.name, employees.salary, branches.location, IFNULL(SUM(-activities.quantity*products.price),0) as total_sales_income
                                FROM employees
                                JOIN branches ON employees.branche = branches.id
                                LEFT JOIN activities ON employees.id = activities.activator_id
                                LEFT JOIN products ON activities.product_id = products.id
                                GROUP BY employees.name, employees.salary, branches.location
                                ORDER BY employees.name ASC"""
    employees_report = repo.execute_command(employees_report_script)
    for row in employees_report:
        print(*row, sep=' ')

    print("\nActivities report")
    activities_report_script = """SELECT activities.date, products.description, activities.quantity, employees.name, suppliers.name
                                FROM activities
                                JOIN products ON activities.product_id = products.id
                                LEFT JOIN employees ON activities.activator_id = employees.id
                                LEFT JOIN suppliers ON activities.activator_id = suppliers.id
                                ORDER BY activities.date ASC"""
    activities_report = repo.execute_command(activities_report_script)
    for row in activities_report:
        print(row)

if __name__ == '__main__':
    main()